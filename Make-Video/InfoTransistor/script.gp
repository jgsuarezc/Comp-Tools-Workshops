set terminal png
set xlabel 'Voltaje a través del diodo'
set ylabel 'Corriente a través del diodo (mA)'
set output "Shockley.png"
plot 'Shockley.txt' w lp