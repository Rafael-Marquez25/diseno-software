#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <chrono>
#include <mutex>

struct Position{
    int x;
    int y;
};

class Robot{

    friend std::ostream &operator<<(std::ostream &, const Robot &); // << overload

    private:
        int id;
        Position robotPosition;
        std::string associatedPatient;
        std::string state;
        std::chrono::steady_clock::time_point lastActivity; 
        std::mutex mtx;

    public:
        Robot(int id); // constructor of robot
        void move();
        int getId() const; // return the id / NOTE: conts to use in the << operator
        void offerSupport();
        void setState(bool newState);
        std::string getState() const; // return the state / NOTE: conts to use in the << operator
        void goToCharge();
        void validatePatientInfo();
        void printTicket();
        void updatePosition(Position newPosition);
        Position getPosition();
        void associatePatient(std::string patient);
        void dummy(int seconds); // Simulate the accompany for n seconds
        double getLastActivityTime() const; // return the time since last activity
};

#endif