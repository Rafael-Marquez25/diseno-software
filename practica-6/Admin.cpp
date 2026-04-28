#include<string>
#include "Admin.h"

Admin::Admin(int id){
    id = id;
}

int Admin::getId(){
    return id;
}

void Admin::manageMedics(){

}

void Admin::manageSpecialties(){

}

void Admin::manageAgenda(){

}

void Admin::setEmail(std::string email){
    this->email = email;
}

std::string Admin::getEmail(){
    return email;
}
