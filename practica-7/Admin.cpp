#include "Admin.h"

Admin::Admin(int id, std::string role, std::string password, std::string username) 
    : User(id, role, password, username){}

void Admin::manageMedics(){

}

void Admin::manageSpecialties(){

}

void Admin::manageAgenda(){

}

void Admin::showMenu(sqlite3* db, int rc){ // Admin menu
    system("clear");
    int userSelection;
    std::cout << "=== Menu Admin ===\n" 
    <<           "1. Crear Doctor.\n"
    <<           "2. Asignar Agenda.\n"
    <<           "3. Ver Lista Doctores.\n"
    <<           "4. Ver Citas.\n"
    <<           "5. Volver.\n"
    <<           "Seleccione una opción: ";

    std::cin >> userSelection;

    switch (userSelection)
    {
    case 1:
        createMedic(db, rc);
        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        showMenu(db, rc);
        break;

    case 2:
        assignScheduleToMedic(db, rc);
        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        showMenu(db, rc);
        break;
    
    case 3:
        showMedicsList(db, rc);
        std::cout << "\nPresiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        showMenu(db, rc);
        break;

    case 4:
        std::cout << "funcionalidad aun no implementada.\n";
        break;
    
    case 5:
        return;

    default:
        std::cout << "Selecione una opccion valida. Presiona Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
        showMenu(db, rc);
    }
    
}

void Admin::showMedicsList(sqlite3* db, int rc){
    const char* sql;

    sql = "SELECT ID, USERNAME, PASSWORD, ROLE, SPECIALTY FROM USER WHERE role = 'Medic';";

    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    int id;
    std::string username;  
    std::string password;  
    std::string role;
    std::string specialty;

    std::cout << "=== Lista de Medicos ===\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        
        id = sqlite3_column_int(stmt, 0);
        username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        specialty = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        std::cout << "id: " << id << " - " << "username: " << username << " - " << "password: " << password << " - " << "role: " << role << " - " << "especialidad: " << specialty << "\n";
    }

    sqlite3_finalize(stmt);
}

void Admin::createMedic(sqlite3* db, int rc){
    showMedicsList(db, rc);

    std::string specialty;
    int id;

    std::cout << "Seleciona un medico por ID: ";
    std::cin >> id;

    if(verifyMedic(db, id) == 1){
        return;
    }

    std::cout << "Introduce su especialidad: ";
    std::cin >> specialty;

    // Sentencia preparada con parámetros
    const char* sql = "UPDATE USER SET SPECIALTY = ? WHERE ID = ?;";  // Solo cambia la del usuario 5;
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la sentencia: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Enlazar los valores
    sqlite3_bind_text(stmt, 1, specialty.c_str(), -1, SQLITE_TRANSIENT);  // Nueva contraseña
    sqlite3_bind_int(stmt, 2, id);  // ID del usuario

    // Ejecutar
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al insertar especialidad: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Especialidad asignada correctamente al medico con ID: " << id << "\n";
    }

    // Liberar
    sqlite3_finalize(stmt);

    return;
}

void Admin::assignScheduleToMedic(sqlite3* db, int rc){
    // Primero, mostrar las medicos disponibles.
    showMedicsList(db, rc);

    int medicId;
    std::string start;
    std::string end;

    std::cout << "Introduce el ID del Medico: ";
    std::cin >> medicId;

    if(verifyMedic(db, medicId)== 1){
        return;
    }

    std::cout << "Introduce la hora de inicio: ";
    std::cin >> start;

    std::cout << "Introduce la hora de fin: ";
    std::cin >> end;

    // Sentencia preparada con parámetros
    const char* sql = "INSERT INTO SCHEDULE (ID_DOCTOR, START, END) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la sentencia: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Enlazar los valores
    sqlite3_bind_int(stmt, 1, medicId);
    sqlite3_bind_text(stmt, 2, start.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, end.c_str(), -1, SQLITE_TRANSIENT);


    char ans;
    // Ejecutar
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        //std::cerr << "Error al insertar horario: " << sqlite3_errmsg(db) << std::endl;
        if (std::string(sqlite3_errmsg(db)).find("FOREIGN KEY") != std::string::npos) {
            std::cerr << "El medico con ID " << medicId << " no existe." << std::endl;
        }
        if (std::string(sqlite3_errmsg(db)).find("UNIQUE") != std::string::npos) {
            std::cerr << "El medico con ID " << medicId << " ya tiene un horario asignado. ¿Quieres actualizarlo? (s/n)"  << std::endl;
            std::cin >> ans;
            if(ans == 's'){
                updateScheduleForMedic(db, medicId, start, end);
            }
        }
    } else {
        std::cout << "Horario insertado correctamente.\n";
        std::cout << "ID del Medico: " << sqlite3_last_insert_rowid(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Admin::updateScheduleForMedic(sqlite3* db, int medicId, std::string start, std::string end) {
    
    const char* sql = "UPDATE SCHEDULE SET START = ?, END = ? WHERE ID_DOCTOR = ?;";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar actualización: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    sqlite3_bind_text(stmt, 1, start.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, end.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, medicId);
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al actualizar horario: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Horario actualizado correctamente.\n";
    }
    
    sqlite3_finalize(stmt);
}

int Admin::verifyMedic(sqlite3* db, int medicId){
    // VERIFICAR QUE EL USUARIO SEA UN MÉDICO
    const char* checkRoleSql = "SELECT ROLE FROM USER WHERE ID = ?;";
    sqlite3_stmt* checkRoleStmt;
    int rc = sqlite3_prepare_v2(db, checkRoleSql, -1, &checkRoleStmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al verificar rol: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    
    sqlite3_bind_int(checkRoleStmt, 1, medicId);
    rc = sqlite3_step(checkRoleStmt);
    
    if (rc != SQLITE_ROW) {
        std::cerr << "Error: El usuario con ID " << medicId << " no existe." << std::endl;
        sqlite3_finalize(checkRoleStmt);
        return 1;
    }
    
    std::string role = reinterpret_cast<const char*>(sqlite3_column_text(checkRoleStmt, 0));
    sqlite3_finalize(checkRoleStmt);
    
    if (role != "Medic") {
        std::cerr << "Error: El usuario con ID " << medicId 
                  << " no es un medico. Es un " << role << "." << std::endl;
        return 1;
    }
    return 0;
}

Admin::~Admin(){

}