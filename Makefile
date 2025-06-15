# Convenience Makefile for building std2 library components

BUILD_DIR = build

.PHONY: all clean memory vector std2

all: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build .

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

memory: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build . --target memory

vector: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build . --target vector

std2: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build . --target std2

clean:
	@rm -rf $(BUILD_DIR)
