reset;

set key right top Left box 1 

#set xrange [1:100]

#set logscale y

set xlabel '<d>' font "Times-Roman,34"
set ylabel '{/Symbol h}' font "Times-Roman,34"


p '../mm.dat' not w l lt 1 
rep '../mm1.dat' t 'd_2=0' w p pt 25 pointsize 2 
rep '../mm2.dat' t 'd_2=0.5' w p pt 4 pointsize 2 
rep '../mm3.dat' t 'd_2=0.75' w p pt 1 pointsize 2 



set term  pos enhanced mono "Times-Roman" 20
set out 'tests_jumps.eps'
rep



