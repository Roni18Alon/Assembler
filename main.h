#ifndef RONIPROJ_MAIN_H
#define RONIPROJ_MAIN_H

#include "default.h"
#include "firstPass.h"
#include "secondPass.h"

void resetVars(globalVariables *);
void freeVars(globalVariables *);

void freeLists(globalVariables *vars);
void freeExternList(externalListPtr *head);
void freeEntryList(entryListPtr *head);
void freeWordList(WordNodePtr *head);
void freeLabelList (labelListPtr *head);

#endif
