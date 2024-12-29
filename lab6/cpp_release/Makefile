CXX = g++
CXXFLAGS = -std=c++14 -I./include -Wall
SRCDIR = src
SOURCES = $(SRCDIR)/User.cpp $(SRCDIR)/main.cpp
TARGET = user_management.exe

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	del $(TARGET)