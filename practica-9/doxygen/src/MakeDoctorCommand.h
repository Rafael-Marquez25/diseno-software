#include "Command.h"
#include "System.h"

class MakeDoctorCommand : public Command
{
private:

public:
    explicit MakeDoctorCommand ( System * sys ) : Command ( sys ) {}

    void execute() override{
        system->createMedic(system->getDb());
    }
};