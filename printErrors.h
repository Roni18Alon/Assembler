/* Name: printErrors.h
 * Author: Roni Alon & Noa Even
 * Description: Print the errors we found in the FIRST PASS OR SECOND PASS
 *
*/
#ifndef RONIPROJECT_PRINTERRORS_H
#define RONIPROJECT_PRINTERRORS_H

#include "default.h"
#include "lableList.h"
#include "WordList.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "directiveAnalysis.h"
#include "firstPass.h"

void printErrors(globalVariables *);
void foundError(globalVariables *,errorType ,char *);

#endif
