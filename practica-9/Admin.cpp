#include "Admin.h"
#include <map>
#include "MakeDoctorCommand.h"
#include "AssingSchedule.h"
#include "ViewDoctorList.h"
#include "ViewAppointments.h"

Admin::Admin(int id, std::string role, std::string password, std::string username, std::string specialty) 
    : User(id, role, password, username){}


void Admin::showMenu(System *sys){ // Admin menu
    bool menu = true;

    while(menu){
        
        system("clear");
        std::cout << "=== Menu Admin ===\n" 
        <<           "1. Crear Doctor.\n"
        <<           "2. Asignar Agenda.\n"
        <<           "3. Ver Lista Doctores.\n"
        <<           "4. Ver Citas.\n"
        <<           "5. Volver.\n"
        <<           "Seleccione una opción: ";
        int userSelection = 0;
        std::cin >> userSelection; 
        
        if(userSelection == 5){
            menu = false;
        }
        else if(userSelection > 0 && userSelection < 5){
            handleUserActions(userSelection, sys);
            std::cout << "Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
        else{
            std::cout << "Opción inválida. Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            continue;
        }

    }
}

void Admin::handleUserActions(int userSelection, System *sys){
    std::map<int, Command*> commandRegistry = {
    {1, new MakeDoctorCommand(sys)},
    {2, new AssingSchedule(sys)},
    {3, new ViewDoctorList(sys)},
    {4, new ViewAppointments(sys)},};

    commandRegistry[userSelection]->execute();
}


Admin::~Admin(){

}