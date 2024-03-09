#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <MD_Parola.h>

#include <WeatherGenerator.hpp>

#include "secrets.h"

WiFiClient espClient;

// Max7219 display
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 12

#define CLK_PIN   18 // VSPI_SCK
#define DATA_PIN  23 // VSPI_MOSI
#define CS_PIN    5  // VSPI_SS

MD_Parola display(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const double latitude = 45.35735430070989;
const double longitude = 9.650215542624574;

WeatherGenerator weather_g(OPENWEATHERMAPORG_APPID, latitude, longitude);

void connectToWiFi(const char* ssid, const char* pass) {
  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to WiFi with IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  delay(100);

  Serial.begin(57600);
  while(!Serial);

  connectToWiFi(WIFI_SSID, WIFI_PASS);

  display.begin();
  display.setIntensity(1);
}

void loop() {
  weather_g.display(display);
}
