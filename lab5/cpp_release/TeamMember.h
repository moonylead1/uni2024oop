#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

#include <string>
#include <ctime>

class TeamMember {
protected:
    std::string name;
    std::tm birthdate;

public:
    TeamMember(const std::string& name, const std::string& birthdateStr);

    virtual std::string getType() const = 0;
    int getAge() const {
        std::time_t now = std::time(0);
        std::tm* today = std::localtime(&now);

        int age = today->tm_year + 1900 - (birthdate.tm_year + 1900);
        if (today->tm_mon < birthdate.tm_mon || 
            (today->tm_mon == birthdate.tm_mon && today->tm_mday < birthdate.tm_mday)) {
            age--;
        }

        return age;
    };

    std::string getName() const { return name; };
    std::tm getBirthdate() const { return birthdate; };
    
    
    virtual std::string getDetailsForSave() const = 0;
    virtual ~TeamMember() = default;
};

#endif // TEAM_MEMBER_H