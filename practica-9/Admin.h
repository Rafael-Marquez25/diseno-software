#ifndef ADMIN_H
#define ADMIN_H

#include<string>
#include <iostream>
#include <sqlite3.h>
#include "User.h"
#include "Command.h"

class Admin : public User
{
private:
    
public:
    Admin(int Id, std::string role, std::string password, std::string username, std::string specialty);
    
    std::unique_ptr<User> clone(int id, std::string role, std::string password, std::string username, std::string specialty) const{
        return std::make_unique<Admin> (id, role, password, username, specialty);
    }

    void showMenu(System *sys);

    void handleUserActions(int userSelection, System *sys);
    ~Admin();
};


#endif
