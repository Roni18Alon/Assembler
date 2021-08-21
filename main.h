#ifndef RONIPROJ_MAIN_H
#define RONIPROJ_MAIN_H

#include "default.h"
#include "firstPass.h"
#include "secondPass.h"
#include "createOutput.h"

void resetVars(globalVariables *);
void freeVars(globalVariables *);
void freeLists(globalVariables *vars);

#endif
