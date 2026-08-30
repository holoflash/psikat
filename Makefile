CC      := gcc
CFLAGS  := -std=c99 -Wall -Wextra -pedantic -O3
LDFLAGS := -framework AudioToolbox -framework CoreAudio

TARGET  := build/psikat
SRC     := $(wildcard src/*.c)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

build:
	mkdir -p build

run: all
	@./$(TARGET)

clean:
	rm -rf build