#include <WeatherGenerator.hpp>

void WeatherGenerator::generate() {
  HTTPClient http;

  String url = String("https://api.openweathermap.org/data/2.5/weather") + \
    String("?appid=") + String(app_id) + \
    String("&lat=") + String(latitude) + \
    String("&lon=") + String(longitude) + \
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