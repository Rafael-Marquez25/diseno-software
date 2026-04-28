#include "System.h"

System::System(){}

void System::logIn(){}

void System::logOut(){}

void System::addPatient(){}

void System::addMedic(){}

void System::addAdmin(){}

void System::addRobot(Robot &robot){
    robots.push(&robot);
}

void System::delRobot(Robot &robot){

}

Robot* System::getRobotFront(){
    if (robots.empty()) {
        std::cout << "No robots available";
    }
    return robots.front();
}

void System::printAvailableRobots(){
    if (robots.front()->getState() != "Libre") {
        std::cout << "No robots available.\n";
        return;
    }
    
    std::queue<Robot*> temp = robots; // Copia
    
    while (!temp.empty()) {
        Robot* robot = temp.front();  // Obtener el robot
        
        if (robot->getState() == "Libre") {
            std::cout << *robot << "\n";  
        }
        temp.pop();  
    }
}

void System::accompany(int time){
    if(robots.front()->getState() == "Libre"){
        Robot* tempRobot = robots.front();
        robots.pop();
        tempRobot->dummy(time);
        robots.push(tempRobot);}
    
    else{std::cout << "There are no free robots, wait until one is available and select an option.\n";}
}

void System::delPatient(){}

void System::delMedic(){}

void System::delAdmin(){}

void System::registerAppointment(){}

void System::cancelAppointment(){}

void System::modifyAppointment(){}
