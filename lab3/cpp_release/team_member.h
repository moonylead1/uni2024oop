#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class TeamMember {
protected:
    std::string name;
    std::tm birthdate;

public:
    TeamMember(const std::string& name, const std::string& birthdate_str) {
        this->name = name;
        std::istringstream ss(birthdate_str);
        ss >> std::get_time(&birthdate, "%d.%m.%Y");
    }

    virtual std::string get_type() const = 0;
    int get_age() const {
        std::time_t now = std::time(0);
        std::tm* today = std::localtime(&now);
        int age = today->tm_year + 1900 - (birthdate.tm_year + 1900);
        if (today->tm_mon < birthdate.tm_mon || (today->tm_mon == birthdate.tm_mon && today->tm_mday < birthdate.tm_mday)) {
            age--;
        }
        return age;
    }
    std::string get_name() const { return name; }
    std::tm get_birthdate() const { return birthdate; }
    virtual std::string get_details_for_save() const = 0;
    virtual ~TeamMember() = default;
};

class Player : public TeamMember {
private:
    int goals;

public:
    Player(const std::string& name, const std::string& birthdate, int goals)
        : TeamMember(name, birthdate), goals(goals) {}

    std::string get_type() const override { return "Player"; }
    int get_goals() const { return goals; }
    std::string get_details_for_save() const override {
        return "Player;" + name + ";" + 
               std::to_string(birthdate.tm_mday) + "." + 
               std::to_string(birthdate.tm_mon + 1) + "." + 
               std::to_string(birthdate.tm_year + 1900) + ";" + 
               std::to_string(goals);
    }
};

class Coach : public TeamMember {
private:
    std::string category;

public:
    Coach(const std::string& name, const std::string& birthdate, const std::string& category)
        : TeamMember(name, birthdate), category(category) {}

    std::string get_type() const override { return "Coach"; }
    std::string get_category() const { return category; }
    std::string get_details_for_save() const override {
        return "Coach;" + name + ";" + 
               std::to_string(birthdate.tm_mday) + "." + 
               std::to_string(birthdate.tm_mon + 1) + "." + 
               std::to_string(birthdate.tm_year + 1900) + ";" + 
               category;
    }
};

#endif // TEAM_MEMBER_H