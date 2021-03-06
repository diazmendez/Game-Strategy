reset;

set key right top Left box 1 

set xrange [:500]

set xlabel '{/Symbol t}' font "Times-Roman,34"
set ylabel 'P({/Symbol t})' font "Times-Roman,34"

#19,35,49

p '../testp0p0/hist.dat'       t 'd_1=0.0     vs   d_2=0.0' w p pt 25 pointsize 2
rep '../testp.5p0/hist.dat'    t 'd_1=0.5     vs   d_2=0.0' w p pt 41 pointsize 2
rep '../testp.75p0/hist.dat'   t 'd_1=0.75   vs   d_2=0.0' w p pt 56 pointsize 2
rep '../testp1p0/hist.dat'     t 'd_1=1.0     vs   d_2=0.0' w p pt 60 pointsize 2

rep '../testp.5p.5/hist.dat'   t 'd_1=0.5     vs   d_2=0.5' w p pt 4 pointsize 2
rep '../testp.75p.5/hist.dat'  t 'd_1=0.75   vs   d_2=0.5' w p pt 6 pointsize 2
rep '../testp1p.5/hist.dat'    t 'd_1=1.0     vs   d_2=0.5' w p pt 8 pointsize 2

rep '../testp.75p.75/hist.dat'  t 'd_1=0.75   vs   d_2=0.75' w p pt 1 pointsize 2
rep '../testp1p.75/hist.dat'    t 'd_1=1.0     vs   d_2=0.75' w p pt 2 pointsize 2


set term  pos enhanced mono "Times-Roman" 20
set out 'tests_tau.eps'
rep



set out "borrar"
set term x11
#*****************

reset

set key left top Left box 1 

set xlabel 't' font "Times-Roman,34"
set ylabel '<v(t)>' font "Times-Roman,34"

set yrange [-.1:3]
set xrange [:47]


p '../testp0p0/avev.dat'     u 0:(2*$1)   t 'd_1=0.0     vs   d_2=0.0' w p pt 25 pointsize 2
rep '../testp.5p0/avev.dat'  u 0:(2*$1)  t 'd_1=0.5     vs   d_2=0.0' w p pt 41 pointsize 2
rep '../testp.75p0/avev.dat' u 0:(2*$1)  t 'd_1=0.75   vs   d_2=0.0' w p pt 56 pointsize 2
rep '../testp1p0/avev.dat'   u 0:(2*$1)  t 'd_1=1.0     vs   d_2=0.0' w p pt 60 pointsize 2

rep '../testp.5p.5/avev.dat'  u 0:(2*$1) t 'd_1=0.5     vs   d_2=0.5' w p pt 4 pointsize 2
rep '../testp.75p.5/avev.dat' u 0:(2*$1) t 'd_1=0.75   vs   d_2=0.5' w p pt 6 pointsize 2
rep '../testp1p.5/avev.dat'   u 0:(2*$1) t 'd_1=1.0     vs   d_2=0.5' w p pt 8 pointsize 2

rep '../testp.75p.75/avev.dat' u 0:(2*$1) t 'd_1=0.75   vs   d_2=0.75' w p pt 1 pointsize 2
rep '../testp1p.75/avev.dat'   u 0:(2*$1) t 'd_1=1.0     vs   d_2=0.75' w p pt 2 pointsize 2


set term  pos enhanced mono "Times-Roman" 20
set out 'tests_vent.eps'
rep


set out "borrar"
set term x11
#*****************

reset

set key left top Left box 1 

set xlabel 't {/Symbol D}d' font "Times-Roman,34"
set ylabel '<v(t)>' font "Times-Roman,34"

set yrange [:2.1]

p '../testp.5p0/avev.dat' u ($0*.5):(2*$1)          t 'd_1=0.5     vs   d_2=0.0' w p pt 41 pointsize 2
rep '../testp.75p0/avev.dat' u ($0*.75):(2*$1)      t 'd_1=0.75   vs   d_2=0.0' w p pt 56 pointsize 2
rep '../testp1p0/avev.dat' u ($0*1):(2*$1)          t 'd_1=1.0     vs   d_2=0.0' w p pt 60 pointsize 2

rep '../testp.75p.5/avev.dat' u ($0*.25):(2*$1)     t 'd_1=0.75   vs   d_2=0.5' w p pt 6 pointsize 2
rep '../testp1p.5/avev.dat' u ($0*.5):(2*$1)        t 'd_1=1.0     vs   d_2=0.5' w p pt 8 pointsize 2

rep '../testp1p.75/avev.dat' u ($0*.25):(2*$1)      t 'd_1=1.0     vs   d_2=0.75' w p pt 2 pointsize 2


set term  pos enhanced mono "Times-Roman" 20
set out 'tests_coll_vent.eps'
rep





set out "borrar"
set term x11
#*****************

reset

set key left top Left box 1 

set xlabel 't' font "Times-Roman,34"
set ylabel 'advantages' font "Times-Roman,34"

set xrange [:127]

p '../testp.75p0/example_v_seq.dat' u 0:(2*$1)   t 'v(t)' w l lt 2 lw 4
rep '../testp.75p0/example_v_seq.dat' u 0:(2*$2) t 's(t)' w l lt 1


set term  pos enhanced mono "Times-Roman" 34
set out 'tests_examp_p.75p0.eps'
rep


	
