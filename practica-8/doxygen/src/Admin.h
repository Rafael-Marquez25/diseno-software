#ifndef ADMIN_H
#define ADMIN_H

#include<string>
#include <iostream>
#include <sqlite3.h>
#include "User.h"

class Admin : public User
{
private:
    
public:
    Admin(int Id, std::string role, std::string password, std::string username);
    void manageMedics();
    void manageSpecialties();
    void manageAgenda();
    void showMenu(sqlite3* db);
    void showMedicsList(sqlite3* db);
    void createMedic(sqlite3* db);
    void assignScheduleToMedic(sqlite3* db);
    void updateScheduleForMedic(sqlite3* db, int medicId, std::string start, std::string end);
    int verifyMedic(sqlite3* db, int medicId);
    ~Admin();
};


#endif
