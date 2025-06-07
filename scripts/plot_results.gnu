#!/usr/bin/env gnuplot

# Set output format and file
set terminal pngcairo enhanced color font 'Arial,12' size 800,600
set output 'data/results/percolation_plot.png'

# Set plot properties
set title "Percolation Probability vs Site Probability"
set xlabel "Site Probability (p)"
set ylabel "Percolation Probability"
set grid
set key top left

# Set ranges
set xrange [0:1]
set yrange [0:1]

# Plot the data
plot 'data/results/probability_study.txt' using 1:2 with linespoints \
     linewidth 2 pointtype 7 pointsize 0.5 \
     title "Percolation Probability" linecolor rgb "blue"

# Also create a matrix visualization script
set output 'data/results/matrix_plot.png'
set title "Percolation Matrix Visualization"
set xlabel "Column"
set ylabel "Row"
set size ratio -1
set origin 0,0
set grid
set palette defined (0 "white", 1 "lightblue", 2 "blue", 3 "red", 4 "green", 5 "yellow", 6 "orange", 7 "purple")

# Check if matrix data exists and plot
if (system("test -f data/results/matrix_data.txt") == 0) {
    plot "data/results/matrix_data.txt" using 2:1:3 with image title "Cluster IDs"
}