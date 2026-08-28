CC        := gcc
CFLAGS    := -std=c99 -Wall -Wextra -pedantic -O3
LDFLAGS   := -framework AudioToolbox -framework CoreAudio

BUILD_DIR := build
TARGET    := $(BUILD_DIR)/psikat
SRC       := main.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	@$(TARGET)

clean:
	rm -rf $(BUILD_DIR)