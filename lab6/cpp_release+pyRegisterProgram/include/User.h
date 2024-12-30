#pragma once
#include <string>
#include "json.hpp"

class User {
private:
    std::string id;
    std::string name;
    std::string email;
    std::string role;
    std::string status;

public:
    User(const std::string& id, const std::string& name, const std::string& email, const std::string& role, const std::string& status);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getRole() const;
    const std::string& getStatus() const;

    nlohmann::json to_json() const;
    static User from_json(const nlohmann::json& j);
};