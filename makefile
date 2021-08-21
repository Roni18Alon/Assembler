
main:main.o firstPass.o secondPass.o inputAnalyzed.o instructionAnalyzed.o directiveAnalyzed.o EntryAndExtern.o lableList.o WordList.o
	gcc -g main.o firsPass.o secondPass.o inputAnalyzed.o instructionAnalyzed.o directiveAnalyzed.o EntryAndExtern.o lableList.o WordList.o -o main
main.o: main.c main.h default.h firstPass.h secondPass.h createOutput.h
	gcc -c -g main.c -ansi -Wall -pedantic -o main.o

firstPass.o: firstPass.c firstPass.h default.h labelList.h WordList.h inputAnalyzed.h instructionAnalyzed.h directiveAnalysis.h printErrors.h
	gcc -c -g main.c -ansi -Wall -pedantic -o firstPass.o

secondPass.o: secondPass.c secondPass.h default.h labelList.h WordList.h inputAnalyzed.h instructionAnalyzed.h directiveAnalysis.h printErrors.h
	 gcc -c -g main.c -ansi -Wall -pedantic -o secondPass.o

inputAnalyzed.o: inputAnalyzed.c inputAnalyzed.h default.h directiveAnalysis.h 
	gcc -c -g main.c -ansi -Wall -pedantic -o inputAnalyzed.o


instructionAnalyzed.o:instructionAnalyzed.c instructionAnalyzed.h firstPass.h default.h EntryAndExtern.h
	gcc -c -g main.c -ansi -Wall -pedantic -o instructionAnalyzed.o


directiveAnalyzed.o:directiveAnalysis.c directiveAnalysis.h default.h inputAnalyzed.h instructionAnalyzed.h
	gcc -c -g main.c -ansi -Wall -pedantic -o directiveAnalyzed.o


EntryAndExtern.o:EntryAndExtern.c EntryAndExtern.h default.h WordList.h labelList.h
	gcc -c -g main.c -ansi -Wall -pedantic -o EntryAndExtern.o


labelList.o:labelList.c labelList.h default.h default.h inputAnalyzed.h
	gcc -c -g main.c -ansi -Wall -pedantic -o lableList.o

WordList.o:WordList.c WordList.h default.h inputAnalyzed.h
	gcc -c -g main.c -ansi -Wall -pedantic -o WordList.o
