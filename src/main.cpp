#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <WeatherGenerator.hpp>

#include "secrets.h"

WiFiClient espClient;

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

  Serial.begin(9600);
  while(!Serial);

  connectToWiFi(WIFI_SSID, WIFI_PASS);
}

void loop() {
  weather_g.generate();
  delay(5000);
}
