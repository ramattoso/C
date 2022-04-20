#Gráfico convergência Método Euler Explicito

set terminal png size 800,600 
set xlabel "log(h)"
set ylabel "log(erro)"
set grid
set output 'conv_exp.png'
set xrange [0:1.2]
set title 'Convergência para Euler Explícito'
set key right bottom
f(x) = a*x + b
fit f(x) 'explicitoer' using 1:2 via a,b
plot f(x) t "Ajuste Linear", 'explicitoer' using 1:2  t "Erro(h)" \
with points lw 2

#Gráfico convergência Método de Euler Implícito

set terminal png size 800,600 
set xlabel "log(h)"
set ylabel "log(erro)"
set grid
set output 'conv_imp.png'
set xrange [0:1.2]
set title 'Convergência para Euler Implícito'
set key right bottom
f(x) = a*x + b
fit f(x) 'implicitoer' using 1:2 via a,b
plot f(x) t "Ajuste Linear", 'implicitoer' using 1:2  t "Erro(h)" \
with points lw 2

#Gráfico N(tk) com h=1 explicito

set terminal png size 800,600 
set xlabel "tk"
set ylabel "N"
set grid
set output 'comp_exp_h1.png'
set xrange [0:60]
set title 'N(tk) Euler Explícito para h=1'
set key right bottom 
plot 'explicito_1' using 1:2 t "Aproximação com h=1", 4000000000.0*exp(0.01*x) t "N(t) = N0*exp(r*tk)"

#Gráfico N(tk) com h=15 explicito

set terminal png size 800,600 
set xlabel "tk"
set ylabel "N"
set grid
set output 'comp_exp_h12.png'
set xrange [0:60]
set title 'N(tk) Euler Explícito para h=12'
set key right bottom 
plot 'explicito_12' using 1:2 t "Aproximação com h=12", 4000000000.0*exp(0.01*x) t "N(t) = N0*exp(r*tk)"

#Gráfico N(tk) com h=1 implicito

set terminal png size 800,600 
set xlabel "tk"
set ylabel "N"
set grid
set output 'comp_imp_h1.png'
set xrange [0:60]
set title 'N(tk) Euler Implícito para h=1'
set key right bottom 
plot 'implicito_1' using 1:2 t "Aproximação com h=1", 4000000000.0*exp(0.01*x) t "N(t) = N0*exp(r*tk)"

#Gráfico N(tk) com h=15 implicito

set terminal png size 800,600 
set xlabel "tk"
set ylabel "N"
set grid
set output 'comp_imp_h12.png'
set xrange [0:60]
set title 'N(tk) Euler Implícito para h=12'
set key right bottom 
plot 'implicito_12' using 1:2 t "Aproximação com h=12", 4000000000.0*exp(0.01*x) t "N(t) = N0*exp(r*tk)"
quit
