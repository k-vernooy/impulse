BUILD := build
OBJECTS := $(BUILD)/main.o
HEADERS := 
CC := g++
CV := -std=c++11

all: compile
compile: setup $(OBJECTS)
	$(CC) $(CV) $(OBJECTS) -o bin/impulse

# object file targets:
$(BUILD)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@

setup:
	mkdir -p build bin

install:
	@install -m 0755 bin/impulse /usr/local/bin

clean:
	rm -f build/ bin/