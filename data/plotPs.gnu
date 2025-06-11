set term png
set out "Probability_of_percolation.png"
set key left top
set grid
set xlabel "p"
set ylabel "P"
set title "Probability of percolation"
plot 'study_L32.txt' u 1:2 w lp title "L = 32", 'study_L64.txt' u 1:2 w lp title "L = 64", 'study_L128.txt' u 1:2 w lp title "L = 128", 'study_L256.txt' u 1:2 w lp title "L = 256", 'study_L512.txt' u 1:2 w lp title "L = 512"
unset output
reset

set term png
set out "Cluster_size.png"
set key left top
set grid 
set xlabel "p"
set ylabel "s"
set title "Average cluster size"
plot 'study_L32.txt' u 1:3:4 w yerrorlines title "L = 32", 'study_L64.txt' u 1:3:4 w yerrorlines title "L = 64", 'study_L128.txt' u 1:3:4 w yerrorlines title "L = 128", 'study_L256.txt' u 1:3:4 w yerrorlines title "L = 256", 'study_L512.txt' u 1:3:4 w yerrorlines title "L = 512"
unset output
reset

