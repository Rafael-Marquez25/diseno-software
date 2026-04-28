/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 6.2.
*/

#include <iostream>

double factorial(int numFact){
    if(numFact == 0){
        return 1;
    }

    int i = numFact - 1;
    while(i > 0){
        numFact *= i;
        i--;
    }
    return numFact;
}

int main(){
    int precisionE;
    double numE = 1;
    std::cout << "Introduce la presicion deseada de e: ";
    std::cin >> precisionE;

    int i = 1;
    while (i < precisionE){
        numE += 1 / factorial(i);
        i++;
    }
    
    std::cout << "Con presicion de "<< precisionE <<  " e: " << numE << "\n";

    return 0;
}