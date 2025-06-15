# Convenience Makefile for building std2 library components

BUILD_DIR = build
UNITTEST ?= false

.PHONY: all clean memory vector std2 unittest configure

configure: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DUNITTEST=$(UNITTEST)

all: configure
	@cd $(BUILD_DIR) && cmake --build .
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure; \
	fi

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build targets with optional testing
memory: configure
	@cd $(BUILD_DIR) && cmake --build . --target memory memory_tests
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "UniquePointerTest"; \
	fi

vector: configure
	@cd $(BUILD_DIR) && cmake --build . --target vector
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "^vector"; \
	fi

std2: configure
	@cd $(BUILD_DIR) && cmake --build . --target std2
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "^std2"; \
	fi

# Run all tests explicitly
unittest: configure
	@cd $(BUILD_DIR) && \
	cmake --build . --target memory_tests && \
	ctest --output-on-failure

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
