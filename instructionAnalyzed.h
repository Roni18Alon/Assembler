/* Name: instructionAnalyzed.c
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze the Instruction commands
 *
*/

#ifndef RONIPROJECT_INSTRUCTIONANALYZED_H
#define RONIPROJECT_INSTRUCTIONANALYZED_H

#include "inputAnalyzed.h"
#include "firstPass.h"
#include "default.h"
#include "EntryAndExtern.h"

InstructionWordType commandGroup (int);
void isInstructionFirstPass(char *, char *,char *, globalVariables *, Bool ,labelListPtr ,WordNodePtr ,int );
void isInstructionSecondPass(char *,InstructionWordType ,int ,globalVariables *);
Bool labelBeforeInstructionCommand(char *, globalVariables *, labelListPtr );
void RCommandFirstPass(char *,char *,InstructionWordType ,int ,globalVariables *,WordNodePtr );
void ICommandFirstPass(char *,char *,InstructionWordType ,int ,globalVariables *,WordNodePtr );
void JCommandFirstPass(char *,int ,globalVariables *,WordNodePtr );
Bool validROperandLine(char *,char * ,char *,int ,globalVariables *, WordNodePtr );
Bool validIOperandLine(char *,char * ,char *,int ,globalVariables *, WordNodePtr );
Bool validJOperandLine(char *str, int ,globalVariables *, WordNodePtr );
Bool I_commandAnalyzed(char *,char * ,char *, int ,int ,globalVariables *, WordNodePtr );
Bool R_commandAnalyzed(char *,char * ,char *, int ,int ,globalVariables *, WordNodePtr );
Bool J_commandAnalyzed(char *, int ,globalVariables *, WordNodePtr );
Bool regJCommand(char *,globalVariables *, WordNodePtr );
Bool labelJCommand(char *,globalVariables *, WordNodePtr );
int opcodeInstruction(int );
void secondPassJ(char *,globalVariables *, InstructionWordType );
void secondPassI(char *,globalVariables *, InstructionWordType );

#endif
