#include "Coach.h"
#include "TeamMember.h"
#include <sstream>
#include <iomanip>

Coach::Coach(const std::string& name, const std::string& birthdate, const std::string& category)
    : TeamMember(name, birthdate), category(category) {}

std::string Coach::getType() const {
    return "Coach";
}

std::string Coach::getCategory() const {
    return category;
}

std::string Coach::getDetailsForSave() const {
    std::ostringstream oss;
    std::tm birthdate_copy = TeamMember::getBirthdate(); // Create a copy
    oss << "Coach;" 
        << getName() << ";" 
        << std::put_time(&birthdate_copy, "%d.%m.%Y") << ";" 
        << getCategory();
    return oss.str();
}