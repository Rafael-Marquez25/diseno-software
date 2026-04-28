#ifndef MEDIC_H
#define MEDIC_H
#include <string>
#include <memory>
#include <iostream>
#include "Agenda.h"
#include "User.h"

class Medic : public User
{
private:
    std::unique_ptr<Agenda> medicAgenda;
    std::string specialty;
    std::string medicState;
public:
    Medic(int Id, std::string role, std::string password, std::string username, std::string specialty);
    std::unique_ptr<User> clone(int id, std::string role, std::string password, std::string username, std::string specialty) const{
        return std::make_unique<Medic> (id, role, password, username, specialty);
    }

    void setState(std::string newState);
    std::string getState();
    void addAppointmentInfo();
    std::string getSpecialty() const;
    void showMenu() const;
    ~Medic();
};

#endif