#include <string>
#include "Appointment.h"

Appointment::Appointment(int id, std::string date,std::string patient, std::string medic, std::string location){
    id = id;
    appointmentDate = date;
    associatedPatient = patient;
    associatedMedic = medic;
    appoinmentLocation = location;
}

int Appointment::getId(){
return id;
}

std::string Appointment::getDate(){
    return appointmentDate;
}

std::string Appointment::getAssociatedPatient(){
    return associatedPatient;
}

std::string Appointment::getAssociatedMedic(){
    return associatedMedic;
}

std::string Appointment::getAppointmentLocation(){
    return appoinmentLocation;
}

void Appointment::changeAppointmentLocation(std::string newLocation){
    appoinmentLocation = newLocation;
}

void Appointment::setAppointmentState(std::string newState){
    appointmentState = newState;
}

Appointment::~Appointment(){
    
}