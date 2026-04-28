#ifndef SYSTEM_H
#define SYSTEM_H

#include <list>
#include <queue>
#include <iostream>
#include <sqlite3.h>
#include <map>

#include "Patient.h"
#include "Medic.h"
#include "Admin.h"
#include "Robot.h"
#include "CustomExceptions.h"

/**
 * \class System
 * \brief Clase principal del sistema de gestión de citas.
 *
 * La clase System implementa el patrón Singleton y se encarga de:
 * - Gestionar la conexión con la base de datos SQLite.
 * - Controlar el inicio de sesión y registro de usuarios.
 * - Crear usuarios según su rol (Admin, Medic, Patient).
 * - Administrar robots disponibles para acompañamiento.
 * - Gestionar médicos y sus horarios.
 */
class System
{
private:
    /**
     * \brief Cola de robots del sistema.
     *
     * Almacena punteros a robots y permite gestionarlos en orden FIFO.
     */
    std::queue<Robot*> robots;

    /**
     * \brief Puntero a la base de datos SQLite.
     *
     * Se utiliza para realizar todas las operaciones de persistencia.
     */
    sqlite3* db;

    /**
     * \brief Instancia única del sistema (Singleton).
     */
    static System* singleSystem;

protected:
    /**
     * \brief Constructor protegido.
     *
     * Evita la creación directa de instancias fuera de la clase,
     * garantizando el uso del patrón Singleton.
     */
    System(){};

public:
    /**
     * \brief Devuelve la instancia única del sistema.
     *
     * Si no existe, se crea una nueva instancia.
     *
     * \return Puntero a la instancia única de System.
     */
    static System* getTheSystem();

    /**
     * \brief Crea un usuario dinámicamente según su rol.
     *
     * Implementa el patrón Prototype para instanciar el tipo
     * correcto de usuario.
     *
     * \param id Identificador del usuario.
     * \param role Rol del usuario (Admin, Medic o Patient).
     * \param password Contraseña del usuario.
     * \param username Nombre de usuario.
     * \param specialty Especialidad del médico (si aplica).
     *
     * \return Puntero inteligente a un objeto User.
     */
    static std::unique_ptr<User> makeUser(int id,
                                          std::string role,
                                          std::string password,
                                          std::string username,
                                          std::string specialty);

    /**
     * \brief Añade un robot a la cola de robots del sistema.
     *
     * \param robot Robot que se desea añadir.
     */
    void addRobot(Robot& robot);

    /**
     * \brief Obtiene el primer robot de la cola.
     *
     * \return Puntero al primer robot disponible.
     */
    Robot* getRobotFront();

    /**
     * \brief Muestra los robots disponibles.
     *
     * Imprime por pantalla los robots cuyo estado sea "Libre".
     */
    void printAvailableRobots();

    /**
     * \brief Asigna un robot libre para acompañar.
     *
     * \param time Tiempo durante el cual el robot acompañará.
     */
    void accompany(int time);

    /**
     * \brief Realiza el proceso de inicio de sesión.
     *
     * Solicita las credenciales del usuario y las verifica
     * en la base de datos.
     *
     * \param db Puntero a la base de datos SQLite.
     * \return Usuario autenticado.
     *
     * \throws DatabaseError Si ocurre un error al acceder a la base de datos.
     * \throws InvalidCredentialsError Si las credenciales son incorrectas.
     */
    std::unique_ptr<User> login(sqlite3* db);

    /**
     * \brief Devuelve el puntero a la base de datos.
     *
     * \return Puntero sqlite3 activo.
     */
    sqlite3* getDb() const;

    /**
     * \brief Registra un nuevo usuario en el sistema.
     *
     * Inserta un nuevo usuario en la base de datos.
     *
     * \param db Puntero a la base de datos SQLite.
     *
     * \throws DatabaseError Si ocurre un error durante la inserción.
     */
    void registerNewUser(sqlite3* db);

    /**
     * \brief Abre la base de datos del sistema.
     *
     * Inicializa la conexión con SQLite y configura
     * las restricciones de claves foráneas.
     *
     * \throws DatabaseError Si ocurre un error al abrir la base de datos.
     */
    void openDb();

    /**
     * \brief Constructor de copia eliminado.
     *
     * Evita la copia de la instancia Singleton.
     */
    System (System &otherSystem) = delete;

    /**
     * \brief Operador de asignación eliminado.
     *
     * Evita la asignación de instancias Singleton.
     */
    void operator= (const System&) = delete;

    /**
     * \brief Muestra la lista de médicos registrados.
     *
     * \param db Puntero a la base de datos SQLite.
     */
    void showMedicsList(sqlite3* db);

    /**
     * \brief Asigna una especialidad a un médico.
     *
     * \param db Puntero a la base de datos SQLite.
     */
    void createMedic(sqlite3* db);

    /**
     * \brief Asigna un horario a un médico.
     *
     * \_ATTACHMENT :
     * \param db Puntero a la base de datos SQLite.
     */
    void assignScheduleToMedic(sqlite3* db);

    /**
     * \brief Actualiza el horario de un médico.
     *
     * \param db Puntero a la base de datos SQLite.
     * \param medicId Identificador del médico.
     * \param start Hora de inicio.
     * \param end Hora de fin.
     */
    void updateScheduleForMedic(sqlite3* db,
                                int medicId,
                                std::string start,
                                std::string end);

    /**
     * \brief Verifica que un usuario sea médico.
     *
     * \param db Puntero a la base de datos SQLite.
     * \param medicId Identificador del usuario.
     *
     * \return 0 si el usuario es médico, 1 en caso contrario.
     */
    int verifyMedic(sqlite3* db, int medicId);

    /**
     * \brief Muestra las citas del sistema.
     *
     * Funcionalidad pendiente de implementación.
     */
    void showAppointments();

    /**
     * \brief Destructor del sistema.
     *
     * Libera los recursos y cierra la base de datos.
     */
    ~System();
};

#endif
