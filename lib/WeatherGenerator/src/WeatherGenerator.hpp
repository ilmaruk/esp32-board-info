#ifndef H_WEATHER_GENERATOR
#define H_WEATHER_GENERATOR

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class WeatherGenerator {
public:
    WeatherGenerator(const char* app_id, const double lat, const double lon) : app_id(app_id), latitude(lat), longitude(lon) {};
    void generate();
private:
    const char* app_id;
    const double latitude;
    const double longitude;
};

#endif