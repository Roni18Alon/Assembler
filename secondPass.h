//
// Created by ronia on 08/08/2021.
//

#ifndef RONIPROJECT_SECONDPASS_H
#define RONIPROJECT_SECONDPASS_H



#include "default.h"
#include "lableList.h"
#include "WordList.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "directiveAnalysis.h"
#include "printErrors.h"



void secondPass(globalVariables *vars);
void secondPassAnalysis(globalVariables *vars,char *lineCpy,char *before, char *after , char *label,char *lineCpyAfterLabel);
void varsResetForSecondPass(globalVariables *vars);

#endif //RONIPROJECT_SECONDPASS_H
