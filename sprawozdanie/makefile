BUILD_DIR=build


sprawko: latex-compile
	sioyek $(BUILD_DIR)/sprawozdanie.pdf

latex-compile:
	pdflatex -output-directory="./$(BUILD_DIR)" ./sprawozdanie.tex
