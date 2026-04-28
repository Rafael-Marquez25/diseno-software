#include <iostream>
#include "Patient.h"

Patient::Patient(int id, std::string role, std::string password, std::string username, std::string specialty) 
    : User(id, role, password, username){
}


void Patient::addAppointmentToHistory(Appointment &appointment){
    appointmentHistory.push_back(appointment);
}

void Patient::setCurrentAppointment(std::unique_ptr<Appointment> appointment) {
    currentAppointment = std::move(appointment);
}

void Patient::showMenu() const {
    system("clear");
    int userSelection;
    std::cout << "=== Menu Patient ===\n" 
    <<           "1. Solicitar Cita.\n"
    <<           "2. Ver Mis Citas.\n"
    <<           "3. Volver.\n"
    <<           "Seleccione una opción: ";

    std::cin >> userSelection;

    switch (userSelection)
    {
    case 1:
        std::cout << "Funcion no implementada. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu();
        break;

    case 2:
        std::cout << "Funcion no implementada. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu();

        break;

    case 3:
        return;
        
    default:
        std::cout << "Selecione una opccion valida. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu();
        break;
    }
}

Patient::~Patient(){

}