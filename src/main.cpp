/**
 * @file main.cpp
 * @author Ruben van Tonder
 * @brief
 * @version 0.1
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <main.hpp>


void setup() {
    // Initialize the M5StickC with default settings
    auto cfg = M5.config();


    cfg.output_power = true; // Enable power for the display
    M5.begin(cfg);
    M5.Rtc.setDateTime( { { 2021, 12, 31 }, { 12, 34, 56 } } );

    // Clear the screen
    M5.Display.fillScreen(TFT_BLACK);
    delay(500);
    // Set text color and size
    M5.Display.setTextColor(TFT_WHITE);
    M5.Display.setTextSize(2);
    M5.Display.setRotation(3);

    // Display text on the screen
    M5.Display.setCursor(25, display.height/2-25); // Set cursor position (x, y)
    //M5.Display.println("Hello, M5StickC!");
    M5.Display.printf("Husky Firmware");
    delay(2000);
    M5.Display.clear(TFT_BLACK);

    M5.Display.setCursor(display.width/2-55,display.height/2-15);
}

void loop() {
  // No continuous tasks in this example
  M5.update();

  // Read state of buttons
  read_ButtonA_State();
  
  switch (menu)
  {
  case 0:

  // Clear display
  if (!main_screen_load)
  {
    M5.Display.clearDisplay(TFT_BLACK);
    load_menu = false;
    main_screen_load = true;
  }
    date = M5.Rtc.getDateTime();
    if (date.time.seconds != previous_seconds)
    {
      M5.Display.setClipRect(display.width/2-55,display.height/2-15,100,50);
      M5.Display.clearDisplay(TFT_BLACK);
      M5.Display.setCursor(display.width/2-55,display.height/2-15);
      M5.Display.printf("%02d:%02d:%02d\n"
               , date.time.hours
               , date.time.minutes
               , date.time.seconds
               );
      previous_seconds = date.time.seconds;
      M5.Display.clearClipRect();
      M5.Display.setCursor(5,5);
      M5.Display.printf("%02d:%02d:%02d\n"
        , date.date.year
        , date.date.month
        , date.date.date
        );
        M5.Display.setCursor(display.width-100,0);
      M5.Display.printf("Bat %d", M5.Power.getBatteryLevel());
    }
    
  
    break;
  case 1:

    if (!load_menu)
    {
      // Clear the display
      M5.Display.clearDisplay(TFT_BLACK);
      // Set cursor to display first menu item
      M5.Display.setCursor(5,5);
      M5.Display.println("Home Screen");

      // Set cursor to display the second menu item
      M5.Display.setCursor(5,35);
      M5.Display.println("Second Screen");

      load_menu = true;
      main_screen_load = false;

      // make sure the button states are reset
      M5.BtnA.setRawState(100, false);
      M5.BtnB.setRawState(100, false);
      M5.BtnC.setRawState(100, false);
      delay(2500);
    }

    // change menu selection
    if(M5.BtnB.isPressed())
    {
      if (menu_selected <1)
      {
        menu_selected++;
      }
    }

    // Switch to selected screen/application
    if (M5.BtnA.isPressed())
    {
      M5.Display.printf("Here");
      delay(1000);
      switch (menu_selected)
      {
      case 0:
        menu = 0;
        break;
      case 1:
        menu = 2;
        break; 
      default:
        break;
      }
    }

    break;

    case 2:

     M5.Display.clearDisplay(TFT_BLACK);
  
  default:
    break;
  }
        
}

void read_ButtonA_State()
{
  if (M5.BtnA.wasPressed())
  {
    if (menu<4){
      menu++;
    }
  }
}
