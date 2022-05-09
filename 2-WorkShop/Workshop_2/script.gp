set terminal pdf
set output 'normal_pdf.pdf'

set title 'Probability density function of Normal Distribution'
set xlabel 'x'
set ylabel 'Probability Density'

plot 'seed1.txt' title 'SEED = 1' w l lw 2, 'seed2.txt' title 'SEED = 2' w l lw 2,'seed3.txt' title 'SEED = 5' w l lw 2