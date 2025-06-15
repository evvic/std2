# Convenience Makefile for building std2 library components

BUILD_DIR = build
UNITTEST ?= false

.PHONY: all clean memory vector std2 unittest

all: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build .
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure; \
	fi

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build targets with optional testing
memory: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DTEST=$(UNITTEST) && cmake --build . --target memory memory_tests
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "UniquePointerTest"; \
	fi

vector: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build . --target vector
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "^vector"; \
	fi

std2: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build . --target std2
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "^std2"; \
	fi

# Run all tests explicitly
unittest: $(BUILD_DIR)
	@cd $(BUILD_DIR) && ctest --output-on-failure

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
