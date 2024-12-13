from abc import ABC, abstractmethod
from datetime import datetime

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