/* Coleccion.cpp
Practical exercise 5.
Coleccion class member -and friend- function definitions.
*/

#include <iostream>
#include <iomanip> // I/O manipulation library
#include "Coleccion.h" // Coleccion class definition

// default constructor for class Coleccion (default size 10)
// considering arraySize > 0, otherwise an exception should be thrown
Coleccion::Coleccion(int arraySize)
    : size(arraySize),
        ptr(new int[size]) {
    for (size_t i = 0; i < size; ++i)
        ptr[i] = 0; // set pointer-based array element
} // end Coleccion default constructor

// copy constructor for class Coleccion; must receive a reference to a Coleccion
Coleccion::Coleccion(const Coleccion &arrayToCopy)
    : size(arrayToCopy.size),
        ptr(new int[size]) {
    for (size_t i = 0; i < size; ++i)
        ptr[i] = arrayToCopy.ptr[i]; // copy into object
} // end Coleccion copy constructor

// destructor for class Coleccion
Coleccion::~Coleccion() {
    delete[] ptr; // release pointer-based array space
} // end destructor

size_t Coleccion::getSize() const{
    return size;
}

const Coleccion& Coleccion::operator=(const Coleccion& otherCollection) //assignment operator
{
    if(size != otherCollection.size) 
    {
        delete[] ptr;  // delete the current pointer
        size = otherCollection.size;    // assignment the new size
        ptr = new int[otherCollection.size]; // Create a new array with the new size
    }
    for (size_t i = 0; i < size; i++)
    {
        this->ptr[i] = otherCollection.ptr[i]; // assignment per index if sizes are equals
    }
    
    return *this;
}

bool Coleccion::operator==(const Coleccion& otherCollection) const // equality operator
{
    if(size != otherCollection.size)
    {
        return false; // sizes not equals
    }

    for(size_t i = 0; i < size; i++)
    {
        if(this->ptr[i] != otherCollection.ptr[i]) // if one element is diferent, the collections are not equals
        {
            return false; 
        }
    }

    return true;
}

std::ostream &operator<<(std::ostream &output, const Coleccion &collection){
    output << "[" ;
    for (size_t i = 0; i < collection.getSize(); i++)
    {
        output << collection[i];
        if (i + 1 < collection.getSize()) output << " ";
    }
    output << "]";
    return output; // Format [value1 value2 value3 ... valueN]
}

std::istream &operator>>(std::istream &input, Coleccion &collection) {
    char c;
    input >> c; // leer '['
    for (size_t i = 0; i < collection.getSize(); i++) {
        input >> collection[i];
    }
    input >> c; // leer ']'
    return input;
}

int &Coleccion::operator[](int index){
    return ptr[index];
}

int Coleccion::operator[](int index) const{
    return ptr[index];
}