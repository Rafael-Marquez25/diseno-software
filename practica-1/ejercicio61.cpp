/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 61.
*/

#include <iostream>

int main(){
    int numUsr;

    std::cout << "Intruce el numero a calcular su factorial: ";
    std::cin >> numUsr;
    int numFact = numUsr;

    if(numUsr == 0){
        std::cout << "El factorial de " << numUsr << " es: 1 " << "\n";
    }

    int i = numUsr - 1;
    while(i > 0){
        numFact *= i;
        i--;
    }

    std::cout << "El factorial de " << numUsr << " es: " << numFact << "\n";

    return 0;
}

