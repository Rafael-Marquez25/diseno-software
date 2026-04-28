#include <string>
#include "Agenda.h"

Agenda::Agenda(int id){
    id = id;
    schedule = std::make_unique<std::unique_ptr<std::string>[]>(10);
}

int Agenda::getId(){
    return id;
}

void Agenda::setAssociatedMedic(std::string medicToAssociate){
    associatedMedic = medicToAssociate;
}

std::string Agenda::getAssociatedMedic(){
    return associatedMedic;
}