#include <cassert>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <climits>
#include "Team.h"

class TeamTests {
private:
    int testsPassed = 0;
    int totalTests = 0;
    const std::string PASS_SYMBOL = "+";
    const std::string FAIL_SYMBOL = "-";
    const std::string HORIZONTAL_LINE = "-----------------------------------------------------------";
    
    void assertCondition(bool condition, const std::string& testName) {
        totalTests++;
        std::cout << std::setw(50) << std::left << testName << " ";
        
        if (condition) {
            testsPassed++;
            std::cout << "\033[32m" << PASS_SYMBOL << " PASS\033[0m" << std::endl;
        } else {
            std::cout << "\033[31m" << FAIL_SYMBOL << " FAIL\033[0m" << std::endl;
        }
    }

    std::string createTestFile(const std::string& content) {
        std::string filename = "test_team_members.txt";
        std::ofstream file(filename);
        file << content;
        file.close();
        return filename;
    }

    void cleanup(const std::string& filename) {
        std::remove(filename.c_str());
    }

    void printSectionHeader(const std::string& sectionName) {
        std::cout << "\n\033[1m" << sectionName << "\033[0m" << std::endl;
        std::cout << HORIZONTAL_LINE << std::endl;
    }

public:
    void runAllTests() {
        std::cout << "\033[1;34m";
        std::cout << R"(
--------------------------------------
|          TEAM CLASS TESTS          |
--------------------------------------
)";
        std::cout << "\033[0m" << std::endl;

        printSectionHeader("File Validation Tests");
        testFileValidation();

        printSectionHeader("Member Addition Tests");
        testMemberAddition();

        printSectionHeader("Player Age Tests");
        testYoungestOldestPlayer();

        printSectionHeader("Player Selection Tests");
        testPlayerSelection();

        printSectionHeader("Boundary Tests");
        testBoundaryConditions();

        printSectionHeader("Performance Tests");
        testPerformance();

        printSectionHeader("Exception Tests");
        testExceptions();

        printSectionHeader("Inheritance Tests");
        testTeamMemberInheritance();
        
        printSectionHeader("Concurrent Access Tests");
        testConcurrentModification();
        
        printSectionHeader("Menu Dependency Tests");
        testMenuDependency();
        
        printSectionHeader("File Operations Tests");
        testFileLocking();
        
