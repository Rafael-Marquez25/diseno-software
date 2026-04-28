/* Coleccion.h
Practical exercise 5.
Coleccion class definition with overloaded operators.
*/
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class Coleccion {
    friend std::ostream &operator<<(std::ostream &, const Coleccion &);
    friend std::istream &operator>>(std::istream &, Coleccion &);

public:
    explicit Coleccion(int = 10); // default constructor
    Coleccion(const Coleccion &); // copy constructor
    ~Coleccion(); // destructor

    size_t getSize() const; // return size
    const Coleccion &operator=(const Coleccion &); // assignment operator
    
    bool operator==(const Coleccion &) const; // equality operator
    bool operator!=(const Coleccion &right) const {
        return !(*this == right); // invokes Coleccion::operator==
    }

    int &operator[](int);
    int operator[](int) const;

private:
    size_t size;
    int *ptr;
};

#endif
