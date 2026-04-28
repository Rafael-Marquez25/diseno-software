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
#include "CustomExceptions.h"

class System
{
private:
    std::queue<Robot*> robots; // queue for the robots
    sqlite3* db;

public:
    System();
    
    void delRobot(Robot& robot);
    void addRobot(Robot& robot); // to add one robot to the queue
    Robot* getRobotFront(); // return the first elemtent of queue 
    void printAvailableRobots(); // prints all available robots
    void accompany(int time); // asing a robot to a accompany

    std::unique_ptr<User> login(sqlite3* db); // login function 

    sqlite3* getDb() const;
    void registerNewUser(sqlite3* db);
    void openDb();

    ~System();
};

#endif