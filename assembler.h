/* Name: assembler.h
 * Author: Roni Alon & Noa Even
 * Description: Gets the file and run the assembler process.
*/


#ifndef ASSEMBLERPROJ_H
#define ASSEMBLERPROJ_H

#include "default.h"
#include "firstPass.h"
#include "secondPass.h"
#include "createOutput.h"

void resetVars(globalVariables *); /*reset global vars*/
void freeVars(globalVariables *);  /*free global vars*/
void freeLists(globalVariables *vars);  /*free lists - word,label,extern,entry */

#endif
