reset;

set key right top Left box 1 

set xrange [1:100]

#set logscale y

set xlabel 'L' font "Times-Roman,34"
set ylabel 'P(L)' font "Times-Roman,34"


p '../testp0p0/hist.seq_emp_sizes.dat'       t 'd_1=0.0     vs   d_2=0.0' w lp lt 1 pt 25 pointsize 2
rep '../testp.5p.5/hist.seq_emp_sizes.dat'   t 'd_1=0.5     vs   d_2=0.5' w lp lt 1 pt 4 pointsize 2
rep '../testp.75p.75/hist.seq_emp_sizes.dat'  t 'd_1=0.75   vs   d_2=0.75' w lp lt 1 pt 1 pointsize 2


set term  pos enhanced mono "Times-Roman" 20
set out 'tests_his_seq_emp.eps'
rep




set out "borrar"
set term x11
#*****************

reset

#set key right top Left box 1 

set xrange [1:300]

set logscale y
set yrange [.00001:.3]
set ytics ("1" 1, "10^{-1}" 0.1,"10^{-2}" 0.01,"10^{-3}" 0.001, "10^{-4}" .0001,"10^{-5}" 0.00001)

set xlabel 'L' font "Times-Roman,34"
set ylabel 'P(L)' font "Times-Roman,34"

#p '../testp0p0/hist.seq_emp_sizes.dat'       t 'd_1=0.0     vs   d_2=0.0' w lp lt 1 pt 25 pointsize 2
#rep '../testp.5p.5/hist.seq_emp_sizes.dat'   t 'd_1=0.5     vs   d_2=0.5' w lp lt 1 pt 4 pointsize 2
#rep '../testp.75p.75/hist.seq_emp_sizes.dat'  t 'd_1=0.75   vs   d_2=0.75' w lp lt 1 pt 1 pointsize 2
p '../testp0p0/hist.seq_emp_sizes.dat'       not w lp lt 1 pt 25 pointsize 2
rep '../testp.5p.5/hist.seq_emp_sizes.dat'   not w lp lt 1 pt 4 pointsize 2
rep '../testp.75p.75/hist.seq_emp_sizes.dat'  not w lp lt 1 pt 1 pointsize 2

set term  pos enhanced mono "Times-Roman" 20
set out 'tests_his_seq_emp_log.eps'
rep






set out "borrar"
set term x11
#*****************

reset

set key right top Left box 1 

set xrange [1:140]

set logscale y
set yrange [.00001:5]
set ytics ("1" 1, "10^{-1}" 0.1,"10^{-2}" 0.01,"10^{-3}" 0.001, "10^{-4}" .0001,"10^{-5}" 0.00001)

set xlabel '(1-<d>)^{/Symbol a} L' font "Times-Roman,34"
set ylabel 'P(L)' font "Times-Roman,34"

f(x)=(1-x)**b
b=.65;

p '../testp0p0/hist.seq_emp_sizes.dat' u (f(0)*$1):2 t 'd_1=0.0     vs   d_2=0.0' w p pt 25 pointsize 2
rep '../testp.5p.5/hist.seq_emp_sizes.dat' u (f(0.5)*$1):2 t 'd_1=0.5     vs   d_2=0.5' w p pt 4 pointsize 2
rep '../testp.75p.75/hist.seq_emp_sizes.dat' u (f(0.75)*$1):2 t 'd_1=0.75   vs   d_2=0.75' w p pt 1 pointsize 2

rep '../testp.5p0/hist.seq_emp_sizes.dat'   u (f(0.25)*$1):2    t 'd_1=0.5     vs   d_2=0.0' w p pt 41 pointsize 2
rep '../testp.75p0/hist.seq_emp_sizes.dat'  u (f(0.375)*$1):2   t 'd_1=0.75   vs   d_2=0.0' w p pt 56 pointsize 2
rep '../testp1p0/hist.seq_emp_sizes.dat'    u (f(0.5)*$1):2     t 'd_1=1.0     vs   d_2=0.0' w p pt 60 pointsize 2
rep '../testp.75p.5/hist.seq_emp_sizes.dat' u (f(0.625)*$1):2  t 'd_1=0.75   vs   d_2=0.5' w p pt 6 pointsize 2
rep '../testp1p.5/hist.seq_emp_sizes.dat'   u (f(0.75)*$1):2    t 'd_1=1.0     vs   d_2=0.5' w p pt 8 pointsize 2
rep '../testp1p.75/hist.seq_emp_sizes.dat'  u (f(0.875)*$1):2    t 'd_1=1.0     vs   d_2=0.75' w p pt 2 pointsize 2



set term  pos enhanced mono "Times-Roman" 20
set out 'tests_his_seq_emp_collapse.eps'
rep
