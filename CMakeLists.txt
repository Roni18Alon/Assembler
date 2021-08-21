cmake_minimum_required(VERSION 3.19)
project(RoniProject C)

set(CMAKE_C_STANDARD 90)

add_executable(RoniProject main.c main.h default.h firstPass.c firstPass.h inputAnalyzed.c inputAnalyzed.h EntryAndExtern.c WordList.c WordList.h labelList.c labelList.h instructionAnalyzed.c instructionAnalyzed.h directiveAnalysis.c directiveAnalysis.h secondPass.c secondPass.h printErrors.c printErrors.h EntryAndExtern.h createOutput.c createOutput.h memleaks.c memleaks.h)