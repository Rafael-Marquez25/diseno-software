#ifndef SYSTEM_H
#define SYSTEM_H
#include <list>
#include <queue>
#include <iostream>
#include <sqlite3.h>
#include "Patient.h"
#include "Medic.h"
#include "Admin.h"
#include "Robot.h"
#include "CustomExepctions.h"

class System
{
private:
    std::list<Patient*> patients;
    std::list<Medic*> medics;
    std::list<Admin*> admins;
    std::queue<Robot*> robots; // queue for the robots
public:
    System();
    void logIn();
    void logOut();

    void addUser(Admin &admin);
    void addUser(Medic &medic);
    void addUser(Patient &patient);

    void delAdmin();

    void delPatient();
    void delMedic();
    
    void registerAppointment();
    void cancelAppointment();
    void modifyAppointment();

    void delRobot(Robot& robot);
    void addRobot(Robot& robot); // to add one robot to the queue
    Robot* getRobotFront(); // return the first elemtent of queue 
    void printAvailableRobots(); // prints all available robots
    void accompany(int time); // asing a robot to a accompany

    std::unique_ptr<User> login(sqlite3* db, int rc); // login function 

    ~System();
};

#endif