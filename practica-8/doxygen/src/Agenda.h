#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <memory>

class Agenda
{
private:
    int id;
    std::unique_ptr<std::unique_ptr<std::string>[]> schedule;
    std::string associatedMedic;
public:
    Agenda(int id);
    int getId();
    void setAssociatedMedic(std::string medicToAssociate);
    std::string getAssociatedMedic();
    ~Agenda();
};

#endif