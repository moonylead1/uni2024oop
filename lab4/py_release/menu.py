from team import Team

class Menu:
    def __init__(self):
        self.team = Team()
    
    def display_menu_options(self):
        print("\n--- Система управління командою ---")
        print("1. Додати члена команди")
        print("2. Переглянути всіх членів команди")
        print("3. Знайти наймолодшого та найстаршого гравців")
        print("4. Вихід")
    
    def process_user_choice(self, choice):
        if choice == '1':
            self.add_member()
        elif choice == '2':
            self.team.view_team()
        elif choice == '3':
            self.team.find_youngest_oldest_player()
        elif choice == '4':
            return False
        return True
    
    def add_member(self):
        member_type = input("Введіть тип (Гравець/Тренер): ")
        name = input("Введіть ім'я: ")
        birthdate = input("Введіть дату народження (ДД.ММ.РРРР): ")
        
        if member_type == 'Гравець':
            goals = input("Введіть кількість голів у кар'єрі: ")
            self.team.add_member(member_type, name, birthdate, goals)
        elif member_type == 'Тренер':
            category = input("Введіть категорію: ")
            self.team.add_member(member_type, name, birthdate, category)
        
        print("Члена команди додано успішно!")
    
    def run(self):
        while True:
            self.display_menu_options()
            choice = input("Виберіть опцію: ")
            
            if not self.process_user_choice(choice):
                break