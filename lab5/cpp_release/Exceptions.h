#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class ExceptionError : public std::exception {
protected:
    std::string msg;

public:
    explicit ExceptionError(std::string msg) : msg(std::move(msg)) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Base class for all team-related errors
class TeamError : public ExceptionError {
public:
    explicit TeamError(const std::string& message) 
        : ExceptionError("Team Error: " + message) {}
};

// File handling errors
class FileLoadError : public ExceptionError { 
public:
    explicit FileLoadError(const std::string& filepath)
        : ExceptionError("Failed to load file: " + filepath) {}
};

class FileParseError : public ExceptionError { 
public:
    explicit FileParseError(const std::string& field)
        : ExceptionError("Failed to parse field: " + field) {}
};

// Member data validation errors
class InvalidTypeError : public TeamError {
public:
    explicit InvalidTypeError(const std::string& type, int line) 
        : TeamError("Invalid member type '" + type + "' at line " + std::to_string(line)) {}
};

class InvalidDateError : public TeamError {
public:
    explicit InvalidDateError(const std::string& date, int line)
        : TeamError("Invalid date format '" + date + "' at line " + std::to_string(line)) {}
};

class InvalidGoalsError : public TeamError {
public:
    explicit InvalidGoalsError(const std::string& goals, int line)
        : TeamError("Invalid goals value '" + goals + "' at line " + std::to_string(line)) {}
};

class EmptyNameError : public TeamError {
public:
    explicit EmptyNameError(int line)
        : TeamError("Empty name field at line " + std::to_string(line)) {}
};

class InvalidFormatError : public TeamError {
public:
    explicit InvalidFormatError(int line)
        : TeamError("Invalid format at line " + std::to_string(line)) {}
};

#endif // EXCEPTIONS_H