set terminal postscript eps enhanced color
set key title "Gamid"  
set yrange [-20:20]  
set xrange [0:2]  
set grid
set border 0
# set tics scale 0.5
set xtics nomirror
set ytics nomirror
set xzeroaxis lt 1 lw 4 lc 3
set yzeroaxis lt 1 lw 4 lc 3
set output 'prim9.eps'
plot "data2.txt" with lines
