CXX := g++
CXXFLAGS := -std=c++2b $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --cflags) -Wall -Wextra
LDFLAGS := $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs) -lallegro_main -lallegro_ttf -lstdc++

TARGET := main
SRC_DIR := src
BUILD_DIR := build
MKDIR_P := mkdir -p

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SOURCES:$(SRC_DIR)/%.cpp=%.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Édition des liens et création du binaire : $@"
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR_P) $(dir $@)
	@echo "Compilation : $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	@echo "Exécution du programme..."
	./$(TARGET)

.PHONY: clean
clean:
	@echo "Nettoyage des fichiers objets et binaires..."
	-rm -rf $(BUILD_DIR) $(TARGET)
