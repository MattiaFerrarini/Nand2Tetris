VMtranslator: VMtranslator.o parser.o code.o output.o
	gcc -o VMtranslator VMtranslator.o parser.o code.o output.o

VMtranslator.o: VMtranslator.c parser.h code.h output.h
	gcc -c VMtranslator.c

parser.o: parser.c parser.h enumTypes.h
	gcc -c parser.c

code.o: code.c code.h enumTypes.h
	gcc -c code.c

output.o: output.c output.h
	gcc -c output.c

clean:
	rm *.o VMtranslator