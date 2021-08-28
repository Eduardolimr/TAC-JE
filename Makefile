INC_DIR := include
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_NO_DIR := $(notdir $(SRC_FILES))
OBJ_FILES := $(SRC_NO_DIR:%.cpp=$(OBJ_DIR)/%.o) 
DEP_FILES := $(OBJ_FILES:.o=.d)
MAIN_FILE := $(OBJ_FILES) $(DEP_FILES) main
INC_PATHS := -Iinclude -Iinclude/SDL

EXEC   := Jogo
OUTPUT := $(BIN_DIR)/$(EXEC)

CC       := g++
CPPFLAGS := -MMD -MP 
DFLAGS   := -g -Wall -pedantic

OUTPUT_OPTION := $(CPPFLAGS) $(DFLAGS)

LIB_DIR := -L./lib
LIBS   := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

ifeq ($(OS),Windows_NT)

LIBS := -lmingw32 -lSDL2main $(LIBS)
OUTPUT := $(OUTPUT).exe

else

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

$(OUTPUT): $(OBJ_FILES)
	@echo OBJ_FILES: $(OBJ_FILES)
	$(LINK.o) $^ $(INC_PATHS) $(LIB_DIR) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@echo $<
	$(COMPILE.c) -o $@ $(INC_PATHS) $(OUTPUT_OPTION) $<

clean:
	rm $(MAIN_FILE)
	@rmdir $(OBJ_DIR)

-include $(deps)