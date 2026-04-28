#include "Command.h"
#include "System.h"

class AssingSchedule : public Command
{
private:

public:
    explicit AssingSchedule ( System * sys ) : Command ( sys ) {}

    void execute() override{
        system->assignScheduleToMedic(system->getDb());
    }
};