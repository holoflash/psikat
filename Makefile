CC      := clang
CFLAGS  := -std=c99 -Wall -Wextra -pedantic -O3 -Isrc
LDFLAGS := -lncurses -framework AudioToolbox -framework CoreAudio
BUILD   := build
OBJ     := $(BUILD)/obj
TARGET  := $(BUILD)/psikat
SRC     := $(wildcard src/*.c)
OBJS    := $(patsubst src/%.c, $(OBJ)/%.o, $(SRC))

.PHONY: all run clean

all: $(TARGET)

$(OBJ)/%.o: src/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJ):
	mkdir -p $(OBJ)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD)