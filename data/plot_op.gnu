set term png
set output "Computing time.png"
set title "Computing time vs L"
set grid
set logscale x
set logscale y
set xlabel "L"
set ylabel "t(ms)"
plot 'study_p06-O2.txt' u 1:4 w lp title "O2", 'study_p06-O3.txt' u 1:4 w lp title "O3"
unset output