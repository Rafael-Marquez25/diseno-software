/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 2.
*/
#include <iostream>
#include <ctime>

int main(){
    srand(time(0));
    int ramdomNum = rand() % 100 + 1;
    int usrNum;
    bool guessNum = true;

    std::cout << ramdomNum << "\n";

    while(guessNum){
        std::cout << "Intruduce un numero: ";
        std::cin >> usrNum;

        if(usrNum == ramdomNum){
            std::cout << "Has acertado\n";
            guessNum = false;
        }
        else if(usrNum < ramdomNum){
            std::cout << "Tu numero es menor\n";
        }
        else{
            std::cout << "Tu numero es mayor\n";
        }
    }

    return 0;
}