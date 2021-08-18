//
// Created by ronia on 06/08/2021.
//

#ifndef RONIPROJECT_DIRECTIVEANALYZED_H
#define RONIPROJECT_DIRECTIVEANALYZED_H

#include "default.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"

void isDirectiveFirstPass(char* ,char* ,char* ,globalVariables *,Bool ,labelListPtr ,WordNodePtr ) ;
Bool isDirectiveSecondPass(char *,char*  ,globalVariables *, Bool , labelListPtr );
void byteDirectiveFirstPass(char *, char *,char *,Bool ,globalVariables *,int , DirectiveWordType, labelListPtr);
void ascizDirectiveFirstPass(char *,char *,Bool ,globalVariables *,DirectiveWordType ,labelListPtr);
Bool isDirectiveCommand(char []);
int isValidDirectiveName(char *);
DirectiveWordType getDirectiveType(int);
Bool dataAnalysis(char *,char *,char *,globalVariables *,long [],int );
Bool ascizAnalysis(char *str,globalVariables *vars);
Bool externDirectiveFirstPass(char *, globalVariables *,labelListPtr );
Bool labelBeforeDirectiveCommand(char *, globalVariables *, labelListPtr );
void labelAndEntryOrExtern(Bool ,int ,globalVariables *);
void entryDirectiveSecondPass(globalVariables *,char *);



#endif //RONIPROJECT_DIRECTIVEANALYZED_H
