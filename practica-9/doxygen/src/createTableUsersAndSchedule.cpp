#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    int exit = 0;

    // open db
    exit = sqlite3_open("appointment_system.db", &db);

    if (exit) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    } else {
        std::cout << "Base de datos abierta correctamente." << std::endl;
    }

    std::string enableFK = "PRAGMA foreign_keys = ON;";
    char* mensajeError;
    exit = sqlite3_exec(db, enableFK.c_str(), NULL, 0, &mensajeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error al activar foreign keys: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }

    // User table
    std::string sqlUser = "CREATE TABLE IF NOT EXISTS USER("
                              "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "USERNAME TEXT NOT NULL UNIQUE, "
                              "PASSWORD TEXT NOT NULL, "
                              "ROLE TEXT NOT NULL, "
                              "SPECIALTY TEXT NOT NULL, "
                              "CHECK(ROLE IN ('Admin', 'Medic', 'Patient')));";

    exit = sqlite3_exec(db, sqlUser.c_str(), NULL, 0, &mensajeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error al crear la tabla USER: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    } else {
        std::cout << "Tabla USER creada correctamente." << std::endl;
    }

    // Schedule table
    std::string sqlschedule = "CREATE TABLE IF NOT EXISTS SCHEDULE("
                              "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "ID_DOCTOR INTEGER NOT NULL UNIQUE, "
                              "START TEXT NOT NULL, "
                              "END TEXT NOT NULL, "
                              "FOREIGN KEY (ID_DOCTOR) REFERENCES USERS (ID));";

    exit = sqlite3_exec(db, sqlschedule.c_str(), NULL, 0, &mensajeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error al crear la tabla SCHEDULE: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    } else {
        std::cout << "Tabla SCHEDULE creada correctamente." << std::endl;
    }

    sqlite3_close(db); // close db

    return 0;
}