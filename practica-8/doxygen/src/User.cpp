#include "User.h"

User::User(int id, std::string role, std::string password, std::string username){
    this->id = id;
    this->role = role;
    this->password = password;
    this->username = username;
}

int User::getId() const{
    return id;
}

std::string User::getRole() const {
    return role;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getUsername() const {
    return username;
}

User::~User(){
    
}