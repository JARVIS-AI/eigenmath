To build and run:

	cd src
	make
	./eigenmath

Press control-C or type exit to exit.

To run a script:

	./eigenmath scriptfilename

To generate LaTeX output:

	./eigenmath --latex scriptfilename | tee foo.tex

To generate MathML output:

	./eigenmath --mathml scriptfilename | tee foo.html

To generate MathJax output:

	./eigenmath --mathjax scriptfilename | tee foo.html

MathML and MathJax results look best on Safari and Firefox.

The Eigenmath manual and sample scripts are available at https://eigenmath.github.io

A Javascript version of Eigenmath is available in the 'js' directory.

To build and run eigenmath.c

	cd tools
	make
	cd ..
	gcc eigenmath.c
	./a.out
