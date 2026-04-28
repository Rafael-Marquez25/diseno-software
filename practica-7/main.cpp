#include <iostream>
#include <string>
#include <sqlite3.h>
#include "System.h"

void mainMenu(){
    std::cout << "=== Plataforma gestión de citas ===\n" 
    <<           "1. Registrar nuevo usuario.\n"
    <<           "2. Iniciar Sesión.\n"
    <<           "3. Salir.\n"
    <<           "Seleccione una opción: ";
}

int registerNewUser(sqlite3* db, int rc) { // Function to register a new user, requires de bd and rc in the parameters
    std::string name;
    std::string password;
    std::string role;
    std::string specialty = "";

    std::cout << "Introduce el usuario: ";
    std::cin >> name;

    std::cout << "Introduce la contraseña: ";
    std::cin >> password;

    std::cout << "Introduce el tipo (Patient, Medic o Admin): ";
    std::cin >> role;

    // Sentencia preparada con parámetros
    const char* sql = "INSERT INTO USER (USERNAME, PASSWORD, ROLE, SPECIALTY) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la sentencia: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Enlazar los valores
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, specialty.c_str(), -1, SQLITE_TRANSIENT);

    // Ejecutar
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al insertar datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Datos insertados correctamente.\n";
    }

    // Liberar
    sqlite3_finalize(stmt);
    return 0;
}

int main(){ // main
    System mainSystem = System(); // instance of the main system of the hospital
    bool menu = true; // bool for the logic of the loop

    sqlite3* db; // pointer to the db
    int rc;

    // Abrir la base de datos
    rc = sqlite3_open("appointment_system.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    const char* pragma_sql = "PRAGMA foreing_keys = ON;"; 

    rc = sqlite3_exec(db, pragma_sql, 0, 0, 0);

    if (rc !=SQLITE_OK) {
        std::cerr << "Error al activar las FK: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    while(menu){ // loop for the menu
        system("clear");
        mainMenu();
        int userSelection = 0;
        std::cin >> userSelection;

        switch (userSelection)
        {
        case 1:{ // option to register a new user
            system("clear");
            registerNewUser(db, rc); 
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
            break;
        }
    
        case 2:{ // option to login
            std::unique_ptr<User> user = mainSystem.login(db, rc);

            if (user) {
                std::cout << "Login exitoso. Rol: " << user->getRole() << "\n";
                
                if (user->getRole() == "Admin") {
                    std::cout << "Administrador\n";
                    Admin *a = dynamic_cast <Admin*>(user.get());
                    a->showMenu(db, rc);
                    //delete a;
                    break;

                } else if (user->getRole() == "Medic") {
                    Medic *d = dynamic_cast <Medic*>(user.get());
                    std::cout << "Especialidad: " << d->getSpecialty() << "\n";
                    d->showMenu();
                    //delete d;
                    break;

                } else if (user->getRole() == "Patient") {
                    Patient *p = dynamic_cast <Patient*>(user.get());
                    std::cout << "Paciente: " << p->getUsername() << " ||" << "\n";
                    p->showMenu();
                    //delete p;
                    break;
                }
                else {
                std::cout << "Usuario o contraseña incorrectos\n";
                }
            }
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore();
            std::cin.get();

            continue;
            break;
        }

        case 3:{ // option to exit
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
    sqlite3_close(db); // close the db
}

// Prueba de dummy de la anterior practica.

// int main(){
//     System mainSystem = System(); // instance of the main system

//     // instance of our robots 
//     Robot robot1 = Robot(1);
//     Robot robot2 = Robot(2);
//     Robot robot3 = Robot(3);
//     Robot robot4 = Robot(4);

//     // add the robots to the system
//     mainSystem.addRobot(robot1);
//     mainSystem.addRobot(robot2);
//     mainSystem.addRobot(robot3);
//     mainSystem.addRobot(robot4);

//     bool menu = true;

//     while(menu){ // loop for the menu
//         printMenu();
//         int userSelection = 0;
//         std::cin >> userSelection;

//         if(userSelection < 1 || userSelection > 3) // input protection 
//         {
//             std::cout << "Invalid option.\n";
//             continue;
//         }
    
//         switch (userSelection)
//         {
//         case 1:
//             mainSystem.accompany(15); // the firts queue robot accompany for n seconds
//             continue;

//         case 2:
//             mainSystem.printAvailableRobots(); // show all the aviable robots
//             continue;

//         case 3:
//             menu = false; // exit the loop
//             break;
        
//         default:
//             break;
//         }
//     }
//     return 0;
// }



