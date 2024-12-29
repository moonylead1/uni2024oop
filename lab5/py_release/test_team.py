import unittest
import json
import os
import time
import threading
from datetime import datetime
from team import Team
from exceptions import (
    FileLoadError, InvalidTypeError, InvalidDateError,
    InvalidGoalsError, InvalidNameError
)

class TeamTests(unittest.TestCase):
    def setUp(self):
        """Set up test fixtures before each test method."""
        self.test_file = "test_team_members.json"
        
    def tearDown(self):
        """Clean up after each test method."""
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def create_test_file(self, content):
        """Helper method to create a test JSON file."""
        with open(self.test_file, 'w', encoding='utf-8') as f:
            json.dump(content, f, ensure_ascii=False, indent=2)
        return self.test_file

    def test_file_validation(self):
        """Test file validation functionality."""
        # invalid file path
        with self.assertRaises(FileLoadError):
            Team("non_existent_file.json")

        # valid file format
        valid_content = [
            {
                "type": "Player",
                "name": "John Doe",
                "birthdate": "01.01.1990",
                "goals": 10
            },
            {
                "type": "Coach",
                "name": "Jane Smith",
                "birthdate": "15.06.1980",
                "category": "Expert"
            }
        ]
        self.create_test_file(valid_content)
        team = Team(self.test_file)
        self.assertEqual(len(team.members), 2)

        # invalid date format
        invalid_date_content = [{
            "type": "Player",
            "name": "John Doe",
            "birthdate": "2023.13.45",
            "goals": 10
        }]
        self.create_test_file(invalid_date_content)
        with self.assertRaises(SystemExit):
            Team(self.test_file)

        # invalid goals format
        invalid_goals_content = [{
            "type": "Player",
            "name": "John Doe",
            "birthdate": "01.01.1990",
            "goals": -5
        }]
        self.create_test_file(invalid_goals_content)
        with self.assertRaises(SystemExit):
            Team(self.test_file)

        # invalid member type
        invalid_type_content = [{
            "type": "Invalid",
            "name": "John Doe",
            "birthdate": "01.01.1990",
            "goals": 10
        }]
        self.create_test_file(invalid_type_content)
        with self.assertRaises(SystemExit):
            Team(self.test_file)

    def test_member_addition(self):
        """Test adding team members."""
        self.create_test_file([])
        team = Team(self.test_file)
        
        # Add a player
        team.add_member("Player", "John Doe", "01.01.1990", 10)
        
        # Add a coach
        team.add_member("Coach", "Jane Smith", "01.01.1980", "Expert")
        
        # verify both members were added correctly
        with open(self.test_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        self.assertEqual(len(data), 2)
        self.assertEqual(data[0]["name"], "John Doe")
        self.assertEqual(data[1]["name"], "Jane Smith")

    def test_player_age_functions(self):
        """Test youngest/oldest player functionality."""
        content = [
            {
                "type": "Player",
                "name": "Young Player",
                "birthdate": "01.01.2000",
                "goals": 5
            },
            {
                "type": "Player",
                "name": "Old Player",
                "birthdate": "01.01.1980",
                "goals": 15
            },
            {
                "type": "Coach",
                "name": "Coach",
                "birthdate": "01.01.1990",
                "category": "Expert"
            }
        ]
        self.create_test_file(content)
        team = Team(self.test_file)
        
        import io
        import sys
        captured_output = io.StringIO()
        sys.stdout = captured_output
        
        team.find_youngest_oldest_player()
        sys.stdout = sys.__stdout__
        
        output = captured_output.getvalue()
        self.assertIn("Young Player", output)
        self.assertIn("Old Player", output)
        self.assertNotIn("Coach", output)

    def test_player_selection(self):
        """Test player selection functionality."""
        content = [
            {
                "type": "Player",
                "name": "Test Player",
                "birthdate": "01.01.1990",
                "goals": 10
            }
        ]
        self.create_test_file(content)
        team = Team(self.test_file)
        
        # Mock input for selection
        import builtins
        original_input = builtins.input
        builtins.input = lambda _: "1"
        
        team.select_player()
        
        # Restore original input function
        builtins.input = original_input
        
        # Verify player was selected
        with open(self.test_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        self.assertTrue(data[0].get("selected_for_game", False))

    def test_boundary_conditions(self):
        """Test boundary conditions."""
        # Test empty team
        self.create_test_file([])
        team = Team(self.test_file)
        self.assertEqual(len(team.members), 0)
        
        # Test maximum goals value
        max_goals_content = [{
            "type": "Player",
            "name": "Max Goals Player",
            "birthdate": "01.01.1990",
            "goals": 2147483647  # max 32-bit integer
        }]
        self.create_test_file(max_goals_content)
        team = Team(self.test_file)
        self.assertEqual(team.members[0]["goals"], 2147483647)
        
        # Test very long name
        long_name = "A" * 256
        long_name_content = [{
            "type": "Player",
            "name": long_name,
            "birthdate": "01.01.1990",
            "goals": 10
        }]
        self.create_test_file(long_name_content)
        team = Team(self.test_file)
        self.assertEqual(team.members[0]["name"], long_name)

    def test_performance(self):
        """Test performance with large dataset."""
        # Create large team file
        large_content = [
            {
                "type": "Player",
                "name": f"Player{i}",
                "birthdate": "01.01.1990",
                "goals": i
            } for i in range(1000)
        ]
        self.create_test_file(large_content)
        
        # Test loading performance
        start_time = time.time()
        team = Team(self.test_file)
        end_time = time.time()
        
        self.assertLess(end_time - start_time, 1.0)  # Should load in under 1 second
        self.assertEqual(len(team.members), 1000)

        # Test memory management
        for _ in range(100):
            team = Team(self.test_file)
            team.add_member("Player", "Test Player", "01.01.1990", 10)

    def test_menu_dependency(self):
        """Test team interactions through menu-like operations."""
        self.create_test_file([])
        team = Team(self.test_file)

        # mock input function
        original_input = __builtins__.input
        __builtins__.input = lambda _: "1"

        try:
            # Test sequence of operations
            team.add_member("Player", "Test Player", "01.01.1990", 10)
            team.view_team()
            team.find_youngest_oldest_player()
            team.select_player()
            team.show_selected_players()
        finally:
            # Restore original input function
            __builtins__.input = original_input

        # Verify final state
        with open(self.test_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        self.assertEqual(len(data), 1)
        self.assertTrue(data[0].get("selected_for_game", False))

    def test_show_selected_players(self):
        """Test showing selected players."""
        content = [
            {
                "type": "Player",
                "name": "Selected Player",
                "birthdate": "01.01.1990",
                "goals": 10,
                "selected_for_game": True
            },
            {
                "type": "Player",
                "name": "Unselected Player",
                "birthdate": "01.01.1990",
                "goals": 15
            }
        ]
        self.create_test_file(content)
        team = Team(self.test_file)

        import io
        import sys
        captured_output = io.StringIO()
        sys.stdout = captured_output
        
        team.show_selected_players()
        sys.stdout = sys.__stdout__
        
        output = captured_output.getvalue()
        self.assertIn("Selected Player", output)
        self.assertNotIn("Unselected Player", output)

    def test_exceptions(self):
        """Test various exception cases."""
        # test invalid type
        with self.assertRaises(InvalidTypeError):
            self.create_test_file([])
            team = Team(self.test_file)
            team.add_member("InvalidType", "Test Name", "01.01.1990", 10)

        # test empty name
        with self.assertRaises(InvalidNameError):
            content = [{
                "type": "Player",
                "name": "",
                "birthdate": "01.01.1990",
                "goals": 10
            }]
            self.create_test_file(content)
            Team(self.test_file)

    def test_menu_dependency(self):
        """Test team interactions through menu-like operations."""
        self.create_test_file([])
        team = Team(self.test_file)

        
        # test sequence of operations
        team.add_member("Player", "Test Player", "01.01.1990", 10)
        team.view_team()
        team.find_youngest_oldest_player()
        
        #is it waiting to do line by line?

        import builtins
        original_input = builtins.input
        builtins.input = lambda _: "1"
        team.select_player()
        builtins.input = original_input
        
        team.show_selected_players()

        # verify final state
        with open(self.test_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        self.assertEqual(len(data), 1)
        self.assertTrue(data[0].get("selected_for_game", False))

if __name__ == '__main__':
    
    
    # run tests with verbose output
    unittest.main(verbosity=2)