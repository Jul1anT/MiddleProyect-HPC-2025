# Gráfica de tiempo de ejecución para p y dos niveles de optimización
set term png
set output "computing-time.png"
set title "Computing time vs L"
set grid
set logscale x
set logscale y
set xlabel "L"
set ylabel "t(ms)"
plot '/data/study_p06-O2.txt' u 1:4 w lp title "O2", \ 
     'study_p06-O3.txt' u 1:4 w lp title "O3"
unset output

# Gráfica de tiempo de ejecución
set out "Execution_time.png"
set title "Tiempo de ejecución vs p"
set ylabel "Time (ms)"
set xrange [0:1]
plot 'study_L32.txt' u 1:5 w lp title "L = 32", \
     'study_L64.txt' u 1:5 w lp title "L = 64", \
     'study_L128.txt' u 1:5 w lp title "L = 128", \
     'study_L256.txt' u 1:5 w lp title "L = 256", \
     'study_L512.txt' u 1:5 w lp title "L = 512"