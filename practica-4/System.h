#ifndef SYSTEM_H
#define SYSTEM_H
#include "Patient.h"
#include "Medic.h"
#include "Admin.h"

class System
{
private:
    std::unique_ptr<std::unique_ptr<Patient>[]> registeredPatients;
    std::unique_ptr<std::unique_ptr<Medic>[]> registeredMedics;
    std::unique_ptr<std::unique_ptr<Admin>[]> registeredAdmins;
public:
    System();
    void logIn();
    void logOut();
    void registerPatient();
    void registerMedic();
    void registerAdmin();
    void deletePatient();
    void deleteMedic();
    void deleteAdmin();
    void registerAppointment();
    void cancelAppointment();
    void modifyAppointment();
};

#endif