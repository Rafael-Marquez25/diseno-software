#include <iostream>
#include <string>
#include "Robot.h"

Robot::Robot(std::string id){
    idRobot = id;
}

void Robot::move(){}

std::string Robot::getId(){
    return idRobot;
}

void Robot::offerSupport(){}

void Robot::setState(bool newState){
    state = newState;
}

bool Robot::getState(){
    return state;
}

void Robot::goToCharge(){}

void Robot::validatePatientInfo(){}

void Robot::printTicket(){}

void Robot::updatePosition(Position newPosition){
    robotPosition = newPosition;
}

Position Robot::getPosition(){
    return robotPosition;
}

void Robot::associatePatient(std::string patient){
    associatedPatient = patient;
}