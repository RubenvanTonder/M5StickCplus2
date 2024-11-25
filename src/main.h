#pragma once


#include <Arduino.h> 
#include <M5StickCPlus2.h>
#include <WiFi.h>

#define WIFI_SSID     "TP-Link_D30C"
#define WIFI_PASSWORD "66331926"
#define NTP_TIMEZONE  "UTC-2"
#define NTP_SERVER1   "0.pool.ntp.org"
#define NTP_SERVER2   "1.pool.ntp.org"
#define NTP_SERVER3   "2.pool.ntp.org"

int width;
int height;
int battery_percentage;
float x_avg;
float y_avg;
float z_avg;

float accel_x_buffer [10] = {};
float accel_y_buffer [10] = {};
float accel_z_buffer [10] = {};

uint8_t i;

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

void wifi_setup();
void dispaly_time();
void display_battery();
void set_cursor(int x,int y);