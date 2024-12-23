import json
from datetime import datetime
from player import Player
from coach import Coach

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