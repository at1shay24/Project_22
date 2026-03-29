# Runs on Linux and Windows by Murphy Jacob
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = client_database.exe
SRCS = main.cpp Address.cpp CountyList.cpp Date.cpp DateList.cpp DriverDatabase.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)
	@echo Build complete! Executable: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Windows clean command
clean:
	@echo Cleaning up...
	@if exist *.o del /Q *.o 2>nul || ver>nul
	@if exist $(TARGET) del /Q $(TARGET) 2>nul || ver>nul
	@echo Clean complete!

# Run the program
run: $(TARGET)
	@echo Running program...
	@$(TARGET)

# Show help
help:
	@echo Available targets:
	@echo   make all    - Build the program
	@echo   make clean  - Remove object files and executable
	@echo   make run    - Run the program
	@echo   make help   - Show this help message

.PHONY: all clean run help