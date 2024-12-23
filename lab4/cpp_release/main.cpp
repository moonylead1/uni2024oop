#include "Menu.h"
#include "Team.h"
#include "Exceptions.h"
#include <iostream>

void runApplication() {
    try {
        Menu menu;
        menu.run();
    } catch (const TeamError& e) {
        std::cerr<< e.what() << std::endl;
    } catch (const FileLoadError& e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    runApplication();
    return 0;
}