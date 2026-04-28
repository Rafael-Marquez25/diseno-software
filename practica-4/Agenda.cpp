#include <string>
#include "Agenda.h"

Agenda::Agenda(std::string id){
    agendaId = id;
    schedule = std::make_unique<std::unique_ptr<std::string>[]>(10);
}

std::string Agenda::getId(){
    return agendaId;
}

void Agenda::setAssociatedMedic(std::string medicToAssociate){
    associatedMedic = medicToAssociate;
}

std::string Agenda::getAssociatedMedic(){
    return associatedMedic;
}