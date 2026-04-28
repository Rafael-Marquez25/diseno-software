#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include <memory>
#include <list>
#include "Appointment.h"
#include "User.h"

class Patient : public User
{
    private:
        std::unique_ptr<Appointment> currentAppointment;
        std::list<Appointment> appointmentHistory;

    public:
        Patient(int Id, std::string role, std::string password, std::string username, std::string specialty);
        std::unique_ptr<User> clone(int id, std::string role, std::string password, std::string username, std::string specialty) const{
            return std::make_unique<Patient> (id, role, password, username, specialty);
        }
        bool getAppointmentState();
        std::string getAppointmentHistoryToString();
        void addAppointmentToHistory(Appointment &appointmentToAdd);
        void setCurrentAppointment(std::unique_ptr<Appointment> appointment);
        void showMenu() const;
        ~Patient();
};

#endif