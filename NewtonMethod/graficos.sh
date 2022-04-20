#Gráfico Comparação Valor inicial

set terminal png size 700,500 
set xlabel "t(dias)"
set ylabel "N(i)"
set grid
set output 'newton.png'
set xrange [0:80]
set title 'Convergência para diferentes valores inciais'
set key box right top Left w 1 h 1
plot 'newtonarq_ok' using 1:2 w p pt 5 ps 0.5 t 'A < N < K', 'newtonarq_menor' using 1:2 w p pt 7 ps 1 t "N < A", 'newtonarq_maior' using 1:2 w p pt 9 ps 0.5 t "N > K"   \


