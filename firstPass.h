/* Name: firstPass.h
 * Author: Roni Alon & Noa Even
 * Description: in this function we will pass on the file for the first time and Start to analyzed it
 *
*/

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
Bool getLine(char *,char *,globalVariables *);
#endif

