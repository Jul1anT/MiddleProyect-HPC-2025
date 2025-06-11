# Configuración para "Probabilidad de percolación" PNG
set term png
set out "data/figures/probability_of_percolation.png"
set key left top
set grid
set xlabel "p"
set ylabel "P(p)"
set title "Probabilidad de percolación"
plot 'data/results/study_L32.txt' u 1:2 w lp title "L = 32",\
     'data/results/study_L64.txt' u 1:2 w lp title "L = 64",\
     'data/results/study_L128.txt' u 1:2 w lp title "L = 128",\
     'data/results/study_L256.txt' u 1:2 w lp title "L = 256",\
     'data/results/study_L512.txt' u 1:2 w lp title "L = 512"
unset output
reset

# Configuración para "Tamaño promedio del Cluster" PNG
set term png
set out "data/figures/cluster_size.png"
set key left top
set grid 
set xlabel "p"
set ylabel "s"
set title "Tamaño promedio del Cluster"
plot 'data/results/study_L32.txt' u 1:3:4 w yerrorlines title "L = 32",\
     'data/results/study_L64.txt' u 1:3:4 w yerrorlines title "L = 64",\
     'data/results/study_L128.txt' u 1:3:4 w yerrorlines title "L = 128",\
     'data/results/study_L256.txt' u 1:3:4 w yerrorlines title "L = 256",\
     'data/results/study_L512.txt' u 1:3:4 w yerrorlines title "L = 512"
unset output
reset