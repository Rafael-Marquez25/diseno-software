#include <iostream>
#include "Patient.h"

Patient::Patient(int id){
    id = id;
    appointmentHistory = std::make_unique<std::unique_ptr<Appointment>[]>(10);
}

int Patient::getId(){
    return id;
}

std::string Patient::getAppointmentHistoryToString(){
    std::string appointmentHistoryString;
    for (size_t i = 0; i < 10; i++) {
        if(appointmentHistory[i] != nullptr){
            appointmentHistoryString += appointmentHistory[i]->getId() + "\n";
        }
    }
    return appointmentHistoryString;
}

void Patient::addAppointmentToHistory(std::unique_ptr<Appointment> appointmentToAdd){
    for (size_t i = 0; i < 10; i++) {
        if (!appointmentHistory[i]) {  // nullptr significa libre
            appointmentHistory[i] = std::move(appointmentToAdd);  // mover
            break; // solo agregamos una vez
        }
    }
}

void Patient::setCurrentAppointment(std::unique_ptr<Appointment> appointment) {
    currentAppointment = std::move(appointment);
}

void Patient::setEmail(std::string email){
    this->email = email;
}

std::string Patient::getEmail(){
    return email;
}

