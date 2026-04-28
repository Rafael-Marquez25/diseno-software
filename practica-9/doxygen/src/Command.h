#ifndef COMMAND_H
#define COMMAND_H

// Necesaria para evitar una dependencia circular si System incluye Command.h
class System;

/**
 * @class Command
 * @brief Interfaz abstracta para el patrón Command.
 *
 * Encapsula una solicitud como un objeto, permitiendo parametrizar
 * clientes con diferentes peticiones, hacer colas o logs de operaciones.
 */
class Command {
protected:
    // Referencia al objeto que sabe cómo realizar las acciones (Receiver).
    // En este caso, la clase System.
    System* system;

public:
    /**
     * @brief Constructor de la clase Command.
     * @param sys Puntero al objeto System que actuará como Receiver.
     */
    explicit Command(System* sys) : system(sys) {}

    /**
     * @brief Método de ejecución del comando.
     *
     * Este es el único método que el Invoker (Admin) necesita conocer.
     */
    virtual void execute() = 0;

    /**
     * @brief Destructor virtual.
     *
     * Crucial para liberar correctamente la memoria de las clases derivadas.
     */
    virtual ~Command() = default;
};

#endif // COMMAND_H
