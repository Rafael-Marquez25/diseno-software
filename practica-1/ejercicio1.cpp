/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 1.
*/

#include <iostream>

int main(){
    double primerNumero = 0;
    double segundoNumero = 0;

    std::cout << "Intruduce el primer número: ";
    std::cin >> primerNumero;
    std::cout << "Intruduce el segundo número: ";
    std::cin >> segundoNumero;

    std::cout << "La suma de los numeros es: " << primerNumero + segundoNumero << "\n";
    std::cout << "La producto de los numeros es: " << primerNumero * segundoNumero << "\n";
    std::cout << "La diferencia de los numeros es: " << primerNumero - segundoNumero << "\n";
    std::cout << "El cociente de los numeros es: " << primerNumero / segundoNumero << "\n";


    return 0;
}