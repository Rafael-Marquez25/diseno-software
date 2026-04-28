/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 2.
*/

#include <iostream>

int main(){
    int primerNumero = 0, segundoNumero = 0;

    std::cout << "Introduce el primer numero entero: ";
    std::cin >> primerNumero;
    std::cout << "Introduce el segundo numero entero: ";
    std::cin >> segundoNumero;

    if (primerNumero % segundoNumero == 0){
        std::cout << "El " << primerNumero << " es multiplo de " << segundoNumero << "\n";
    }
    else{
        std::cout << "El " << primerNumero << " no es multiplo de " << segundoNumero << "\n";
    }

    return 0;
}