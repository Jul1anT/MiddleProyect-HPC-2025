SOURCES := $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=src/%.o)

all: percolation.x

percolation.x: $(OBJECTS)
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address $^ -o $@

%src/.o: src/%.cpp
	g++ -std=c++17 -O3 -fsanitize=undefined,leak,address $< -c -Isrc -o $@

# Generate probability study data
data/probability_study.txt: percolation.x
	./$< 20 0.0 study > $@

# Create plots from data
data/percolation_plot.png: scripts/plot_results.gnu data/probability_study.txt
	gnuplot $<

test: percolation.x
	@echo -e "\n== Testing p=0 (should not percolate)"
	./$< 10 0.0 single
	@echo -e "\n== Testing p=1 (should always percolate)"
	./$< 10 1.0 single
	@echo -e "\n== Testing p=0.6 (random case)"
	./$< 10 0.6 single

study: data/probability_study.txt

plot: data/percolation_plot.png

clean:
	rm -f *.o *.x data/*.txt data/*.png