import json
import os

class UserManager:
    def __init__(self, file_path="member_list.json"):
        self.file_path = file_path
        self.users = self.load_users()

    def load_users(self):
        """Load users from JSON file. Create file if it doesn't exist."""
        if not os.path.exists(self.file_path):
            with open(self.file_path, 'w') as f:
                json.dump([], f, indent=4)
            return []
        
        with open(self.file_path, 'r') as f:
            return json.load(f)

    def save_users(self):
        """Save users to JSON file."""
        with open(self.file_path, 'w') as f:
            json.dump(self.users, f, indent=4)

    def find_user(self, email):
        """Find user by email."""
        for user in self.users:  # Now directly iterating over the list
            if user["email"] == email:
                return user
        return None

    def register(self, user_id, name, email, role="user"):
        """Register a new user."""
        if self.find_user(email):
            return False, "User already exists"
        
        new_user = {
            "id": user_id,
            "name": name,
            "email": email,
            "role": role,
            "status": "up"
        }
        
        self.users.append(new_user)  # Append to list directly
        self.save_users()
        return True, "User registered successfully"

    def login(self, email):
        """Login user and set status to 'up'."""
        user = self.find_user(email)
        if not user:
            return False, "User not found"
        
        user["status"] = "up"
        self.save_users()
        return True, "Login successful"

    def logout(self, email):
        """Logout user and set status to 'down'."""
        user = self.find_user(email)
        if not user:
            return False, "User not found"
        
        user["status"] = "down"
        self.save_users()
        return True, "Logout successful"