#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>

class Appointment
{
    private:
        int id;
        std::string appointmentDate; // se pude mejorar a un tipo date
        std::string associatedPatient;
        std::string associatedMedic;
        std::string appoinmentLocation;
        std::string appointmentState;
    public:
        Appointment(int id, std::string date, std::string patient, std::string medic, std::string location);
        int getId();
        std::string getDate();
        std::string getAssociatedPatient();
        std::string getAssociatedMedic();
        std::string getAppointmentLocation();
        void changeAppointmentLocation(std::string newLocation);
        void setAppointmentState(std::string newState);
        
};

#endif
