from team import Team
from datetime import datetime
from exceptions import InvalidGoalsError, InvalidNameError, InvalidDateError, InvalidTypeError
class Menu:
    def __init__(self):
        self.team = Team()
    
    def display_menu_options(self):
        print("\n--- Team Management System ---")
        print("1. Add Team Member")
        print("2. View Team Members")
        print("3. Show Youngest and Oldest Player")
        print("4. Select Player for Game")
        print("5. Show Selected Players")
        print("6. Exit")
    
    def process_user_choice(self, choice):
        if choice == '1':
            self.add_member()
        elif choice == '2':
            self.team.view_team()
        elif choice == '3':
            self.team.find_youngest_oldest_player()
        elif choice == '4':
            self.team.select_player()
        elif choice == '5':
            self.team.show_selected_players()
        elif choice == '6':
            return False
        return True
    
    def add_member(self):
        try:
            member_type = input("Enter member type (Player/Coach): ")
            if member_type not in ['Player', 'Coach']:
                raise InvalidTypeError(member_type, 1)
                
            name = input("Enter name: ")
            if not name:
                raise InvalidNameError('name', 2)
                
            birthdate = input("Enter birthdate (DD.MM.YYYY): ")
            if birthdate != datetime.strptime(birthdate, "%d.%m.%Y").strftime('%d.%m.%Y'):
                raise ValueError
                
            if member_type == 'Player':
                goals = input("Enter number of goals in career: ")
                if not goals.isdigit():
                    raise InvalidGoalsError('goals', 4)
                self.team.add_member(member_type, name, birthdate, int(goals))
            elif member_type == 'Coach':
                self.team.add_member(member_type, name, birthdate, category)
        except InvalidTypeError as e:
            print(e)
        except InvalidNameError as e:
            print(e)
        except InvalidGoalsError as e:
            print(e)
        except InvalidDateError as e:
            print(e)
        except ValueError as e:
            print(InvalidDateError(birthdate, 3))
        else:
            print("Member added successfully!")
        

    def run(self):
        while True:
            self.display_menu_options()
            choice = input("Choose an option: ")
            
            if not self.process_user_choice(choice):
                break