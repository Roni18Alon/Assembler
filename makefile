
assembler:assembler.o firstPass.o secondPass.o inputAnalyzed.o instructionAnalyzed.o directiveAnalysis.o EntryAndExtern.o labelList.o WordList.o printErrors.o createOutput.o
	gcc -g assembler.o firstPass.o secondPass.o inputAnalyzed.o instructionAnalyzed.o directiveAnalysis.o EntryAndExtern.o labelList.o WordList.o printErrors.o createOutput.o -o assembler
assembler.o: assembler.c assembler.h default.h firstPass.h secondPass.h createOutput.h
	gcc -c -g assembler.c -ansi -Wall -pedantic -o assembler.o

firstPass.o: firstPass.c firstPass.h default.h labelList.h WordList.h inputAnalyzed.h instructionAnalyzed.h directiveAnalysis.h printErrors.h
	gcc -c -g firstPass.c -ansi -Wall -pedantic -o firstPass.o

secondPass.o: secondPass.c secondPass.h default.h labelList.h WordList.h inputAnalyzed.h instructionAnalyzed.h directiveAnalysis.h printErrors.h
	 gcc -c -g secondPass.c -ansi -Wall -pedantic -o secondPass.o

inputAnalyzed.o: inputAnalyzed.c inputAnalyzed.h default.h directiveAnalysis.h 
	gcc -c -g inputAnalyzed.c -ansi -Wall -pedantic -o inputAnalyzed.o


instructionAnalyzed.o:instructionAnalyzed.c instructionAnalyzed.h firstPass.h default.h EntryAndExtern.h
	gcc -c -g instructionAnalyzed.c -ansi -Wall -pedantic -o instructionAnalyzed.o


directiveAnalysis.o:directiveAnalysis.c directiveAnalysis.h default.h inputAnalyzed.h instructionAnalyzed.h
	gcc -c -g directiveAnalysis.c -ansi -Wall -pedantic -o directiveAnalysis.o


EntryAndExtern.o:EntryAndExtern.c EntryAndExtern.h default.h WordList.h labelList.h
	gcc -c -g EntryAndExtern.c -ansi -Wall -pedantic -o EntryAndExtern.o


labelList.o:labelList.c labelList.h default.h default.h inputAnalyzed.h
	gcc -c -g labelList.c -ansi -Wall -pedantic -o labelList.o

WordList.o:WordList.c WordList.h default.h inputAnalyzed.h
	gcc -c -g WordList.c -ansi -Wall -pedantic -o WordList.o
printErrors.o:printErrors.c printErrors.h default.h labelList.h WordList.h inputAnalyzed.h instructionAnalyzed.h directiveAnalysis.h
	gcc -c -g printErrors.c -ansi -Wall -pedantic -o printErrors.o

createOutput.o:createOutput.c createOutput.h default.h
	gcc -c -g createOutput.c -ansi -Wall -pedantic -o createOutput.o