#include <iostream>
#include <string>
#include <sqlite3.h>
#include "System.h"

void mainMenu(){
    std::cout << "=== Plataforma gestión de citas ===\n" 
    <<           "1. Registrar nuevo usuario.\n"
    <<           "2. Iniciar Sesión.\n"
    <<           "3. Acompañamiento de Robots.\n"
    <<           "4. Salir.\n"
    <<           "Seleccione una opción: ";
}

void printMenu(){
    std::cout << "\nSeleciona una opcción:\n" 
    << "1. Acompañar.\n"
    << "2. Mostrar robots libres.\n"
    << "3. Volver.\n"; 
}

void robotAcompanySim(System &mainSystem){

    // instance of our robots 
    Robot robot1 = Robot(1);
    Robot robot2 = Robot(2);

    Robot robot3 = Robot(3);
    Robot robot4 = Robot(4);

    // add the robots to the system
    mainSystem.addRobot(robot1);
    mainSystem.addRobot(robot2);
    mainSystem.addRobot(robot3);
    mainSystem.addRobot(robot4);

    bool menu = true;

    while(menu){ // loop for the menu
        printMenu();
        int userSelection = 0;
        std::cin >> userSelection;
    
        switch (userSelection)
        {
        case 1:
            mainSystem.accompany(15); // the firts queue robot accompany for n seconds
            continue;

        case 2:
            mainSystem.printAvailableRobots(); // show all the aviable robots
            continue;

        case 3:
            menu = false; // exit the loop
            return;
        
        default:
            std::cout << "\nOpcion invalida. Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}


int main(){ // main
    System* mainSystem = System::getTheSystem();

    try{
        mainSystem->openDb();
    }
    catch(DatabaseError &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    bool menu = true; // bool for the logic of the loop


    while(menu){ // loop for the menu
        system("clear");
        mainMenu();
        int userSelection = 0;
        std::cin >> userSelection;

        switch (userSelection)
        {
        case 1:{ // option to register a new user
            system("clear");
            mainSystem->registerNewUser(mainSystem->getDb()); 
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
    
        case 2:{ // option to login
            try
            {
                std::unique_ptr<User> user = mainSystem->login(mainSystem->getDb());
                if (user) {
                std::cout << "Login exitoso. Rol: " << user->getRole() << "\n";

                std::string role = user->getRole();
                
                if (role == "Admin") {
                    std::cout << "Administrador\n";
                    Admin *a = dynamic_cast <Admin*>(user.get());
                    a->showMenu(mainSystem);
                    break;

                } else if (role == "Medic") {
                    Medic *d = dynamic_cast <Medic*>(user.get());
                    std::cout << "Especialidad: " << d->getSpecialty() << "\n";
                    d->showMenu();
                    break;

                } else if (role == "Patient") {
                    Patient *p = dynamic_cast <Patient*>(user.get());
                    std::cout << "Paciente: " << p->getUsername() << " ||" << "\n";
                    p->showMenu();
                    break;
                }
            }
            }catch(InvalidCredentialsError &e){
                std::cerr << "Error: " << e.what() << '\n';
            }     
            catch(DatabaseError &e){
                std::cerr << "Error: " << e.what() << '\n';
            }       

            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            continue;
            break;
            }

        case 3:{
            robotAcompanySim(*mainSystem);
            break;
        }
            
        case 4:{ // option to exit
            menu = false;
            break;
        }
        default: // default wrong option
            std::cout << "Opción inválida. Presiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
    }
    
    return 0;
}


