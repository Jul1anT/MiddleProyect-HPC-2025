SOURCES := src/main.cpp src/percolation.cpp src/statistic.cpp
OBJECTS = $(SOURCES:src/%.cpp=src/%.o)

all: percolation.x

percolation.x: $(OBJECTS)
	g++ -std=c++17 -O2 -fsanitize=undefined,leak,address $^ -o $@

src/%.o: src/%.cpp src/percolation.h
	g++ -std=c++17 -O2 -fsanitize=undefined,leak,address $< -c -Isrc -o $@

test.x: src/test.cpp src/percolation.cpp src/statistic.cpp src/percolation.h
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address src/test.cpp src/percolation.cpp src/statistic.cpp -o $@ -Isrc

.PHONY: all test clean run-single run-prob run-study run-full

test: test.x
	@echo "Running tests..."
	./test.x
	@echo "Tests completed."

clean:
	rm -f src/*.o *.x 

clean-all:
	rm -f src/*.o *.x data/*.txt data/*.png

run-single: percolation.x
	./$< 20 0.5

run-study: percolation.x
	./$<