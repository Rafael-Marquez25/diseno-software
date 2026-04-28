#include<string>
#include "Admin.h"

Admin::Admin(std::string adminId){
    this->adminId = adminId;
}

std::string Admin::getId(){
    return adminId;
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
