class ExceptionError(Exception):
    """Base class for custom exceptions"""
    def __init__(self, msg):
        super().__init__(msg)
        self.msg = msg

class TeamError(ExceptionError):
    """Base class for all team-related errors"""
    def __init__(self, message):
        super().__init__(f"Team Error: {message}")

class FileLoadError(ExceptionError):
    """Exception raised for file loading errors"""
    def __init__(self, filepath):
        super().__init__(f"Failed to load file: {filepath}")

class FileParseError(ExceptionError):
    """Exception raised for file parsing errors"""
    def __init__(self, field):
        super().__init__(f"Failed to parse field: {field}")

class InvalidTypeError(TeamError):
    """Exception raised for invalid type errors"""
    def __init__(self, type, line):
        super().__init__(f"Invalid member type '{type}' at line {line}")

class InvalidDateError(TeamError):
    """Exception raised for invalid date errors"""
    def __init__(self, date, line):
        super().__init__(f"Invalid date format '{date}' at line {line}")

class InvalidGoalsError(TeamError):
    """Exception raised for invalid goals errors"""
    def __init__(self, goals, line):
        super().__init__(f"Invalid goals value '{goals}' at line {line}")

class InvalidNameError(TeamError):
    """Exception raised for empty name errors"""
    def __init__(self, line):
        super().__init__(f"Empty name field at line {line}")

class InvalidFormatError(TeamError):
    """Exception raised for invalid format errors"""
    def __init__(self, line):
        super().__init__(f"Invalid format at line {line}")


