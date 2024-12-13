#include "Coach.h"

Coach::Coach(const std::string& name, const std::string& birthdate, const std::string& category)
    : TeamMember(name, birthdate), category(category) {}

std::string Coach::getCategory() const {
    return category;
}