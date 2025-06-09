SOURCES := src/main.cpp src/percolation.cpp src/statistic.cpp
OBJECTS = $(SOURCES:src/%.cpp=src/%.o)

all: percolation.x

percolation.x: $(OBJECTS)
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address $^ -o $@

src/%.o: src/%.cpp src/percolation.h
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address $< -c -Isrc -o $@

test.x: src/test.cpp src/percolation.cpp src/statistic.cpp src/percolation.h
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address src/test.cpp src/percolation.cpp src/statistic.cpp -o $@ -Isrc

test: test.x
	@echo "Running tests..."
	./test.x
	@echo "Tests completed."

data/probability_study.txt: percolation.x
	./$< 20 0.0 study > $@

data/percolation_plot.png: scripts/plot_results.gnu data/probability_study.txt
	gnuplot $<

study: data/probability_study.txt

plot: data/percolation_plot.png

clean:
	rm -f src/*.o *.x data/*.txt data/*.png

.PHONY: all test study plot clean