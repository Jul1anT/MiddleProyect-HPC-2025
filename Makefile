SOURCES := src/main.cpp src/percolation.cpp src/statistic.cpp
OBJECTS = $(SOURCES:src/%.cpp=src/%.o)
OBJECTSGDB = $(SOURCES:src/%.cpp=src/%_gdb.o)
OBJECTSVGD = $(SOURCES:src/%.cpp=src/%_vgd.o)
OBJECTSPRO = $(SOURCES:src/%.cpp=src/%_pro.o)

all: percolation.x

percolation.x: $(OBJECTS)
    g++ -std=c++17 -O2 -fsanitize=undefined,leak,address $^ -o $@

src/%.o: src/%.cpp src/percolation.h
    g++ -std=c++17 -O2 -fsanitize=undefined,leak,address $< -c -Isrc -o $@

test.x: src/test.cpp src/percolation.cpp src/statistic.cpp src/percolation.h
    g++ -std=c++17 -O3 -fsanitize=undefined,leak,address src/test.cpp src/percolation.cpp src/statistic.cpp -o $@ -Isrc

.PHONY: all test clean run-single run-prob run-study run-full debug-gdb do-valgrind do-profile

test: test.x
    @echo "Running tests..."
    ./test.x
    @echo "Tests completed."

clean:
    rm -f src/*.o *.x 

clean-all:
    rm -f src/.o *.x data/*.txt gmon.out

simul: percolation.x
    ./$< 4 0.6 

run-study: percolation.x
    ./$<
	parallel sort -n -o study_L{}.txt study_L{}.txt ::: 32 64 128 256 512

valgrind: percolation_vgd.x
    valgrind --tool=memcheck --leak-check=yes ./percolation_vgd.x 6 0.6

percolation_vgd.x: $(OBJECTSVGD)
    g++ -std=c++17  $^ -o $@

src/%_vgd.o: src/%.cpp src/percolation.h
    g++ -std=c++17  $< -c -Isrc -o $@

debug: percolation_debug.x
    gdb ./percolation_debug.x -ex "run 6 0.6" -ex "q"

percolation_debug.x: $(OBJECTSGDB)
    g++ -std=c++17 -g -ggdb -fsanitize=undefined,leak,address $^ -o $@

src/%_gdb.o: src/%.cpp src/percolation.h
    g++ -std=c++17 -g -ggdb -fsanitize=undefined,leak,address $< -c -Isrc -o $@

profile: percolation_profile.x
    ./percolation_profile.x 8 0.5
    gprof -p percolation_profile.x gmon.out | c++filt > analysis.txt

percolation_profile.x: $(OBJECTSPRO)
    g++ -std=c++17 -g -pg -fprofile-filter-files='src.*' $^ -o $@

src/%_pro.o: src/%.cpp src/percolation.h
    g++ -std=c++17 -g -pg -fprofile-filter-files='src.*' $< -c -Isrc -o $@

report: report.tex
	pdflatex $<
	okular report.pdf