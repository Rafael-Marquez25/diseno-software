#include "System.h"

System::System(){ // pointer to the db
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

void System::delRobot(Robot &robot){

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

        if (role == "Admin"){
            std::unique_ptr<Admin> user = std::make_unique<Admin>(id, role, password, username);
            std::cout << "Username y Contraseña Correctos.\n";
            return user;
        }

        else if(role == "Medic"){
            std::unique_ptr<Medic> user = std::make_unique<Medic>(id, role, password, username, specialty);
            std::cout << "Username y Contraseña Correctos.\n";
            return user;
        }

        else if(role == "Patient"){
            std::unique_ptr<Patient> user = std::make_unique<Patient>(id, role, password, username);
            std::cout << "Username y Contraseña Correctos.\n";
            return user;
        }
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

    std::cout << "Introduce el tipo (Patient, Medic o Admin): ";
    std::cin >> role;

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