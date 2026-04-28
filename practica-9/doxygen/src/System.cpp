#include "System.h"

System* System::singleSystem = nullptr;

System* System::getTheSystem(){
    if (singleSystem == nullptr){
        singleSystem = new System ();
    }
    else{
        std::cout << "Error: trying to get another instance of a System singleton class!\n";
    }

    return singleSystem;
}

void System::openDb(){
    int rc;

    // Abrir la base de datos
    rc = sqlite3_open("appointment_system.db", &db);
    if (rc) {
        throw DatabaseError(sqlite3_errmsg(db));    
    }

    const char* pragma_sql = "PRAGMA foreing_keys = ON;";
    
    if (rc !=SQLITE_OK) {
        throw DatabaseError(sqlite3_errmsg(db));
    }

    rc = sqlite3_exec(db, pragma_sql, 0, 0, 0);
}

void System::addRobot(Robot &robot){
    robots.push(&robot);
}

Robot* System::getRobotFront(){
    if (robots.empty()) {
        std::cout << "No robots available";
    }
    return robots.front();
}

void System::printAvailableRobots(){
    if (robots.front()->getState() != "Libre") {
        std::cout << "No robots available.\n";
        return;
    }
    
    std::queue<Robot*> temp = robots; // Copia
    
    while (!temp.empty()) {
        Robot* robot = temp.front();  // Obtener el robot
        
        if (robot->getState() == "Libre") {
            std::cout << *robot << "\n";  
        }
        temp.pop();  
    }
}

void System::accompany(int time){
    if(robots.front()->getState() == "Libre"){
        Robot* tempRobot = robots.front();
        robots.pop();
        tempRobot->dummy(time);
        robots.push(tempRobot);}
    
    else{std::cout << "There are no free robots, wait until one is available and select an option.\n";}
}

std::unique_ptr<User> System::login(sqlite3* db){ // login function

    std::string usernameToVerify, passwordToVerify;

    std::cout << "Ingrese el username: ";
    std::cin >> usernameToVerify;

    std::cout << "Ingrese la contraseña: ";
    std::cin >> passwordToVerify;

    // sql sentence
    const char* sql = "SELECT ID, USERNAME, PASSWORD, ROLE, SPECIALTY FROM USER WHERE username = ? AND password = ?;";    
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw DatabaseError(sqlite3_errmsg(db));
    }

    // link the values
    sqlite3_bind_text(stmt, 1, usernameToVerify.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, passwordToVerify.c_str(), -1, SQLITE_TRANSIENT);

    int id;
    std::string username;  
    std::string password;  
    std::string role;
    std::string specialty;

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
        username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        specialty = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        return makeUser(id, role, username, password, specialty);
    }
    else{
        throw InvalidCredentialsError();
    }

    sqlite3_finalize(stmt); 
    return nullptr;
}

sqlite3* System::getDb() const{
    return db;
}

void System::registerNewUser(sqlite3* db) { // Function to register a new user, requires de bd
    std::string name;
    std::string password;
    std::string role;
    std::string specialty = "";

    std::cout << "Introduce el usuario: ";
    std::cin >> name;

    std::cout << "Introduce la contraseña: ";
    std::cin >> password;

    bool validRole = false;

    while(!validRole) {
        std::cout << "Introduce el tipo (Patient, Medic o Admin): ";
        std::cin >> role;
        
        if(role == "Patient" || role == "Medic" || role == "Admin") {
            validRole = true;
        } else {
            std::cout << "Rol inválido. Debe ser Patient, Medic o Admin.\n";
        }
    }

    // Sentencia preparada con parámetros
    const char* sql = "INSERT INTO USER (USERNAME, PASSWORD, ROLE, SPECIALTY) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        throw DatabaseError(sqlite3_errmsg(db));
    }

    // Enlazar los valores
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, specialty.c_str(), -1, SQLITE_TRANSIENT);

    // Ejecutar
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        throw DatabaseError(sqlite3_errmsg(db));
    } else {
        std::cout << "Datos insertados correctamente.\n";
    }

    // Liberar
    sqlite3_finalize(stmt);
}

System::~System(){
    sqlite3_close(db); // close the db
}



std::unique_ptr<User> System::makeUser (int id, std::string role, std::string password, std::string username, std::string specialty) {
    std::map<std::string, User*> userType = {
    {"Admin", new Admin(0, "", "", "", "")},
    {"Medic", new Medic(0, "", "", "", "")},
    {"Patient", new Patient(0, "", "", "", "")}
    };
    return userType[role]->clone(id, role, password, username, specialty);
}

void System::showMedicsList(sqlite3* db){
    const char* sql;

    sql = "SELECT ID, USERNAME, PASSWORD, ROLE, SPECIALTY FROM USER WHERE role = 'Medic';";

    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
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

void System::createMedic(sqlite3* db){
    showMedicsList(db);

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

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
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

void System::assignScheduleToMedic(sqlite3* db){
    // Primero, mostrar las medicos disponibles.
    showMedicsList(db);

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

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
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

void System::updateScheduleForMedic(sqlite3* db, int medicId, std::string start, std::string end) {
    
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

int System::verifyMedic(sqlite3* db, int medicId){
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

void System::showAppointments(){
    std::cout << "funcion no implementada\n";
}
