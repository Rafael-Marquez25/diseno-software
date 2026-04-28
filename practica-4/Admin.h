#ifndef ADMIN_H
#define ADMIN_H

#include<string>

class Admin
{
private:
    std::string adminId;
    std::string email;
    std::string password;
public:
    Admin(std::string adminId);
    std::string getId();
    void manageMedics();
    void manageSpecialties();
    void manageAgenda();
    void setEmail(std::string email);
    std::string getEmail();
};


#endif
