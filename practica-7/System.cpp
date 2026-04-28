#include "System.h"

System::System(){}

void System::logIn(){}

void System::logOut(){}

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

void System::addUser(Admin &admin){
    admins.push_front(&admin);
}

void System::addUser(Medic &medic){
    medics.push_front(&medic);
}

void System::addUser(Patient &patient){
    patients.push_front(&patient);
}

void System::registerAppointment(){}

void System::cancelAppointment(){}

void System::modifyAppointment(){}

std::unique_ptr<User> System::login(sqlite3* db, int rc){ // login function

    std::string usernameToVerify, passwordToVerify;

    std::cout << "Ingrese el username: ";
    std::cin >> usernameToVerify;

    std::cout << "Ingrese la contraseña: ";
    std::cin >> passwordToVerify;

    // sql sentence
    const char* sql = "SELECT ID, USERNAME, PASSWORD, ROLE, SPECIALTY FROM USER WHERE username = ? AND password = ?;";    
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return nullptr;
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

    sqlite3_finalize(stmt);

    try
    {
        throw InvalidCredentialsError();
    }
    catch(InvalidCredentialsError &except)
    {
        std::cerr << except.what() << '\n';
    }
    
    return nullptr;
}


System::~System(){
    
}