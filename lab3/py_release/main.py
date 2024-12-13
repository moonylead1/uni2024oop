import json
from datetime import datetime
from abc import ABC, abstractmethod

class Menu:
    def display_main_menu(self):
        print("\n--- Team Management System ---")
        print("1. Add Team Member")
        print("2. View Team Members")
        print("3. Find Youngest and Oldest Players")
        print("4. Exit")

    def get_user_choice(self):
        return int(input("Select an option: "))

    def add_team_member(self, team, file_manager):
        member_type = input("Enter member type (Player/Coach): ")
        name = input("Enter name: ")
        birthdate = input("Enter birthdate (DD.MM.YYYY): ")

        if member_type == "Player":
            goals = int(input("Enter number of goals in career: "))
            team.add_player(name, birthdate, goals)
        elif member_type == "Coach":
            category = input("Enter category: ")
            team.add_coach(name, birthdate, category)

        file_manager.save_team_members(team.get_members())
        print("Team member added successfully!")


class TeamMember(ABC):
    def __init__(self, name, birthdate):
        self.name = name
        self.birthdate = datetime.strptime(birthdate, "%d.%m.%Y")
    
    @abstractmethod
    def get_type(self):
        pass
    
    def get_age(self):
        today = datetime.now()
        age = today.year - self.birthdate.year - \
              ((today.month, today.day) < (self.birthdate.month, self.birthdate.day))
        return age

class Player(TeamMember):
    def __init__(self, name, birthdate, goals):
        super().__init__(name, birthdate)
        self.goals = int(goals)
    
    def get_type(self):
        return "Гравець"

class Coach(TeamMember):
    def __init__(self, name, birthdate, category):
        super().__init__(name, birthdate)
        self.category = category
    
    def get_type(self):
        return "Тренер"

class Team:
    def __init__(self, filename='team_members.json'):
        self.filename = filename
        self.members = self.load_members()
    
    def load_members(self):
        try:
            with open(self.filename, 'r', encoding='utf-8') as file:
                return json.load(file)
        except FileNotFoundError:
            return []
    
    def save_members(self):
        with open(self.filename, 'w', encoding='utf-8') as file:
            json.dump(self.members, file, ensure_ascii=False, indent=2)
    
    def add_member(self, member_type, name, birthdate, additional_info):
        new_member = {
            'type': member_type,
            'name': name,
            'birthdate': birthdate
        }
        
        if member_type == 'Гравець':
            new_member['goals'] = additional_info
        elif member_type == 'Тренер':
            new_member['category'] = additional_info
        
        self.members.append(new_member)
        self.save_members()
    
    def view_team(self):
        if not self.members:
            print("Команда порожня.")
            return
        
        print("\n--- Члени команди ---")
        for member in self.members:
            print(f"\nТип: {member['type']}")
            print(f"Ім'я: {member['name']}")
            print(f"Дата народження: {member['birthdate']}")
            
            # Розрахунок віку
            birth_date = datetime.strptime(member['birthdate'], "%d.%m.%Y")
            today = datetime.now()
            age = today.year - birth_date.year - \
                  ((today.month, today.day) < (birth_date.month, birth_date.day))
            print(f"Вік: {age} років")
            
            if member['type'] == 'Гравець':
                print(f"Голів у кар'єрі: {member['goals']}")
            elif member['type'] == 'Тренер':
                print(f"Категорія: {member['category']}")
    
    def find_youngest_oldest_player(self):
        players = [
            member for member in self.members 
            if member['type'] == 'Гравець'
        ]
        
        if not players:
            print("В команді немає гравців.")
            return
        
        # Перетворення дат народження
        players_with_dates = [
            {**player, 'birth_date': datetime.strptime(player['birthdate'], "%d.%m.%Y")} 
            for player in players
        ]
        
        # Знаходження наймолодшого та найстаршого
        youngest = max(players_with_dates, key=lambda x: x['birth_date'])
        oldest = min(players_with_dates, key=lambda x: x['birth_date'])
        
        print("\n--- Наймолодший та найстарший гравці ---")
        print(f"Наймолодший гравець:")
        print(f"Ім'я: {youngest['name']}")
        print(f"Дата народження: {youngest['birthdate']}")
        
        today = datetime.now()
        age = today.year - youngest['birth_date'].year - \
              ((today.month, today.day) < (youngest['birth_date'].month, youngest['birth_date'].day))
        print(f"Вік: {age} років")
        print(f"Голів у кар'єрі: {youngest['goals']}")
        
        print("\nНайстарший гравець:")
        print(f"Ім'я: {oldest['name']}")
        print(f"Дата народження: {oldest['birthdate']}")
        
        age = today.year - oldest['birth_date'].year - \
              ((today.month, today.day) < (oldest['birth_date'].month, oldest['birth_date'].day))
        print(f"Вік: {age} років")
        print(f"Голів у кар'єрі: {oldest['goals']}")

def main():
    team = Team()
    
    while True:
        print("\n--- Система управління командою ---")
        print("1. Додати члена команди")
        print("2. Переглянути всіх членів команди")
        print("3. Знайти наймолодшого та найстаршого гравців")
        print("4. Вихід")
        
        choice = input("Виберіть опцію: ")
        
        if choice == '1':
            member_type = input("Введіть тип (Гравець/Тренер): ")
            name = input("Введіть ім'я: ")
            birthdate = input("Введіть дату народження (ДД.ММ.РРРР): ")
            
            if member_type == 'Гравець':
                goals = input("Введіть кількість голів у кар'єрі: ")
                team.add_member(member_type, name, birthdate, goals)
            elif member_type == 'Тренер':
                category = input("Введіть категорію: ")
                team.add_member(member_type, name, birthdate, category)
            
            print("Члена команди додано успішно!")
        
        elif choice == '2':
            team.view_team()
        
        elif choice == '3':
            team.find_youngest_oldest_player()
        
        elif choice == '4':
            break
        else:
            print("Невірний вибір. Спробуйте знову.")

if __name__ == "__main__":
    main()