#ifndef MEDIC_H
#define MEDIC_H
#include <string>
#include <memory>
#include "Agenda.h"

class Medic
{
private:
    std::string medicId;
    std::string email;
    std::string password;
    std::unique_ptr<Agenda> medicAgenda;
    std::string medicSpecialty;
    std::string medicState;
public:
    Medic(std::string id, std::string specialty);
    std::string getId();
    void setState(std::string newState);
    std::string getState();
    void addAppointmentInfo();
    void setEmail(std::string email);
    std::string getEmail();
};

#endif