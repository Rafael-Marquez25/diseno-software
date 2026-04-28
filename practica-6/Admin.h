#ifndef ADMIN_H
#define ADMIN_H

#include<string>

class Admin
{
private:
    int id;
    std::string email;
    std::string password;
public:
    Admin(int adminId);
    int getId();
    void manageMedics();
    void manageSpecialties();
    void manageAgenda();
    void setEmail(std::string email);
    std::string getEmail();
};


#endif
