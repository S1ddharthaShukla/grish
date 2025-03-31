# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude
LDFLAGS =

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN = grisha

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: banner $(BIN)

# Link object files into final binary
$(BIN): $(OBJS)
	@echo "🔧 Linking..."
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✅ Build complete."

# Compile each .c into a .o in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "📦 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Clean build artifacts
clean:
	@echo "🧹 Cleaning up..."
	@rm -rf $(BUILD_DIR) $(BIN)

# Build banner
banner:
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "🔥 Building grish(a) — AoT-themed Shell"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Phony targets
.PHONY: all clean debug banner
# Prevent make from confusing files with directories
