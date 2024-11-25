//#include <TEST.h>
//
//void set_cursor(int x, int y){
//    M5.Display.setCursor(x,y);
//}
//
//void wifi_setup() {
//    if (!M5.Rtc.isEnabled()) {
//        Serial.println("RTC not found.");
//        M5.Display.println("RTC not found.");
//        for (;;) {
//            vTaskDelay(500);
//        }
//    }
//    Serial.println("RTC found.");
//
//    M5.Display.print("WiFi:");
//    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//    while (WiFi.status() != WL_CONNECTED) {
//        Serial.print('.');
//        vTaskDelay(500);
//    }
//    Serial.println("\r\n WiFi Connected.");
//    M5.Display.print("Connected.");
//
//    configTzTime(NTP_TIMEZONE, NTP_SERVER1, NTP_SERVER2, NTP_SERVER3);
//    vTaskDelay(500);
//
//    #if SNTP_ENABLED
//    while (sntp_get_sync_status() != SNTP_SYNC_STATUS_COMPLETED) {
//        Serial.print('.');
//        delay(1000);
//    }
//    #else
//        delay(1600);
//        struct tm timeInfo;
//        while (!getLocalTime(&timeInfo, 1000)) {
//            Serial.print('.');
//        };
//    #endif
//
//    Serial.println("\r\n NTP Connected.");
//
//    time_t t = time(nullptr) + 1;  // Advance one second.
//    while (t > time(nullptr))
//        ;  /// Synchronization in seconds
//    M5.Rtc.setDateTime(gmtime(&t));
//}
//
//void display_time() {
//    // put your setup code here, to run once:
//  static constexpr const char* const wd[7] = {"Sun", "Mon", "Tue", "Wed",
//                                                "Thr", "Fri", "Sat"};
//
//    auto t = time(nullptr);
//
//    {
//        auto tm = localtime(&t);  // for local timezone.
//        set_cursor(0, 0);
//        M5.Display.printf("%02d:%02d:%02d",
//                                tm->tm_hour, tm->tm_min, tm->tm_sec);
//    }
//}
//
//void display_battery(){
//    battery_percentage = M5.Power.getBatteryLevel();
//    set_cursor(1,height-20);
//    M5.Display.printf("Battery:%d", battery_percentage);
//}
//
//void setup() {
//    // put your setup code here, to run once:
//    auto cfg = M5.config();
//    M5.begin(cfg);
//    M5.Display.setRotation(1);
//    int textsize = M5.Display.height() / 60;
//    
//
//    width = M5.Display.width();
//    height = M5.Display.height();
//
//    if (textsize == 0){
//        textsize = 1;
//    }
//
//    M5.Display.setTextSize(textsize);
//
//    wifi_setup();
//
//    M5.Display.clear();
//
//    x_avg = 0;
//    y_avg = 0;
//    z_avg = 0;
//
//
//}
//
//
//void loop() {
//
//    // Update M5
//    M5.update();
//
//    // Display the time
//    display_time();
//
//    // Display the battery
//    display_battery();
//
//    // Read imu data
//    auto imu_update = M5.Imu.update();
//
//    if (imu_update){
//        set_cursor(width/2,height/2);
//
//        auto data = M5.Imu.getImuData();
//        // The data obtained by getImuData can be used as follows.
//        // data.accel.x;      // accel x-axis value.
//        // data.accel.y;      // accel y-axis value.
//        // data.accel.z;      // accel z-axis value.
//        // data.accel.value;  // accel 3values array [0]=x / [1]=y / [2]=z.
//
//        // data.gyro.x;      // gyro x-axis value.
//        // data.gyro.y;      // gyro y-axis value.
//        // data.gyro.z;      // gyro z-axis value.
//        // data.gyro.value;  // gyro 3values array [0]=x / [1]=y / [2]=z.
//        
//        // Fill up buffer
//        accel_Buf.x[i] = data.accel.x;
//        accel_Buf.x[i] = data.accel.x;
//        accel_Buf.x[i] = data.accel.x;
//
//        i = i + 1;
//        
//        // Calculate average acceleration over the last 10 samples
//        x_avg = (accel_Buf.x[0] + accel_Buf.x[1] + accel_Buf.x[2] + accel_Buf.x[3] + accel_Buf.x[4] + accel_Buf.x[5] + accel_Buf.x[6] + accel_Buf.x[7] + accel_Buf.x[8] + accel_Buf.x[9])/10;
//        y_avg = (accel_Buf.y[0] + accel_Buf.y[1] + accel_Buf.y[2] + accel_Buf.y[3] + accel_Buf.y[4] + accel_Buf.y[5] + accel_Buf.y[6] + accel_Buf.y[7] + accel_Buf.y[8] + accel_Buf.y[9])/10;
//        z_avg = (accel_Buf.z[0] + accel_Buf.z[1] + accel_Buf.z[2] + accel_Buf.z[3] + accel_Buf.z[4] + accel_Buf.z[5] + accel_Buf.z[6] + accel_Buf.z[7] + accel_Buf.z[8] + accel_Buf.z[9])/10;    
//
//
//        // Check for raise to wake 
//        if (abs(x_avg-accel_Buf.x[i])>0.5){
//            M5.Display.wakeup();
//        }
//
//        if (abs(y_avg-accel_Buf.y[i])>0.5){
//            M5.Display.wakeup();
//        }
//
//        if (abs(z_avg-accel_Buf.z[i])>0.5){
//            M5.Display.wakeup();
//        }
//
//
//        if (i>10){
//            i=0;
//        }
//
//
//    }
// 
//    // Enters sleep mode if btnA is pressed
//    if (M5.BtnA.wasPressed()) {
//        M5.Speaker.tone(8000, 20);
//        M5.Display.sleep();
//    }
//
//    // Exits sleep mode if btnB is pressed
//    if (M5.BtnB.wasPressed()) {
//        M5.Speaker.tone(8000, 20);
//        
//    }
//
//    M5.Display.printf("%d",M5.Rtc.getTime().seconds);
//
//}
//
//
//

