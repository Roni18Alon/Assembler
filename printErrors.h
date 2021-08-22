/* Name: printErrors.h
 * Author: Roni Alon & Noa Even
 * Description: Print the errors we found in the FIRST PASS OR SECOND PASS
 *
*/

#ifndef ASSEMBLERPROJ_PRINTERRORS_H
#define ASSEMBLERPROJ_PRINTERRORS_H

#include "default.h"
#include "labelList.h"
#include "WordList.h"
#include "inputAnalyzed.h"
#include "instructionAnalyzed.h"
#include "directiveAnalysis.h"


void printErrors(globalVariables *);
void foundError(globalVariables *,errorType ,char *);

#endif
