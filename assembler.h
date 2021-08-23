/* Name: assembler.h
 * Author: Roni Alon & Noa Even
 * Description: Gets the file and run the assembler process.
*/


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
