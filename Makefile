CC      := clang
CFLAGS  := -std=c99 -Wall -Wextra -pedantic -O3 -Isrc -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lSDL3 -lSDL3_ttf -framework AudioToolbox -framework CoreAudio

BUILD   := build
TARGET  := $(BUILD)/psikat
SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:src/%.c=$(BUILD)/%.o)
DEP     := $(OBJ:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD)

-include $(DEP)