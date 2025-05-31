#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include <iostream>

int main() {
    // Получаем IP
    httplib::SSLClient ipify("api.ipify.org", 443);
    auto ip_res = ipify.Get("/?format=json");
    if (!ip_res || ip_res->status != 200) {
        std::cout << "Не удалось получить ip" << std::endl;
        return 1;
    }
    nlohmann::json ip_json = nlohmann::json::parse(ip_res->body);
    std::string ip = ip_json["ip"];

    // Геолокация по IP
    httplib::Client ipapi("ip-api.com", 80);
    std::string geo_path = "/json/" + ip;
    auto geo_res = ipapi.Get(geo_path);
    if (!geo_res || geo_res->status != 200) {
        std::cout << "Не удалось получить геолокацию" << std::endl;
        return 1;
    }

    nlohmann::json geo_json = nlohmann::json::parse(geo_res->body);
    double lat = geo_json["lat"];
    double lon = geo_json["lon"];
    //std::cout << "Широта: " << lat << ", Долгота: " << lon << std::endl;

    // Погода 
    httplib::SSLClient meteo("api.open-meteo.com", 443);
    std::string weather_path = "/v1/forecast?latitude=" + std::to_string(lat) +"&longitude=" + std::to_string(lon) +
    "&current=temperature_2m,wind_speed_10m";
    auto weather_res = meteo.Get(weather_path);
    if (!weather_res || weather_res->status != 200) {
        std::cout << "Не удалось получить погоду" << std::endl;
        return 1;
    }
    nlohmann::json weather_json = nlohmann::json::parse(weather_res->body);
    //auto current = weather_json["current"];
    std::cout << "  Температура: " << weather_json["current"]["temperature_2m"] << " °C" << std::endl;
    std::cout << "  Ветер:       " << weather_json["current"]["wind_speed_10m"] << " км/ч" << std::endl;

    return 0;
}