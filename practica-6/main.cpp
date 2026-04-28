#include <iostream>
#include <string>
#include "System.h"

void printMenu(){
    std::cout << "Select an option:\n" 
    << "1. Accompany.\n"
    << "2. Show available robots.\n"
    << "3. Exit.\n"; 
}

int main(){
    System mainSystem = System(); // instance of the main system

    // instance of our robots 
    Robot robot1 = Robot(1);
    Robot robot2 = Robot(2);
    Robot robot3 = Robot(3);
    Robot robot4 = Robot(4);

    // add the robots to the system
    mainSystem.addRobot(robot1);
    mainSystem.addRobot(robot2);
    mainSystem.addRobot(robot3);
    mainSystem.addRobot(robot4);

    bool menu = true;

    while(menu){ // loop for the menu
        printMenu();
        int userSelection = 0;
        std::cin >> userSelection;

        if(userSelection < 1 || userSelection > 3) // input protection 
        {
            std::cout << "Invalid option.\n";
            continue;
        }
    
        switch (userSelection)
        {
        case 1:
            mainSystem.accompany(15); // the firts queue robot accompany for n seconds
            continue;

        case 2:
            mainSystem.printAvailableRobots(); // show all the aviable robots
            continue;

        case 3:
            menu = false; // exit the loop
            break;
        
        default:
            break;
        }
    }
    return 0;
}



