/*
Autor: Rafael Márquez
Dia: 19/9/25
Objetivo: Practica 1, ejercicio 7.
*/

#include <iostream>
#include <ctime>

int ramdomNum(){
    srand(time(0));
    int num = rand() % 3 + 1;
    std::cout << num << "\n";
    return num;
}

int roundGenerator(char playerChoice){ // funcion para empezar una ronda, retorna el valor del ganador
    int playerValue;
    int computerValue = ramdomNum();

    if (playerChoice == 'r'){
        playerValue = 1;
    } else if (playerChoice == 'p'){
        playerValue = 2;
    }
    else{
        playerValue = 3;
    }

    int result = (playerValue - computerValue + 3) % 3;
    if (result == 0){
        std::cout << "It's a tie\n";
    }
    else if (result == 1){
        std::cout << "Player wins.\n";
    }
    else{
        std::cout << "Computer wins.\n";
    }

    return result;
}

int main(){
    char playerChoice;
    int playerPoints = 0;
    int computerPoints = 0;

    for(int i = 0; i < 3; i++){
        std::cout << "Round " << i + 1 <<". Introduce r, p, o s: ";
        std::cin >> playerChoice;
        int roundResult = roundGenerator(playerChoice);
        if (roundResult == 0){
            continue;
        } 
        else if(roundResult == 1){
            playerPoints++;
        }
        else{
            computerPoints++;
        }
    }
    
    if(playerPoints == computerPoints){
        std::cout << "The game ended in a tie.\n";
    }
    else if (playerPoints > computerPoints){
        std::cout << "Player wins the game.\n";
    }
    else{
        std::cout << "Computer wins the game.\n";
    }

    return 0;
}