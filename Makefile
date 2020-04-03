BUILD := build
OBJECTS := $(BUILD)/main.o $(BUILD)/audio.o
HEADERS := 
CC := g++
CV := -std=c++11

all: compile
compile: setup $(OBJECTS) fft
	$(CC) $(CV) $(OBJECTS) $(BUILD)/fft.o -o bin/impulse

$(BUILD)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CV) $< -c -o $@

fft: lib/fft/fft.cpp
	$(CC) $(CV) lib/fft/fft.cpp -c -o $(BUILD)/fft.o

setup:
	mkdir -p build bin

install:
	@install -m 0755 bin/impulse /usr/local/bin

clean:
	rm -f build/ bin/