#pragma once


#pragma once
#include <Arduino.h>
#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>
#include <Button.h>
#include <Wire.h>
#include <MPU6886.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <cplus_RTC.h>

#include <esp_wifi.h>

#include "arduinoFFT.h"

#define display Disbuff
#define displayUpdate Displaybuff

#define LCD_MOSI_PIN 15
#define LCD_MISO_PIN -1
#define LCD_SCLK_PIN 13
#define LCD_DC_PIN 14
#define LCD_CS_PIN 5
#define LCD_RST_PIN 12
#define LCD_BUSY_PIN -1
#define LCD_BL_PIN 27

#define POWER_HOLD_PIN 4
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

#define I2S_DATA_PIN 34
#define I2S_SCLK_PIN 0

#define WIFI_SSID     "TP-Link_D30C"
#define WIFI_PASSWORD "66331926"
#define NTP_TIMEZONE  "UTC-2"
#define NTP_SERVER1   "0.pool.ntp.org"
#define NTP_SERVER2   "1.pool.ntp.org"
#define NTP_SERVER3   "2.pool.ntp.org"

class CLite_GFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    CLite_GFX(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi = LCD_MOSI_PIN;
            cfg.pin_miso = LCD_MISO_PIN;
            cfg.pin_sclk = LCD_SCLK_PIN;
            cfg.pin_dc = LCD_DC_PIN;
            cfg.freq_write = 40000000;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert = true;
            cfg.pin_cs = LCD_CS_PIN;
            cfg.pin_rst = LCD_RST_PIN;
            cfg.pin_busy = LCD_BUSY_PIN;
            cfg.panel_width = 135;
            cfg.panel_height = 240;
            cfg.offset_x = 52;
            cfg.offset_y = 40;
            // cfg.offset_x     = 0;
            // cfg.offset_y     = 0;

            _panel_instance.config(cfg);
        }
        {                                        // バックライト制御の設定を行います。（必要なければ削除）
            auto cfg = _light_instance.config(); // バックライト設定用の構造体を取得します。

            cfg.pin_bl = 27;    // バックライトが接続されているピン番号
            cfg.invert = false; // バックライトの輝度を反転させる場合 true
            // cfg.freq   = 44100;           // バックライトのPWM周波数
            cfg.freq = 200;      // バックライトのPWM周波数
            cfg.pwm_channel = 7; // 使用するPWMのチャンネル番号

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance); // バックライトをパネルにセットします。
        }

        setPanel(&_panel_instance);
    }
};

typedef struct {
    float x;
    float y;
    float z;
} Accel;

typedef struct {
    uint32_t width;
    uint32_t height;
}Screen;

typedef struct {
    float x[10] ={};
    float y[10] ={};
    float z[10] ={};
} AccelerationBuffer;

namespace TEST
{
    class TEST
        {
            private:

                void wifi_setup();
                void display_time();
                void display_battery();
                void set_cursor(int x,int y);
                

            public:
                uint8_t i;
                uint16_t width;
                uint16_t height;
                uint16_t battery_percentage;
                void setup();
                void loop();           
            
    };

}




// Different versions of the framework have different SNTP header file names and
// availability.
#if __has_include(<esp_sntp.h>)
#include <esp_sntp.h>
#define SNTP_ENABLED 1
#elif __has_include(<sntp.h>)
#include <sntp.h>
#define SNTP_ENABLED 1
#endif

#ifndef SNTP_ENABLED
#define SNTP_ENABLED 0
#endif
