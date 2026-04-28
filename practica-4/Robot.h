#ifndef ROBOT_H
#define ROBOT_H

#include<string>

struct Position{
    int x;
    int y;
};


class Robot{

    private:
        std::string idRobot;
        Position robotPosition;
        std::string associatedPatient;
        bool state;

    public:
        Robot(std::string idRobot);
        void move();
        std::string getId();
        void offerSupport();
        void setState(bool newState);
        bool getState();
        void goToCharge();
        void validatePatientInfo();
        void printTicket();
        void updatePosition(Position newPosition);
        Position getPosition();
        void associatePatient(std::string patient);
};

#endif