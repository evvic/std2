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
		cd $(BUILD_DIR) && GTEST_OUTPUT=xml:test-results/ GTEST_COLOR=1 ctest --output-on-failure -V -R "UniquePointerTest"; \
	fi

vector: configure
	@cd $(BUILD_DIR) && cmake --build . --target vector vector_tests
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && GTEST_OUTPUT=xml:test-results/ GTEST_COLOR=1 ctest --output-on-failure -V -R "VectorTest|AllocatorTest"; \
	fi

std2: configure
	@cd $(BUILD_DIR) && cmake --build . --target std2
	@if [ "$(UNITTEST)" = "true" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure -R "^std2"; \
	fi

# Run all unit tests explicitly
unittest: all
	@cd $(BUILD_DIR) && cmake .. -DUNITTEST=true
	@cd $(BUILD_DIR) && cmake --build . --target memory_tests vector_tests
	@cd $(BUILD_DIR) && ctest --output-on-failure

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
