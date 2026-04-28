/*
Autor: Rafael Márquez
Fecha: 18/9/25
Objetivo: Pratica 1. Ejercicio 2.
*/

#include <iostream>

int main(){
    double sumaNotas = 0;
    double notaTemp = 0;
    
    for(int i = 0; i < 5; i++){
        std::cout << "Inctroduce una nota: ";
        std::cin >> notaTemp;
        sumaNotas += notaTemp;
    }

    std::cout << "La media de las cinco notas es: " << sumaNotas/5.0 << "\n";

    return 0;
}