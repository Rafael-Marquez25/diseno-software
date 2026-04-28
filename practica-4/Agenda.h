#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <memory>

class Agenda
{
private:
    std::string agendaId;
    std::unique_ptr<std::unique_ptr<std::string>[]> schedule;
    std::string associatedMedic;
public:
    Agenda(std::string id);
    std::string getId();
    void setAssociatedMedic(std::string medicToAssociate);
    std::string getAssociatedMedic();
};

#endif