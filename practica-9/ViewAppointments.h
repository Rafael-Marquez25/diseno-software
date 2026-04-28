#include "Command.h"
#include "System.h"

class ViewAppointments : public Command
{
private:

public:
    explicit ViewAppointments ( System * sys ) : Command ( sys ) {}

    void execute() override{
        system->showAppointments();
    }
};