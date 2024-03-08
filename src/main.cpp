#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "secrets.h"

WiFiClient espClient;

const double_t latitude = 45.35735430070989;
const double_t longitude = 9.650215542624574;

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

void get_weather(const char* appid, double_t lat, double_t lon) {
  HTTPClient http;

  String url = String("https://api.openweathermap.org/data/2.5/weather") + \
    String("?appid=") + String(appid) + \
    String("&lat=") + String(lat) + \
    String("&lon=") + String(lon) + \
    String("&units=metric&lang=it");
  http.begin(url.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode != 200) {
    Serial.println("Failed to get weather update");
    Serial.println(httpResponseCode);
    return;
  }

  String body = http.getString();

  JsonDocument doc;
  deserializeJson(doc, body.c_str());

  String banner = String("Meteo ") + String(doc["name"].as<String>()) + String(": ") + \
    String(doc["weather"][0]["description"].as<String>()) + String(" ") + \
    String(doc["main"]["temp"].as<double>(), 1) + String("C");
  Serial.println(banner);
}

void setup() {
  delay(100);

  Serial.begin(9600);
  while(!Serial);

  connectToWiFi(WIFI_SSID, WIFI_PASS);
}

void loop() {
  get_weather(OPENWEATHERMAPORG_APPID, latitude, longitude);
  delay(5000);
}
