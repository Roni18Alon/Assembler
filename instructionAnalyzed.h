//
// Created by ronia on 05/08/2021.
//

#ifndef RONIPROJECT_INSTRUCTIONANALYZED_H
#define RONIPROJECT_INSTRUCTIONANALYZED_H

#include "inputAnalyzed.h"
#include "firstPass.h"
#include "default.h"
#include "EntryAndExtern.h"

InstructionWordType commandGroup (int instructionNum);


void isInstructionFirstPass(char *before, char *after,char *labelName, globalVariables *vars, Bool hasLabel, labelListPtr currentLabel, WordNodePtr currentWord, int instructionNum);
void isInstructionSecondPass(char *str,InstructionWordType commandType,int instructionNum,globalVariables *vars);
Bool labelBeforeInstructionCommand(char *labelName, globalVariables *vars, labelListPtr currentLabel);

void RCommandFirstPass(char *before,char *after,InstructionWordType commandType,int instructionNum,globalVariables *vars,WordNodePtr currentWord);
void ICommandFirstPass(char *before,char *after,InstructionWordType commandType,int instructionNum,globalVariables *vars,WordNodePtr currentWord);
void JCommandFirstPass(char *after,int instructionNum,globalVariables *vars,WordNodePtr currentWord);

Bool validROperandLine(char *str,char *before ,char *after, int instructionNum,int numOfOperands,globalVariables *vars, WordNodePtr currentWord);
Bool validIOperandLine(char *str,char *before ,char *after, int instructionNum,int type,globalVariables *vars, WordNodePtr currentWord);
Bool validJOperandLine(char *str, int instructionNum,globalVariables *vars, WordNodePtr currentWord);

Bool I_commandAnalyzed(char *str,char *before ,char *after, int instructionNum,int type,globalVariables *vars, WordNodePtr currentWord);
Bool R_commandAnalyzed(char *str,char *before ,char *after, int instructionNum,int numOfOperands,globalVariables *vars, WordNodePtr currentWord);
Bool J_commandAnalyzed(char *str, int instructionNum,globalVariables *vars, WordNodePtr currentWord);

Bool regJCommand(char *str,globalVariables *vars, WordNodePtr currentWord);
Bool labelJCommand(char *str,globalVariables *vars, WordNodePtr currentWord);

int opcodeInstruction(int instructionNum);

void secondPassJ(char *str,globalVariables *vars, InstructionWordType commandType);
void secondPassI(char *str,globalVariables *vars, InstructionWordType commandType);

#endif //RONIPROJECT_INSTRUCTIONANALYZED_H
