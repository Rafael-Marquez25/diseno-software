#ifndef MEDIC_H
#define MEDIC_H
#include <string>
#include <memory>
#include "Agenda.h"

class Medic
{
private:
    int id;
    std::string email;
    std::string password;
    std::unique_ptr<Agenda> medicAgenda;
    std::string medicSpecialty;
    std::string medicState;
public:
    Medic(int id, std::string specialty);
    int getId();
    void setState(std::string newState);
    std::string getState();
    void addAppointmentInfo();
    void setEmail(std::string email);
    std::string getEmail();
};

#endif