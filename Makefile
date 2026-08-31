CC      := clang
CFLAGS  := -std=c99 -Wall -Wextra -pedantic -O3 -Isrc
LDFLAGS := -lncurses -framework AudioToolbox -framework CoreAudio
BUILD   := build
TARGET  := $(BUILD)/psikat
SRC     := $(wildcard src/*.c)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD)