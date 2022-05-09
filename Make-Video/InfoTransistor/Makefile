MAIN = labReport

labReport.pdf: intro.tex methods.tex results.tex Shockley.png Code/Shockley.cpp
	pdflatex labReport.tex
	biber labReport
	makeindex labReport
	pdflatex labReport.tex

Shockley.png: script.gp Shockley.txt
	gnuplot script.gp

Shockley.txt: Shockley.x
	./Shockley.x > Shockley.txt

Shockley.x: Code/Shockley.cpp Code/top.h Code/functions.cpp 
	g++ Code/Shockley.cpp Code/top.h Code/functions.cpp -o Shockley.x

clean:
	rm -f Shockley.x labReport.aux labReport.idx labReport.log labReport.bcf labReport.run.xml *~ *png *txt *blg *bbl  a.out
