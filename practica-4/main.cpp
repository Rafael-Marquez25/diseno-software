#include <iostream>
#include <string>
#include "Robot.h"
#include "Patient.h"
#include "Medic.h"
#include "Admin.h"
#include "Agenda.h"
#include "System.h"

int main(){

    System hospitalsystem = System();

    Robot robot1 = Robot("R1");
    std::cout << robot1.getId() << std::endl;

    Patient patient1 = Patient("P1");
    std::cout << patient1.getId() << std::endl;

    Medic medic1 = Medic("M1", "Cirujano");
    std::cout << medic1.getId() << std::endl;

    Admin admin1 = Admin("A1");
    std::cout << admin1.getId() << std::endl;

    Agenda agenda1 = Agenda("AG1");
    std::cout << agenda1.getId() << std::endl;

    return 0;
}
