#ifndef COACH_H
#define COACH_H
#include "Coach.h"
#include "TeamMember.h"
#include <string>

class Coach : public TeamMember {
private:
    std::string category;

public:
    Coach(const std::string& name, const std::string& birthdate, const std::string& category);

    std::string getType() const override;
    std::string getCategory() const;
    
    std::string getDetailsForSave() const override;
};

#endif // COACH_H