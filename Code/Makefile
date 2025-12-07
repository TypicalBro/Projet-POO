# Compilateur et options
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude -Iinclude/core -Iinclude/view

# Librairies SFML (modifie si besoin selon ton install)
LIBS_SFML := -lsfml-graphics -lsfml-window -lsfml-system

# Cibles
TARGET_CONSOLE := game_console
TARGET_SFML    := game_sfml
TARGET_TEST    := game_test

# Sources
CORE_SRCS      := $(wildcard src/core/*.cpp)
VIEW_SRCS      := $(wildcard src/view/*.cpp)
CONSOLE_MAIN   := app/main_console.cpp
SFML_MAIN      := app/main_sfml.cpp
TEST_MAIN      := app/test_main.cpp

# Objets
CORE_OBJS      := $(CORE_SRCS:.cpp=.o)
VIEW_OBJS      := $(VIEW_SRCS:.cpp=.o)
CONSOLE_OBJ    := $(CONSOLE_MAIN:.cpp=.o)
SFML_OBJ       := $(SFML_MAIN:.cpp=.o)
TEST_OBJ       := $(TEST_MAIN:.cpp=.o)


# Règle par défaut : on compile la version console
all: $(TARGET_CONSOLE)

# Cible explicite pour la version console
console: $(TARGET_CONSOLE)

# Cible explicite pour la version SFML
sfml: $(TARGET_SFML)

# Edition de liens :
$(TARGET_CONSOLE): $(CORE_OBJS) $(VIEW_OBJS) $(CONSOLE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_SFML)

$(TARGET_SFML): $(CORE_OBJS) $(VIEW_OBJS) $(SFML_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_SFML)

$(TARGET_TEST): $(CORE_OBJS) $(VIEW_OBJS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_SFML)


# Règle générique de compilation (.cpp -> .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(CORE_OBJS) $(VIEW_OBJS) $(CONSOLE_OBJ) $(SFML_OBJ) $(TARGET_CONSOLE) $(TARGET_SFML)

.PHONY: all console sfml clean
