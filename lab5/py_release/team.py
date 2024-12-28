import json
import threading
import os
from datetime import datetime
from exceptions import FileLoadError, InvalidTypeError, InvalidNameError, InvalidDateError, InvalidGoalsError

class Team:
    _file_lock = threading.Lock()
    
    def __init__(self, filename='team_members.json'):
        self.filename = filename
        self.members = self.load_members()

    def load_members(self):
        with self._file_lock:
            try:
                # Handle case where file doesn't exist yet
                if not os.path.exists(self.filename):
                    return []
                    
                with open(self.filename, 'r', encoding='utf-8') as file:
                    data = json.load(file)
                    for index, member in enumerate(data, 1):
                        # Validate member type
                        if member['type'] not in ['Player', 'Coach']:
                            raise InvalidTypeError(member['type'], index)
                
                        # Validate name
                        if not member['name'] or member['name'].strip() == '':
                            raise InvalidNameError(index)
                
                        # Validate birthdate
                        try:
                            parsed_date = datetime.strptime(member['birthdate'], "%d.%m.%Y")
                            formatted_date = parsed_date.strftime('%d.%m.%Y')
                            if member['birthdate'] != formatted_date:
                                raise InvalidDateError('birthdate', index)
                        except ValueError:
                            raise InvalidDateError('birthdate', index)
                
                        # Validate goals for players
                        if member['type'] == 'Player':
                            goals = member.get('goals')
                            if goals is None or (
                                not isinstance(goals, (int, str)) or 
                                (isinstance(goals, str) and not goals.isdigit()) or
                                (isinstance(goals, int) and goals < 0)
                                ):
                                    raise InvalidGoalsError('goals', index)
                
                return data
            
            except FileNotFoundError:
                return []  # Return empty list instead of raising error
            except json.JSONDecodeError:
                raise FileLoadError(self.filename) from None
            except (InvalidTypeError, InvalidNameError, InvalidDateError, InvalidGoalsError) as e:
                print(e)
                exit(1)

    def save_members(self):
        with self._file_lock:
            with open(self.filename, 'w', encoding='utf-8') as file:
                json.dump(self.members, file, ensure_ascii=False, indent=2)

    def add_member(self, member_type, name, birthdate, additional_info):
        if not name or name.strip() == '':
            raise InvalidNameError(len(self.members) + 1)
            
        new_member = {
            'type': member_type,
            'name': name,
            'birthdate': birthdate
        }
        
        if member_type == 'Player':
            new_member['goals'] = additional_info
        elif member_type == 'Coach':
            new_member['category'] = additional_info
        else:
            raise InvalidTypeError(member_type, len(self.members) + 1)
        
        with self._file_lock:
            try:
                # Load current data
                current_data = self.load_members()
                current_data.append(new_member)
                self.members = current_data
                self.save_members()
            except Exception as e:
                # If anything goes wrong, ensure we don't leave the file in a bad state
                self.members = self.load_members()
                raise e

    def view_team(self):
        if not self.members:
            print("Team is empty.")
            return
        
        print("\n--- Team Members ---")
        for member in self.members:
            print(f"\nType: {member['type']}")
            print(f"Name: {member['name']}")
            print(f"Birthdate: {member['birthdate']}")
            
            birth_date = datetime.strptime(member['birthdate'], "%d.%m.%Y")
            today = datetime.now()
            age = today.year - birth_date.year - \
                  ((today.month, today.day) < (birth_date.month, birth_date.day))
            print(f"Age: {age} years")
            
            if member['type'] == 'Player':
                print(f"Goals: {member['goals']}")
            elif member['type'] == 'Coach':
                print(f"Category: {member['category']}")

    def find_youngest_oldest_player(self):
        players = [
            member for member in self.members 
            if member['type'] == 'Player'
        ]
        
        if not players:
            print("There are no players in the team.")
            return
        
        players_with_dates = [
            {**player, 'birth_date': datetime.strptime(player['birthdate'], "%d.%m.%Y")} 
            for player in players
        ]
        
        youngest = max(players_with_dates, key=lambda x: x['birth_date'])
        oldest = min(players_with_dates, key=lambda x: x['birth_date'])
        
        print("\n--- Youngest and Oldest Player ---")
        print(f"Youngest Player:")
        print(f"Name: {youngest['name']}")
        print(f"Birthdate: {youngest['birthdate']}")
        
        today = datetime.now()
        age = today.year - youngest['birth_date'].year - \
              ((today.month, today.day) < (youngest['birth_date'].month, youngest['birth_date'].day))
        print(f"Age: {age}")
        print(f"Goals: {youngest['goals']}")
        
        print(f"\nOldest Player:")
        print(f"Name: {oldest['name']}")
        print(f"Birthdate: {oldest['birthdate']}")
        
        age = today.year - oldest['birth_date'].year - \
              ((today.month, today.day) < (oldest['birth_date'].month, oldest['birth_date'].day))
        print(f"Age: {age}")
        print(f"Goals: {oldest['goals']}")

    def select_player(self):
        players = [member for member in self.members if member['type'] == 'Player']
        if not players:
            print("There are no players in the team.")
            return

        print("\n--- Available Players ---")
        for i, player in enumerate(players, 1):
            status = "Selected" if player.get('selected_for_game', False) else "Available"
            print(f"{i}. {player['name']} (Goals: {player['goals']}) - {status}")

        with self._file_lock:
            try:
                choice = int(input("\nSelect player number (or 0 to cancel): "))
                if choice == 0:
                    return
                if 1 <= choice <= len(players):
                    selected_player = players[choice - 1]
                    if selected_player.get('selected_for_game', False):
                        print(f"{selected_player['name']} is already selected for the game!")
                        return
                    
                    current_data = self.load_members()
                    for member in current_data:
                        if member['name'] == selected_player['name']:
                            member['selected_for_game'] = True
                    self.members = current_data
                    self.save_members()
                    print(f"{selected_player['name']} has been selected for the game!")
                else:
                    print("Invalid player number!")
            except ValueError:
                print("Please enter a valid number!")

    def show_selected_players(self):
        selected_players = [
            member for member in self.members 
            if member['type'] == 'Player' and member.get('selected_for_game', False)
        ]
        
        if not selected_players:
            print("No players selected for the game yet!")
            return
        
        print("\n--- Players Selected for Game ---")
        for player in selected_players:
            print(f"Name: {player['name']}")
            print(f"Goals: {player['goals']}")
            
            birth_date = datetime.strptime(player['birthdate'], "%d.%m.%Y")
            today = datetime.now()
            age = today.year - birth_date.year - \
                ((today.month, today.day) < (birth_date.month, birth_date.day))
            print(f"Age: {age} years")