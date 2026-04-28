/*
Autor: Rafael Márquez
Dia: 19/9/25
Objetivo: Practica 1, ejercicio 8.
*/

#include <iostream>
#include <chrono>

std::chrono::minutes parseHora(const std::string& s) {
    int h = std::stoi(s.substr(0, 2));
    int m = std::stoi(s.substr(3, 2));
    return std::chrono::hours{h} + std::chrono::minutes{m};
}

std::string toStringHora(std::chrono::minutes t) {
    auto h = std::chrono::duration_cast<std::chrono::hours>(t).count();
    auto m = (t % std::chrono::hours{1}).count();
    std::string hh = (h < 10 ? "0" : "") + std::to_string(h);
    std::string mm = (m < 10 ? "0" : "") + std::to_string(m);
    return hh + ":" + mm;
}

int main(){
    std::string strStartHour, strEndHour;
    std::cout << "Intruce hora de inicio (HH:MM): ";
    std::cin >> strStartHour;
    std::cout << "Intruce hora de fin (HH:MM): ";
    std::cin >> strEndHour;

    std::chrono::minutes startHour, endHour;

    startHour = parseHora(strStartHour);
    endHour = parseHora(strEndHour);
    std::cout << "Slots generados:\n";
    while (startHour <= endHour){
        std::cout << toStringHora(startHour) << "\n";
        startHour += std::chrono::minutes(30);
    }
    

    return 0;
}