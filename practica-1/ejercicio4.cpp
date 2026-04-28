/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 2.
*/

#include <iostream>

int main(){
    int numPisos = 0;
    int numAst = 1;

    std::cout << "Intruce el numero de pisos: ";
    std::cin >> numPisos;
    int spaces = numPisos - 1;

    for(int i = 0; i < numPisos; i++){
        for(int i = spaces; i > 0; i--){
                std::cout << " ";
            }
            

        for(int i = 0; i < numAst; i++){
            std::cout << "*";
        }

        std::cout << "\n";
        numAst += 2;
        spaces--;
    }

    return 0;
}