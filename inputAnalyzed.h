/* Name: inputAnalyzed.h
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze the given input
 *
*/

#ifndef ASSEMBLERPROJ_INPUTANALYZED_H
#define ASSEMBLERPROJ_INPUTANALYZED_H

#include "default.h"
#include "directiveAnalysis.h"


void strip(char*);
int isEmptyOrCommentLine(char *);
int split(char *, char *, char *, char *);
int isLegalLabel(char*,globalVariables *);
Bool labelIsKnown(char *label);
long directiveNumber(char *);
Bool ValidNumberDirective(char *,globalVariables *);
WordType directiveOrInstruction(char *,char *,char *,globalVariables *);
long validNumByDirective(int,long,char *,globalVariables *);
int isValidString(char *,globalVariables*);
int Rfunct(int );
int instructionValidName(char *);
int numberOfOperands(InstructionWordType ,int );
int isValidRegisterNum(char *,globalVariables *);
int isValidRegister(char *,globalVariables *);
int isValidImmediate(char *,globalVariables *);
InstructionWordType commandGroup (int );
Bool foundLabel(char *,char *,char *);
int validJRegister(char *str,globalVariables *vars);
void resetStrings(char *,char *,char * , char *, char *,char *);


#endif