/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 6.3.
*/

#include <iostream>
#include <cmath>

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
    int x;
    std::cout << "Introduce la presicion deseada de e: ";
    std::cin >> precisionE;
    std::cout << "Introduce el valor de x:";
    std::cin >> x;

    int i = 1;
    while (i < precisionE){
        numE += pow(x, i) / factorial(i);
        i++;
    }
    
    std::cout << "Con presicion de "<< precisionE << " y x = " << x << " e: " << numE << "\n";

    return 0;
}