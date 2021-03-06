/* Name: directiveAnalysis.h
 * Author: Roni Alon & Noa Even
 * Description: Include functions for Directive command analysis
 *
*/

#ifndef ASSEMBLERPROJ_DIRECTIVEANALYSIS_H
#define ASSEMBLERPROJ_DIRECTIVEANALYSIS_H

#include "default.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "firstPass.h"
#include "secondPass.h"

void isDirectiveFirstPass(char* ,char* ,char* ,globalVariables *,Bool ,labelListPtr ) ;
Bool isDirectiveSecondPass(char *);
void byteDirectiveFirstPass(char *, char *,char *,Bool ,globalVariables *,int , DirectiveWordType, labelListPtr);
void ascizDirectiveFirstPass(char *,char *,Bool ,globalVariables *,DirectiveWordType ,labelListPtr);
Bool isDirectiveCommand(char *);
void ascizStr(char *str);
int isValidDirectiveName(char *);
DirectiveWordType getDirectiveType(int);
int dataAnalysis(char *,char *,globalVariables *,long [],int);
Bool ascizAnalysis(char *str,globalVariables *vars);
Bool externDirectiveFirstPass(char *, globalVariables *,labelListPtr );
Bool labelBeforeDirectiveCommand(char *, globalVariables *, labelListPtr );
void labelAndEntryOrExtern(Bool ,int ,globalVariables *);
void entryDirectiveSecondPass(globalVariables *,char *);



#endif
