assembler: assembler.o parser.o code.o symbolTable.o output.o
	gcc -o assembler assembler.o parser.o code.o symbolTable.o output.o

assembler.o: assembler.c parser.h code.h symbolTable.h output.h
	gcc -c assembler.c

parser.o: parser.c parser.h
	gcc -c parser.c

code.o: code.c code.h
	gcc -c code.c

symbolTable.o: symbolTable.c symbolTable.h
	gcc -c symbolTable.c

output.o: output.c output.h
	gcc -c output.c

clean:
	rm *.o assembler