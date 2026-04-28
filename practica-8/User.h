#ifndef USER_H
#define USER_H
#include <string>

class User{

    private:
        int id;
        std::string username;
        std::string password;
        std::string role;
        
    public:
        User(int id, std::string role, std::string password, std::string username);
        int getId() const;
        virtual std::string getRole() const;
        std::string getPassword() const;
        std::string getUsername() const;
        ~User();    
};

#endif