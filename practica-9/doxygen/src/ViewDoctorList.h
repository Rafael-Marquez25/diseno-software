#include "Command.h"
#include "System.h"

class ViewDoctorList : public Command
{
private:

public:
    explicit ViewDoctorList ( System * sys ) : Command ( sys ) {}

    void execute() override{
        system->showMedicsList(system->getDb());
    }
};