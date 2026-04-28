#include <string>
#include "Medic.h"

Medic::Medic(std::string id, std::string specialty){
    medicId = id;
    medicSpecialty = specialty;
}

std::string Medic::getId(){
    return medicId;
}

void Medic::setState(std::string newState){
    medicState = newState;
}

std::string Medic::getState(){
    return medicState;
}

void Medic::addAppointmentInfo(){}

void Medic::setEmail(std::string email){
    this->email = email;
}

std::string Medic::getEmail(){
    return email;
}