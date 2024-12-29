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

class UserManager {
private:
    std::unique_ptr<UserDisplayStrategy> displayStrategy;
    std::unique_ptr<UserSearchStrategy> searchStrategy;
    std::vector<User> users;
public:
    UserManager(){
        users = getUsersFromDatabase();
    }

    void setDisplayStrategy(std::unique_ptr<UserDisplayStrategy> strategy) {
        displayStrategy = std::move(strategy);
    }

    void setSearchStrategy(std::unique_ptr<UserSearchStrategy> strategy) {
        searchStrategy = std::move(strategy);
    }

    void showUserInfo(const User& user) const {
        if (displayStrategy) {
            displayStrategy->display(user);
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

    std::vector<User> getUsersFromDatabase() {
        // logic to get users from database we will change it later
        std::vector<User> users;
        
        users.emplace_back("001", "John Doe", "q9H3i@example.com", "admin", "active");
        users.emplace_back("002", "Bob Johnson", "Btq4D@example.com", "manager", "active");
        users.emplace_back("003", "Jane Smith", "7V5l0@example.com", "user", "inactive");
        users.emplace_back("004", "Kate Smith", "732sE@example.com", "user", "active");
        users.emplace_back("005", "Kate Smith", "732sE@example.com", "user", "blocked");

        return users;
    }
};

#endif