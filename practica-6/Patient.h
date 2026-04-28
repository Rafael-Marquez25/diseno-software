#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include <memory>
#include "Appointment.h"

class Patient
{
    private:
        int id;
        std::string password;
        std::string email;
        std::unique_ptr<Appointment> currentAppointment;
        std::unique_ptr<std::unique_ptr<Appointment>[]> appointmentHistory;

    public:
        Patient(int idPaciente);
        int getId();
        bool getAppointmentState();
        std::string getAppointmentHistoryToString();
        void addAppointmentToHistory(std::unique_ptr<Appointment> appointmentToAdd);
        void setCurrentAppointment(std::unique_ptr<Appointment> appointment);
        void setEmail(std::string email);
        std::string getEmail();
};

#endif