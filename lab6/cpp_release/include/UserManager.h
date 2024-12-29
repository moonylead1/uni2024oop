// idea of double strategy pattern
// we have some sort of users that have id email name user_position
// we want to get the Detailed view or Basic (Small) view
// we also want to search for users by name id or email
// if multimle we want to have some sort of list for example Admins or Managers
// also i want to add some more stuff like active/ inactive users

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "UserDisplayStrategy.h"
#include "UserSearchStrategy.h"

#include <memory>
#include <vector>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class UserManager {
private:
    std::unique_ptr<UserDisplayStrategy> displayStrategy;
    std::unique_ptr<UserSearchStrategy> searchStrategy;
    std::vector<User> users;
    const std::string filename;

    std::vector<User> createDefaultUsers() const {
        std::vector<User> defaultUsers;
        defaultUsers.push_back(User("001", "Ivan", "ivan@example.com", "Admin"));
        defaultUsers.push_back(User("002", "Maria", "maria@example.com", "User"));
        defaultUsers.push_back(User("003", "Petro", "petro@example.com", "Manager"));
        return defaultUsers;
    }
public:
    UserManager() : filename("member_list.json") {
        loadUsersFromJson();
    }

    void setDisplayStrategy(std::unique_ptr<UserDisplayStrategy> strategy) {
        displayStrategy = std::move(strategy);
    }

    void setSearchStrategy(std::unique_ptr<UserSearchStrategy> strategy) {
        searchStrategy = std::move(strategy);
    }

    


    bool addUser(const std::string& id, const std::string& name, 
                const std::string& email, const std::string& role) {
        try {
            users.push_back(User(id, name, email, role));
            return saveUsersToJson();
        } catch (const std::exception& e) {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            return false;
        }
    }

    bool loadUsersFromJson() {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "No existing users file found. Creating new one.\n";
                users = createDefaultUsers();
                return saveUsersToJson();
            }

            json j;
            file >> j;
            users.clear();
            
            for (const auto& user_json : j) {
                users.push_back(User::from_json(user_json));
            }
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error loading users: " << e.what() << std::endl;
            users = createDefaultUsers();
            return false;
        }
    }

    bool saveUsersToJson() const {
        try {
            json j = json::array();
            for (const auto& user : users) {
                j.push_back(user.to_json());
            }

            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Could not open file for writing: " << filename << std::endl;
                return false;
            }
            
            file << j.dump(4);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error saving users: " << e.what() << std::endl;
            return false;
        }
    }
    
    std::vector<User> searchUsers(const std::string& searchTerm) const {
        if (!searchStrategy) { // add error handling here
            return {};
        }
        
        std::vector<User> results;
        for (const auto& user : users) {
            if (searchStrategy->matches(user, searchTerm)) {
                results.push_back(user);
            }
        }
        return results;
    }
    
    void showUserInfo(const User& user) const {
        if (displayStrategy) {
            displayStrategy->display(user);
        }
    }
};

#endif