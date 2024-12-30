#include "UserManager.h"
#include "DetailedUserDisplay.h"
#include "BasicUserDisplay.h"
#include "SearchById.h"
#include "SearchByName.h"
#include "SearchByEmail.h"
#include "SearchByStatus.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Menu
{
private:
    std::string prompt;
    UserManager userManager;
    void setDisplayStrategy(std::unique_ptr<UserDisplayStrategy> strategy){
        userManager.setDisplayStrategy(std::move(strategy));
    }
public:
    Menu();

    std::string CommandPrompt(std::string prompt);
    void welcomeMessage();
    void runMenu();
    void compileAsk(const std::vector<std::string>& str);

    ~Menu();
};

Menu::Menu(/* args */)
{
    welcomeMessage();
    userManager.setDisplayStrategy(std::make_unique<BasicUserDisplay>());
    while (true){
        runMenu();
    }
}

Menu::~Menu()
{
}

void Menu::runMenu() {
    std::cout << "Prompt: ";
    std::getline(std::cin, prompt);
    CommandPrompt(prompt);
}

std::vector<std::string> splitStringBySpace(const std::string& str) {
    std::vector<std::string> options;
    std::istringstream stream(str);
    std::string option;
    while (stream >> option) {
        options.push_back(option);
    }
    return options;
}

inline std::string Menu::CommandPrompt(std::string prompt)
{
    std::vector<std::string> options = splitStringBySpace(prompt);
    compileAsk(options);
    return prompt;
}

void Menu::welcomeMessage()
{
    std::cout << "----Welcome to the User Database Interface!----" << std::endl;
    std::cout << "To use fast interface just use the command prompt like: " << std::endl;
    std::cout << "For example: searchId 009 (for searching by ID)" << std::endl;
    std::cout << "* If you want to use manual interface instead, type: manual *" << std::endl;
    std::cout << "* For more information type: help or 0 *" << std::endl;
}

void Menu::compileAsk(const std::vector<std::string>& str) {

    
    //menu option: help
    if (str[0] == "help" || str[0] == "0") {
        std::cout << "--------------Commands--------------" << std::endl;
        std::cout << "switchDisplay [basic | detailed] (default: basic) - changes the display strategy" << std::endl;
        std::cout << "searchId [ID] - searches for a user by ID" << std::endl;
        std::cout << "searchName [Name] - searches for a user by Name" << std::endl;
        std::cout << "searchEmail [Email] - searches for a user by Email" << std::endl;
        std::cout << "searchStatus [all | up | down | blocked] - searches for a user by Status" << std::endl;
        std::cout << "exit - exits the program" << std::endl;
    }
    //menu option: switchDisplay [detailed | basic]
    if (str[0] == "switchDisplay") {
        if (str[1] == "basic") {
            userManager.setDisplayStrategy(std::make_unique<BasicUserDisplay>());
            //currentDisplayStrategy = std::make_unique<DetailedUserDisplay>();
            std::cout << "Switched to Basic User Display" << std::endl;
        }
        else if (str[1] == "detailed") {
            userManager.setDisplayStrategy(std::make_unique<DetailedUserDisplay>());
            //currentDisplayStrategy = std::make_unique<BasicUserDisplay>();
            std::cout << "Switched to Detailed User Display" << std::endl;
        }
    }
    //menu option: searchId [ID]
    if (str[0] == "searchId") {
        std::cout << "Search User by ID: " + str[1] << std::endl;
        userManager.setSearchStrategy(std::make_unique<SearchById>());
        auto results = userManager.searchUsers(str[1]);
        for (const auto& user : results) {
            userManager.showUserInfo(user);
            std::cout << std::endl;
        }
    }
    //menu option: searchName [Name]
    if (str[0] == "searchName") {
        std::cout << "Search User by Name: " + str[1] << std::endl;
        userManager.setSearchStrategy(std::make_unique<SearchByName>());
        auto results = userManager.searchUsers(str[1]);
        for (const auto& user : results) {
            userManager.showUserInfo(user);
            std::cout << std::endl;
        }
    }
    //menu option: searchEmail [Email]
    if (str[0] == "searchEmail") {
        std::cout << "Search User by Email: " + str[1] << std::endl;
        userManager.setSearchStrategy(std::make_unique<SearchByEmail>());
        auto results = userManager.searchUsers(str[1]);
        for (const auto& user : results) {
            userManager.showUserInfo(user);
            std::cout << std::endl;
        }
    }
    //menu option: status [all | up | down | blocked]
    if (str[0] == "status") {
        if (str[1] == "up") {
            userManager.setSearchStrategy(std::make_unique<SearchByStatus>());
            auto results = userManager.searchUsers(str[1]);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }
            return;
        }
        else if (str[1] == "down") {
            userManager.setSearchStrategy(std::make_unique<SearchByStatus>());
            auto results = userManager.searchUsers(str[1]);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }
            return;
        }
        else if (str[1] == "blocked") {
            userManager.setSearchStrategy(std::make_unique<SearchByStatus>());
            auto results = userManager.searchUsers(str[1]);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }
            return;
        }
        else if (str[1] == "all") {
            std::cout << "No concrete users specified, showing all" << std::endl;
            userManager.setSearchStrategy(std::make_unique<SearchByStatus>());

            std::cout << "active users: " << std::endl;
            std::string user_status_active = "up";
            auto results = userManager.searchUsers(user_status_active);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }

            std::cout << "inactive users: " << std::endl;
            std::string user_status_inactive = "down";
            results = userManager.searchUsers(user_status_inactive);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }

            std::cout << "blocked users: " << std::endl;
            std::string user_status_blocked = "blocked";
            results = userManager.searchUsers(user_status_blocked);
            for (const auto& user : results) {
                userManager.showUserInfo(user);
                std::cout << std::endl;
            }
        }
    }
    //menu option: exit
    if (str[0] == "exit") {
        exit(0);
    }

}