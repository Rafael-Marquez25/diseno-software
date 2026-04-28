/* main.cpp
Practical exercise 5.
Coleccion class test program.
*/

#include <iostream>
#include "Coleccion.h"


int main() {
    Coleccion integers1(7); // seven-element Coleccion
    Coleccion integers2;    // 10-element Coleccion by default

    // print integers1 size and contents
    std::cout << "Size of Coleccion integers1 is " << integers1.getSize()
        << "\nColeccion after initialization:\n" << integers1;

    // print integers2 size and contents
    std::cout << "\nSize of Coleccion integers2 is " << integers2.getSize()
        << "\nColeccion after initialization:\n" << integers2;

    // input and print integers1 and integers2
    std::cout << "\nEnter 17 integers: " << std::endl;
    std::cin >> integers1 >> integers2;
    std::cout << "\nAfter input, the Coleccions contain:\n"
        << "integers1:\n" << integers1
        << "integers2:\n" << integers2;

    // use overloaded inequality (!=) operator
    std::cout << "\nEvaluating: integers1 != integers2" << std::endl;
    if (integers1 != integers2)
        std::cout << "integers1 and integers2 are not equal" << std::endl;

    // create Coleccion integers3 using integers1 as an initializer
    Coleccion integers3(integers1); // invokes copy constructor
    std::cout << "\nSize of Coleccion integers3 is " << integers3.getSize()
        << "\nColeccion after initialization:\n" << integers3;

    // use overloaded assignment (=) operator
    std::cout << "\nAssigning integers2 to integers1:" << std::endl;
    integers1 = integers2; // note target Coleccion is smaller
    std::cout << "integers1:\n" << integers1
        << "integers2:\n" << integers2;

    // use overloaded equality (==) operator
    std::cout << "\nEvaluating: integers1 == integers2" << std::endl;
    if (integers1 == integers2)
        std::cout << "integers1 and integers2 are equal" << std::endl;

    // use overloaded subscript operator to create rvalue
    std::cout << "\nintegers1[5] is " << integers1[5];

    // use overloaded subscript operator to create lvalue
    std::cout << "\n\nAssigning 1000 to integers1[5]" << std::endl;
    integers1[5] = 1000;
    std::cout << "integers1:\n" << integers1;

    return 0;
} // end main
