CC      := clang
CFLAGS  := -std=c99 -Wall -Wextra -pedantic -O3 -Isrc
LDFLAGS := -framework AudioToolbox \
           -framework CoreAudio \
           -framework Foundation \
           -framework AppKit \
           -framework CoreVideo

BUILD   := build
TARGET  := $(BUILD)/psikat
SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:src/%.c=$(BUILD)/%.o)
DEP     := $(OBJ:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(BUILD)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r $(BUILD)

-include $(DEP)