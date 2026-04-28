#ifndef USER_H
#define USER_H
#include <string>
#include <memory>
#include <map>

class User{

    private:
        int id;
        std::string username;
        std::string password;
        std::string role;
        
    public:
        User(int id, std::string role, std::string password, std::string username);
        virtual int getId() const;
        virtual std::string getRole() const;
        virtual std::string getPassword() const;
        virtual std::string getUsername() const;
        virtual std::unique_ptr<User> clone(int id, std::string role, std::string password, std::string username, std::string specialty) const = 0;
        ~User();    
};

#endif