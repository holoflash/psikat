CC      := clang
CFLAGS  := -Wall -Wextra -pedantic -O3 -Isrc
LDFLAGS := -framework AudioToolbox \
           -framework CoreAudio \
           -framework Foundation \
           -framework AppKit \
           -framework CoreVideo

BUILD   := build
TARGET  := $(BUILD)/psikat

C_SRC   := $(wildcard src/*.c)
M_SRC   := $(wildcard src/*.m)

OBJ     := $(C_SRC:src/%.c=$(BUILD)/%.o) $(M_SRC:src/%.m=$(BUILD)/%.o)
DEP     := $(OBJ:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(BUILD)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -std=c99 $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.o: src/%.m
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -fno-objc-arc -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r $(BUILD)

-include $(DEP)