//
// Created by ronia on 12/08/2021.
//

#ifndef RONIPROJECT_PRINTERRORS_H
#define RONIPROJECT_PRINTERRORS_H

#include "default.h"
#include "lableList.h"
#include "WordList.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "directiveAnalysis.h"
#include "firstPass.h"

void printErrors(globalVariables *vars);
void foundError(globalVariables *vars,errorType type,char *str);

#endif //RONIPROJECT_PRINTERRORS_H
