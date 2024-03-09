#include <WeatherGenerator.hpp>

void WeatherGenerator::display(MD_Parola& display) {
  if (next_banner.equals("")) {
    Serial.print("Fetching next weather banner ... ");
    next_banner = generate();
    Serial.println(next_banner);
  }

  if (display.displayAnimate()) {
    next_banner = "";
    display.displayText(next_banner.c_str(), PA_LEFT, 40, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}

String WeatherGenerator::generate() {
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
    return String("");
  }

  String body = http.getString();

  JsonDocument doc;
  deserializeJson(doc, body.c_str());

  String banner = String("Meteo ") + String(doc["name"].as<String>()) + String(": ") + \
    String(doc["weather"][0]["description"].as<String>()) + String(" ") + \
    String(doc["main"]["temp"].as<double>(), 1) + String("C");
  // Serial.println(banner);

  return banner;
}