/**
 * @file TEST.cpp
 * @author Ruben van Tonder
 * @brief
 * @version 0.1
 * @date 2024-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <test.h>

namespace TEST
{

    Screen screen;
    Accel acceleration;
    AccelerationBuffer accel_Buf;
    TEST test;

    /// @brief Set the cursor to coordinates (x,y) on the screen
    /// @param x 
    /// @param y 
    void TEST::set_cursor(int x, int y){
        //M5.Display.setCursor(x,y);
    }

    void TEST::wifi_setup() {
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

    void TEST::display_time() {
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

    void TEST::display_battery(){
        test.battery_percentage = M5.Power.getBatteryLevel();
        set_cursor(1,screen.height-20);
        M5.Display.printf("Battery:%d", test.battery_percentage);
    }

    void TEST::setup() {

        // put your setup code here, to run once:
        auto cfg = M5.config();
        M5.begin(cfg);
        M5.Display.setRotation(1);
        int textsize = M5.Display.height() / 60;


        screen.width = M5.Display.width();
        screen.height = M5.Display.height();

        if (textsize == 0){
            textsize = 1;
        }

        M5.Display.setTextSize(textsize);

        wifi_setup();

        M5.Display.clear();

        acceleration.x = 0;
        acceleration.y = 0;
        acceleration.z = 0;
    }

  void TEST::loop() {

    // Update M5
    M5.update();

    // Display the time
    display_time();

    // Display the battery
    display_battery();

    // Read imu data
    auto imu_update = M5.Imu.update();

    if (imu_update){
        set_cursor(screen.width/2,screen.height/2);

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
        accel_Buf.x[test.i] = data.accel.x;
        accel_Buf.x[test.i] = data.accel.x;
        accel_Buf.x[test.i] = data.accel.x;

        test.i = test.i + 1;
        
        // Calculate average acceleration over the last 10 samples
        acceleration.x = (accel_Buf.x[0] + accel_Buf.x[1] + accel_Buf.x[2] + accel_Buf.x[3] + accel_Buf.x[4] + accel_Buf.x[5] + accel_Buf.x[6] + accel_Buf.x[7] + accel_Buf.x[8] + accel_Buf.x[9])/10;
        acceleration.y = (accel_Buf.y[0] + accel_Buf.y[1] + accel_Buf.y[2] + accel_Buf.y[3] + accel_Buf.y[4] + accel_Buf.y[5] + accel_Buf.y[6] + accel_Buf.y[7] + accel_Buf.y[8] + accel_Buf.y[9])/10;
        acceleration.z = (accel_Buf.z[0] + accel_Buf.z[1] + accel_Buf.z[2] + accel_Buf.z[3] + accel_Buf.z[4] + accel_Buf.z[5] + accel_Buf.z[6] + accel_Buf.z[7] + accel_Buf.z[8] + accel_Buf.z[9])/10;    


        // Check for raise to wake 
        if (abs(acceleration.x-accel_Buf.x[test.i])>0.5){
            M5.Display.wakeup();
        }

        if (abs(acceleration.y-accel_Buf.y[test.i])>0.5){
            M5.Display.wakeup();
        }

        if (abs(acceleration.z-accel_Buf.z[test.i])>0.5){
            M5.Display.wakeup();
        }


        if (test.i>10){
            test.i=0;
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
}
