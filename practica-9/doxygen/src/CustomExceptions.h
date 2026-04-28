#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H
#include <stdexcept>
#include <string>

class DatabaseError : public std::runtime_error {
public:
    // El mensaje 'what' debe ser descriptivo, p. ej.:
    // "Database error: Failed to prepare statement."
    DatabaseError(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InvalidCredentialsError : public std::runtime_error {
public:
    InvalidCredentialsError(const std::string& msg = "Usuario o contraseña incorrectos.")
        : std::runtime_error(msg) {}
};

#endif
