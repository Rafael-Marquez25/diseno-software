#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Robot.h"

Robot::Robot(int id){
    this->id = id;
    state = "Libre";
    lastActivity = std::chrono::steady_clock::now();
}

void Robot::move(){}

int Robot::getId() const {
    return id;
}

void Robot::offerSupport(){}

void Robot::setState(bool newState){
    state = newState;
}

std::string Robot::getState() const{
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

void Robot::dummy(int segundos) {
    //Acá creo un hilo para simular la tarea sin bloquear el hilo principal
    std::thread([this, segundos]() {
        {
            //Acá se protege el acceso al estado con mutex
            std::lock_guard<std::mutex> lock(mtx);
            state = "Ocupado";
            std::cout << "[Robot " << id << "] acompañado por " << segundos << " segundos. \n";
        }

        // Esta linea simula el tiempo de acompañamiento del robot al paciente
        std::this_thread::sleep_for(std::chrono::seconds(segundos));
        {
        //Acá protege el acceso al estado para cambiar el estado
            std::lock_guard<std::mutex> lock(mtx);
            state = "Libre";
            lastActivity = std::chrono::steady_clock::now();
            std::cout << "[Robot " << id << "] Finalizó. Estado: Libre. \n";
        }
    }).detach(); //hilo separado, no bloquea.
}

std::ostream &operator<<(std::ostream &output, const Robot &robot){
    // Format [id - State - last activity]
    output << "[Robot " << robot.getId() << " - " << "State: " << robot.getState() << " - " << "Last Activity: " << robot.getLastActivityTime() << "s]";
    return output; 
}

double Robot::getLastActivityTime() const {
    std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - lastActivity;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() / 1000.0;
}