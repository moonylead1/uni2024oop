//as i ve seen in task ill better use strcpy bc it is more efficient in understanding text docs

#include <iostream>
#include <string>

//menu must contain: 
//1. SHOW : show players (showing the table with all players currently written down in file)
//2. SHOW : trainers (same above)
//3. PLAYER : add player with all options as name, age, position, touchdowns (goals, assists) (btw pair maybe), team
// [name age position touchdowns team]
//4. PLAYER : remove player
//5. TRAINER : add trainer (trainer must have a name and a team based)
// [name team]
//6. TRAINER : remove trainer
//7. FUNC : show the youngest and oldest player
//8. OPER : EXIT

void menu() {
    std::cout << "Menu:\n";
    std::cout << "1.\tShow players\n";
    std::cout << "2.\tShow players in game\n";
    std::cout << "3.\tShow trainers\n";
    std::cout << "4.\tMove player to game\n";
    std::cout << "5.\tAdd player\n";
    std::cout << "6.\tRemove player\n";
    std::cout << "7.\tAdd trainer\n";
    std::cout << "8.\tRemove trainer\n";
    std::cout << "9.\tShow the youngest and oldest player\n";
    std::cout << "10.\tExit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    menu();
    return 0;
}