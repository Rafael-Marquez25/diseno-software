#ifndef SYSTEM_H
#define SYSTEM_H
#include <list>
#include <queue>
#include <iostream>
#include "Patient.h"
#include "Medic.h"
#include "Admin.h"
#include "Robot.h"

class System
{
private:
    std::list<Patient> patients;
    std::list<Medic> medics;
    std::list<Admin> admins;
    std::queue<Robot*> robots; // queue for the robots
public:
    System();
    void logIn();
    void logOut();
    void addPatient();
    void addMedic();
    void addAdmin();
    void delPatient();
    void delMedic();
    void delAdmin();
    void registerAppointment();
    void cancelAppointment();
    void modifyAppointment();

    void delRobot(Robot& robot);
    void addRobot(Robot& robot); // to add one robot to the queue
    Robot* getRobotFront(); // return the first elemtent of queue 
    void printAvailableRobots(); // prints all available robots
    void accompany(int time); // asing a robot to a accompany
};

#endif