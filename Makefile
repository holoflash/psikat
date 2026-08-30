CC          := clang
SWIFTC      := swiftc
CFLAGS      := -std=c99 -Wall -Wextra -pedantic -O3 -Iinclude
LDFLAGS     := -framework AudioToolbox -framework CoreAudio -framework SwiftUI -framework AppKit
APP_NAME    := psikat
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj
BUNDLE_DIR  := $(BUILD_DIR)/$(APP_NAME).app
CONTENTS_DIR:= $(BUNDLE_DIR)/Contents
MACOS_DIR   := $(CONTENTS_DIR)/MacOS
TARGET      := $(MACOS_DIR)/$(APP_NAME)
C_SRC       := $(wildcard src/*.c)
C_OBJS      := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(C_SRC))
SWIFT_SRC   := Swift/App.swift

.PHONY: all run clean

all: $(TARGET)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(C_OBJS) $(SWIFT_SRC) Info.plist | $(MACOS_DIR)
	$(SWIFTC) -parse-as-library -I . \
		$(C_OBJS) \
		$(SWIFT_SRC) \
		$(LDFLAGS) \
		-o $@
	cp Info.plist $(CONTENTS_DIR)/Info.plist

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MACOS_DIR):
	mkdir -p $(MACOS_DIR)

run: all
	open $(BUNDLE_DIR)

clean:
	rm -rf $(BUILD_DIR)