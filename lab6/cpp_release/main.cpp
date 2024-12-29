#include "UserManager.h"
#include "DetailedUserDisplay.h"
#include "BasicUserDisplay.h"
#include "SearchById.h"
#include "SearchByName.h"
#include "SearchByEmail.h"

#include <iostream>
#include <memory>

int main() {
    UserManager userManager;
    userManager.setDisplayStrategy(std::make_unique<BasicUserDisplay>());
    
    std::cout << "Search User by ID: " << std::endl;
    userManager.setSearchStrategy(std::make_unique<SearchById>());
    auto results = userManager.searchUsers("002");
    for (const auto& user : results) {
        userManager.showUserInfo(user);
        std::cout << std::endl;
    }

    std::cout << "Search User by Name: " << std::endl;
    userManager.setSearchStrategy(std::make_unique<SearchByName>());
    results = userManager.searchUsers("John Doe");
    for (const auto& user : results) {
        userManager.showUserInfo(user);
        std::cout << std::endl;
    }

    std::cout << "Search User by Email: " << std::endl;
    userManager.setSearchStrategy(std::make_unique<SearchByEmail>());
    results = userManager.searchUsers("Btq4D@example.com");
    for (const auto& user : results) {
        userManager.showUserInfo(user);
        std::cout << std::endl;
    }
    
    return 0;
}