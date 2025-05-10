BUILD_DIR=build


view: latex-compile

latex-compile: compile1, compile2

compile1:
	pdflatex -output-directory="./$(BUILD_DIR)" ./analiza.tex

compile2:
	pdflatex -output-directory="./$(BUILD_DIR)" ./koncepcja.tex
