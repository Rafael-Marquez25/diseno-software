#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    int rc;
    char *errMsg = 0;

    // Abrir la base de datos
    rc = sqlite3_open("appointment_system.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::string name;
    std::string password;
    std::string role;

    std::cout << "Introduce el nombre: ";
    std::cin >> name;

    std::cout << "Introduce la contraseña: ";
    std::cin >> password;

    std::cout << "Introduce el tipo: ";
    std::cin >> role;

    // Sentencia preparada con parámetros
    const char* sql = "INSERT INTO USER (USERNAME, PASSWORD, ROLE) VALUES (?, ?, ?);";
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

    // Ejecutar
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al insertar datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Datos insertados correctamente.\n";
    }

    // Liberar
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
