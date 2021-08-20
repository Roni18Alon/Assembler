//
// Created by ronia on 24/07/2021.
//

#ifndef RONIPROJ_FIRSTPASS_H
#define RONIPROJ_FIRSTPASS_H

#include "default.h"
#include "lableList.h"
#include "WordList.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "directiveAnalysis.h"
#include "printErrors.h"

void firstPass(globalVariables *);
void firstPassAnalysis(globalVariables *,char *,char *, char * , char *,char *);
Bool getLine(char *line,char *lineCpy,globalVariables *vars);
#endif //RONIPROJ_FIRSTPASS_H

