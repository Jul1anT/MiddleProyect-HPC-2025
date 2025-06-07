CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = percolation
SRCDIR = src
INCDIR = include
DATADIR = data
RESULTSDIR = $(DATADIR)/results

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run test study directories

all: directories $(TARGET)

directories:
	@mkdir -p $(RESULTSDIR)
	@mkdir -p $(DATADIR)/input
	@mkdir -p docs

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Run single simulation
run: $(TARGET)
	./$(TARGET) 20 0.6

# Calculate probability for specific parameters
prob: $(TARGET)
	./$(TARGET) 20 0.6 prob

# Run complete probability study
study: $(TARGET)
	./$(TARGET) 20 0.0 study

# Run unit tests (simple version)
test: $(TARGET)
	@echo "Running basic tests..."
	@echo "Test 1: p=0 (should not percolate)"
	@./$(TARGET) 10 0.0 single
	@echo "\nTest 2: p=1 (should always percolate)"
	@./$(TARGET) 10 1.0 single
	@echo "\nTest 3: p=0.6 (may or may not percolate)"
	@./$(TARGET) 10 0.6 single

# Plot results using gnuplot
plot: 
	@if [ -f $(RESULTSDIR)/probability_study.txt ]; then \
		gnuplot scripts/plot_results.gnu; \
		echo "Plot saved to $(RESULTSDIR)/percolation_plot.png"; \
	else \
		echo "No data found. Run 'make study' first."; \
	fi

# Clean build files
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
	rm -f $(RESULTSDIR)/*.txt $(RESULTSDIR)/*.png

# Deep clean (remove all generated files and directories)
distclean: clean
	rm -rf $(DATADIR) docs/*.pdf

help:
	@echo "Available targets:"
	@echo "  all      - Build the project"
	@echo "  run      - Run single simulation (L=20, p=0.6)"
	@echo "  prob     - Calculate percolation probability"
	@echo "  study    - Run complete probability study"
	@echo "  test     - Run basic unit tests"
	@echo "  plot     - Generate plots from study results"
	@echo "  clean    - Remove build files"
	@echo "  distclean- Remove all generated files"
	@echo "  help     - Show this help message"