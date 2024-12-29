#ifndef USER_H
#define USER_H
#include <string>

class User
{
private:
    std::string id; // id of the user
    std::string name; // name of the user
    std::string email; // email of the user
    std::string role; // role of the user
    std::string status; // active, inactive, blocked
public:
    User(std::string id, std::string name, std::string email, std::string role, std::string status) 
        : id(id), name(name), email(email), role(role), status(status) {}
    
    //getters
    const std::string& get_id() const {return id;}
    const std::string& get_name() const {return name;}
    const std::string& get_email() const {return email;}
    const std::string& get_role() const {return role;}
    const std::string& get_status() const {return status;}
};

#endif