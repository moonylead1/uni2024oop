from team_member import TeamMember

class Player(TeamMember):
    def __init__(self, name, birthdate, goals):
        super().__init__(name, birthdate)
        self.goals = int(goals)
    
    def get_type(self):
        return "Гравець"