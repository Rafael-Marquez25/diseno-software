#include <string>
#include "Medic.h"

Medic::Medic(int id, std::string specialty){
    id = id;
    medicSpecialty = specialty;
}

int Medic::getId(){
    return id;
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