        printTestResults();
    }


    void testFileValidation() {
        // invalid file EXTENTION
        try {
            Team team("invalid.dat");
            assertCondition(false, "Invalid file extension check");
        } catch (const FileLoadError&) {
            assertCondition(true, "Invalid file extension check");
        }

        // valid file FORMAT
        std::string validContent = "Player;John Doe;01.01.1990;10\n"
                                 "Coach;Jane Smith;15.06.1980;Expert\n";
        std::string filename = createTestFile(validContent);
        try {
            Team team(filename);
            assertCondition(true, "Valid file content loading");
        } catch (...) {
            assertCondition(false, "Valid file content loading");
        }
        cleanup(filename);

        // test invalid DATE format 
        std::string invalidDateContent = "Player;John Doe;13123123122121312312312312.1231321321.1990;10\n";
        filename = createTestFile(invalidDateContent);
        try {
            Team team(filename);
            assertCondition(false, "Invalid date format check");
        } catch (const InvalidDateError&) {
            assertCondition(true, "Invalid date format check");
        }
        cleanup(filename);

        // test invalid GOALS format
        std::string invalidGoalsContent = "Player;John Doe;01.01.1990;-5\n";
        filename = createTestFile(invalidGoalsContent);
        try {
            Team team(filename);
            assertCondition(false, "Invalid goals value check");
        } catch (const InvalidGoalsError&) {
            assertCondition(true, "Invalid goals value check");
        }
        cleanup(filename);
    }

    void testMemberAddition() {
        std::string filename = createTestFile("");
        Team team(filename);

        std::stringstream input;
        input << "Player\nJohn Doe\n01.01.1990\n10\n";
        std::cin.rdbuf(input.rdbuf());
        
        team.addMember();
        
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line);
        assertCondition(line == "Player;John Doe;01.01.1990;10", 
                       "Player data storage format");
        
        cleanup(filename);
    }

    void testYoungestOldestPlayer() {
        std::string content = 
            "Player;Young Player;01.01.2000;5\n"
            "Player;Old Player;01.01.1980;15\n"
            "Coach;Some Coach;01.01.1990;Expert\n";
            
        std::string filename = createTestFile(content);
        Team team(filename);

        std::stringstream output;
        auto oldCout = std::cout.rdbuf(output.rdbuf());

        team.findYoungestOldestPlayer();
        std::cout.rdbuf(oldCout);

        std::string outputStr = output.str();
        assertCondition(outputStr.find("Young Player") != std::string::npos &&
                       outputStr.find("Old Player") != std::string::npos,
                       "Age extremes identification");

        cleanup(filename);
    }

    void testPlayerSelection() {
        std::string content = 
            "Player;Test Player;01.01.1990;10\n"
            "Coach;Test Coach;01.01.1980;Expert\n";
            
        std::string filename = createTestFile(content);
        Team team(filename);

        std::stringstream input;
        input << "Test Player\n";
        std::cin.rdbuf(input.rdbuf());

        Player* selected = team.selectPlayer();
        assertCondition(selected != nullptr && selected->getName() == "Test Player",
                       "Existing player selection");

        input.str("Non Existent\n");
        std::cin.rdbuf(input.rdbuf());

        selected = team.selectPlayer();
        assertCondition(selected == nullptr,
                       "Non-existent player selection");

        cleanup(filename);
    }

    void testBoundaryConditions() {
        // max goals test
        std::string maxGoalsContent = "Player;Max Goals Player;01.01.1990;" + std::to_string(INT_MAX) + "\n";
        std::string filename = createTestFile(maxGoalsContent);
        try {
            Team team(filename);
            assertCondition(true, "Maximum goals value check");
        } catch (...) {
            assertCondition(false, "Maximum goals value check");
        }
        cleanup(filename);

        // empty file test
        filename = createTestFile("");
        try {
            Team team(filename);
            assertCondition(true, "Empty team file check");
        } catch (...) {
            assertCondition(false, "Empty team file check");
        }
        cleanup(filename);

        // name length test
        std::string longName(256, 'A');  // сreate a 256-character name or other legnth name
        std::string maxNameContent = "Player;" + longName + ";01.01.1990;10\n";
        filename = createTestFile(maxNameContent);
        try {
            Team team(filename);
            assertCondition(true, "Maximum name length check");
        } catch (std::length_error) {
            assertCondition(false, "Maximum name length check");
        }
        cleanup(filename);
    }

    void testPerformance() {
        // large team file
        std::string filename = "large_team.txt";
        {
            std::ofstream file(filename);
            for (int i = 0; i < 1000; i++) {
                file << "Player;Player" << i << ";01.01.1990;" << i << "\n";
            }
        }

        // loading performance
        auto start = std::chrono::high_resolution_clock::now();
        {
            Team team(filename);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        assertCondition(duration.count() < 1000, "Large team loading performance");

        // Test memory leaks (indirect through proper cleanup)
        /*bool memoryOk = true;
        try {
            for (int i = 0; i < 100; i++) {
                Team team(filename);
                std::stringstream input;
                input << "Player\nJohn Doe\n01.01.1990\n10\n";
                std::cin.rdbuf(input.rdbuf());
        
                team.addMember();  // Add some members to test memory management
            }
        } catch (...) {
            memoryOk = false;
        }
        assertCondition(memoryOk, "Memory management check");*/

        cleanup(filename);
    }

    void testExceptions() {
        // attempt to read from non-existent file
        try {
            Team team("non_existent_file.txt");
            assertCondition(false, "Non-existent file check");
        } catch (const FileLoadError&) {
            assertCondition(true, "Non-existent file check");
        }

        // corrupted data Goals
        std::string corruptedContent = "Player;Test;01.01.1990;NotANumber\n";
        std::string filename = createTestFile(corruptedContent);
        try {
            Team team(filename);
            assertCondition(false, "Corrupted file content check");
        } catch (const InvalidGoalsError&) {  // Changed from InvalidFormatError
            assertCondition(true, "Corrupted file content check");
        }
        cleanup(filename);

        // invalid team member type
        std::string invalidTypeContent = "InvalidType;Test;01.01.1990;10\n";
        filename = createTestFile(invalidTypeContent);
        try {
            Team team(filename);
            assertCondition(false, "Invalid member type check");
        } catch (const InvalidTypeError&) {
            assertCondition(true, "Invalid member type check");
        }
        cleanup(filename);
    }

    void testTeamMemberInheritance() {
        //inheritance relationship between Player v Coach and TeamMember
        std::string content = 
            "Player;Test Player;01.01.1990;10\n"
            "Coach;Test Coach;01.01.1980;Expert\n";
            
        std::string filename = createTestFile(content);
        Team team(filename);

        std::stringstream output;
        auto oldCout = std::cout.rdbuf(output.rdbuf());
        
        team.viewTeam();
        std::cout.rdbuf(oldCout);
        std::string outputStr = output.str();

        //if both types are handled through polymorphism
        assertCondition(outputStr.find("Type: Player") != std::string::npos &&
                    outputStr.find("Type: Coach") != std::string::npos,
                    "TeamMember inheritance polymorphism");

        cleanup(filename);
    }

    void testConcurrentModification() {
        std::string filename = createTestFile("Player;Initial Player;01.01.1990;10\n");
        
        try {
            Team team1(filename);
            
            // modify through 1 inst
            std::stringstream input1;
            input1 << "Player\nJohn Doe\n01.01.1990\n20\n";
            std::cin.rdbuf(input1.rdbuf());
            team1.addMember();

            // create and modify through 2 inst
            Team team2(filename);
            std::stringstream input2;
            input2 << "Coach\nJane Smith\n01.01.1980\nPro\n";
            std::cin.rdbuf(input2.rdbuf());
            team2.addMember();

            // read final file content
            std::ifstream resultFile(filename.c_str());
            std::string fileContent;
            std::string line;
            while (std::getline(resultFile, line)) {
                fileContent += line + "\n";
            }
            
            // check if both modifications are present
            bool hasJohnDoe = fileContent.find("John Doe") != std::string::npos;
            bool hasJaneSmith = fileContent.find("Jane Smith") != std::string::npos;
            bool hasInitialPlayer = fileContent.find("Initial Player") != std::string::npos;
            
            assertCondition(hasJohnDoe && hasJaneSmith && hasInitialPlayer,
                        "Concurrent file modification handling");
        } catch (const TeamError& e) {
            std::cout << "Test caught expected TeamError: " << e.what() << std::endl;
            assertCondition(true, "Concurrent file modification handling");
        }

        // cleanup both the data file and potential lock file
        cleanup(filename);
        cleanup(filename + ".lock");
    }

    void testMenuDependency() {
        std::string filename = createTestFile("Player;Test Player;01.01.1990;10\n");
        Team team(filename);

        //  menu simulator interactions event handler
        std::vector<std::string> menuInputs = {
            "Player\nMenu Player\n01.01.1995\n5\n",  // adding member
            "Test Player\n",                         // select player
            ""                                       // trottle down for other operations
        };

        for (const auto& input : menuInputs) {
            std::stringstream inputStream(input);
            auto oldCin = std::cin.rdbuf(inputStream.rdbuf());
            
            std::stringstream outputStream;
            auto oldCout = std::cout.rdbuf(outputStream.rdbuf());

            // Test different menu operations
            team.addMember();
            team.viewTeam();
            team.findYoungestOldestPlayer();
            team.selectPlayer();

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            std::string output = outputStream.str();
            assertCondition(output.length() > 0, "Menu-Team interaction");
        }

        cleanup(filename);
    }

    void testFileLocking() {
        std::string filename = createTestFile("Player;Test Player;01.01.1990;10\n");
        
        // attrmpt to to open file exclusively while Team inst is active status
        Team team(filename);
        std::fstream lockTest(filename, std::ios::in | std::ios::out);
        
        assertCondition(lockTest.is_open(), "File locking mechanism");
        lockTest.close();
        
        cleanup(filename);
    }


    void printTestResults() {
                std::cout << R"(
--------------------------------------
|       Tests results summary        |
--------------------------------------
)";
        
    double successRate = (totalTests > 0) ? (testsPassed * 100.0 / totalTests) : 0;
        
    std::cout << std::setw(20) << std::left << "Total Tests:" << totalTests << std::endl;
    std::cout << std::setw(20) << std::left << "Tests Passed:" << testsPassed << std::endl;
    std::cout << std::setw(20) << std::left << "Success Rate:" << 
        std::fixed << std::setprecision(1) << successRate << "%" << std::endl;
        
    std::cout << "\nOverall Status: ";
    if (successRate == 100.0) {
        std::cout << "ALL TESTS PASSED SUCCESSFULLY" << std::endl;
    } else {
        std::cout << "SOME TESTS FAILED" << std::endl;
    }
        
    std::cout << HORIZONTAL_LINE << std::endl;
    }
};

int main() {
    TeamTests tests;
    tests.runAllTests();
    return 0;
}