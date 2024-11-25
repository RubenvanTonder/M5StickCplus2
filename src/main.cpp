#include <main.h>

void set_cursor(int x, int y){
    M5.Display.setCursor(x,y);
}

void wifi_setup() {
    if (!M5.Rtc.isEnabled()) {
        Serial.println("RTC not found.");
        M5.Display.println("RTC not found.");
        for (;;) {
            vTaskDelay(500);
        }
    }
    Serial.println("RTC found.");

    M5.Display.print("WiFi:");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        vTaskDelay(500);
    }
    Serial.println("\r\n WiFi Connected.");
    M5.Display.print("Connected.");

    configTzTime(NTP_TIMEZONE, NTP_SERVER1, NTP_SERVER2, NTP_SERVER3);
    vTaskDelay(500);

    #if SNTP_ENABLED
    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
        Serial.print('.');
        delay(1000);
    }
    #else
        delay(1600);
        struct tm timeInfo;
        while (!getLocalTime(&timeInfo, 1000)) {
            Serial.print('.');
        };
    #endif

    Serial.println("\r\n NTP Connected.");

    time_t t = time(nullptr) + 1;  // Advance one second.
    while (t > time(nullptr))
        ;  /// Synchronization in seconds
    M5.Rtc.setDateTime(gmtime(&t));
}

void display_time() {
    // put your setup code here, to run once:
  static constexpr const char* const wd[7] = {"Sun", "Mon", "Tue", "Wed",
                                                "Thr", "Fri", "Sat"};

    auto t = time(nullptr);

    {
        auto tm = localtime(&t);  // for local timezone.
        set_cursor(0, 0);
        M5.Display.printf("%02d:%02d:%02d",
                                tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
}

void display_battery(){
    battery_percentage = M5.Power.getBatteryLevel();
    set_cursor(1,height-20);
    M5.Display.printf("Battery:%d", battery_percentage);
}

void setup() {
    // put your setup code here, to run once:
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Display.setRotation(1);
    int textsize = M5.Display.height() / 60;
    

    width = M5.Display.width();
    height = M5.Display.height();

    if (textsize == 0){
        textsize = 1;
    }

    M5.Display.setTextSize(textsize);

    wifi_setup();

    M5.Display.clear();

    x_avg = 0;
    y_avg = 0;
    z_avg = 0;


}


void loop() {

    // Update M5
    M5.update();

    // Display the time
    display_time();

    // Display the battery
    display_battery();

    // Read imu data
    auto imu_update = M5.Imu.update();

    if (imu_update){
        set_cursor(width/2,height/2);

        auto data = M5.Imu.getImuData();
        // The data obtained by getImuData can be used as follows.
        // data.accel.x;      // accel x-axis value.
        // data.accel.y;      // accel y-axis value.
        // data.accel.z;      // accel z-axis value.
        // data.accel.value;  // accel 3values array [0]=x / [1]=y / [2]=z.

        // data.gyro.x;      // gyro x-axis value.
        // data.gyro.y;      // gyro y-axis value.
        // data.gyro.z;      // gyro z-axis value.
        // data.gyro.value;  // gyro 3values array [0]=x / [1]=y / [2]=z.
        
        // Fill up buffer
        accel_x_buffer[i] = data.accel.x;
        accel_x_buffer[i] = data.accel.x;
        accel_x_buffer[i] = data.accel.x;

        i = i + 1;
        
        // Calculate average acceleration over the last 10 samples
        x_avg = (accel_x_buffer[0] + accel_x_buffer[1] + accel_x_buffer[2] + accel_x_buffer[3] + accel_x_buffer[4] + accel_x_buffer[5] + accel_x_buffer[6] + accel_x_buffer[7] + accel_x_buffer[8] + accel_x_buffer[9])/10;
        y_avg = (accel_y_buffer[0] + accel_y_buffer[1] + accel_y_buffer[2] + accel_y_buffer[3] + accel_y_buffer[4] + accel_y_buffer[5] + accel_y_buffer[6] + accel_y_buffer[7] + accel_y_buffer[8] + accel_y_buffer[9])/10;
        z_avg = (accel_z_buffer[0] + accel_z_buffer[1] + accel_z_buffer[2] + accel_z_buffer[3] + accel_z_buffer[4] + accel_z_buffer[5] + accel_z_buffer[6] + accel_z_buffer[7] + accel_z_buffer[8] + accel_z_buffer[9])/10;    


        // Check for raise to wake 
        if (abs(x_avg-accel_x_buffer[i])>0.5){
            M5.Display.wakeup();
        }

        if (abs(y_avg-accel_y_buffer[i])>0.5){
            M5.Display.wakeup();
        }

        if (abs(z_avg-accel_z_buffer[i])>0.5){
            M5.Display.wakeup();
        }


        if (i>10){
            i=0;
        }


    }
 
    // Enters sleep mode if btnA is pressed
    if (M5.BtnA.wasPressed()) {
        M5.Speaker.tone(8000, 20);
        M5.Display.sleep();
    }

    // Exits sleep mode if btnB is pressed
    if (M5.BtnB.wasPressed()) {
        M5.Speaker.tone(8000, 20);
        
    }

    M5.Display.printf("%d",M5.Rtc.getTime().seconds);

}


