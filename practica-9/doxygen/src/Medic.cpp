#include "Medic.h"

Medic::Medic(int id, std::string role, std::string password, std::string username, std::string specialty) 
    : User(id, role, password, username){
        this->specialty = specialty;
    }

void Medic::setState(std::string newState){
    medicState = newState;
}

std::string Medic::getState(){
    return medicState;
}

std::string Medic::getSpecialty() const{
    return specialty;
}

void Medic::addAppointmentInfo(){}

void Medic::showMenu() const {
    system("clear");
    int userSelection;
    std::cout << "=== Menu Medic ===\n" 
    <<           "1. Confirmar Asistencia.\n"
    <<           "2. Modificar Agenda.\n"
    <<           "3. Añadir Notas a Cita.\n"
    <<           "4. Volver.\n"
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
        std::cout << "Funcion no implementada. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu();
        break;

        break;

    case 4:
        return;
        
    default:
        std::cout << "Selecione una opccion valida. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu();
        break;
    }
}

Medic::~Medic(){

}