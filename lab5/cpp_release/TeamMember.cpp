#include "TeamMember.h"
#include <sstream>
#include <iomanip>
#include <cstring>
#include <iostream>

TeamMember::TeamMember(const std::string& name, const std::string& birthdateStr) : name(name) {
    std::istringstream ss(birthdateStr);
    
    // Reset the tm structure
    std::memset(&birthdate, 0, sizeof(std::tm));
    
    // Try DD.MM.YYYY
    if (!(ss >> std::get_time(&birthdate, "%d.%m.%Y"))) { //maybe add later another formats?
        std::cerr << "Warning: Failed to parse date: " << birthdateStr << std::endl;
    }
}