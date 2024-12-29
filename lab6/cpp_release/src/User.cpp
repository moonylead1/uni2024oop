#include "User.h"

User::User(const std::string& id, const std::string& name, 
           const std::string& email, const std::string& role)
    : id(id), name(name), email(email), role(role) {}

const std::string& User::getId() const { return id; }
const std::string& User::getName() const { return name; }
const std::string& User::getEmail() const { return email; }
const std::string& User::getRole() const { return role; }

nlohmann::json User::to_json() const {
    nlohmann::json j;
    j["id"] = id;
    j["name"] = name;
    j["email"] = email;
    j["role"] = role;
    return j;
}

User User::from_json(const nlohmann::json& j) {
    return User(
        j.at("id").get<std::string>(),
        j.at("name").get<std::string>(),
        j.at("email").get<std::string>(),
        j.at("role").get<std::string>()
    );
}