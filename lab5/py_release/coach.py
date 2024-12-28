from team_member import TeamMember

class Coach(TeamMember):
    def __init__(self, name, birthdate, category):
        super().__init__(name, birthdate)
        self.category = category
    
    def get_type(self):
        return "Тренер"
