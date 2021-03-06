
/* Name: labelList.h
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze and handle  the label list like add, search for a label in the list
 *
*/


#ifndef ASSEMBLERPROJ_LABELLIST_H
#define ASSEMBLERPROJ_LABELLIST_H

#include "default.h"
#include "inputAnalyzed.h"



void updateLabel(labelListPtr ,int ,Location ,LabelType );
void addLabelToList(labelListPtr* , labelListPtr );
int labelNameCompare(labelListPtr *, char *,globalVariables *);
Bool isLabelExternal(labelListPtr *,char * ,globalVariables *);
Bool isLabelEntry(labelListPtr *, char *after,globalVariables *);
void  updateLabelTableICF(labelListPtr *,globalVariables *);
long findLabel(labelListPtr *, char *,globalVariables *,InstructionWordType );
Bool existsLabelExternalIBranch(labelListPtr *, char *,globalVariables *);
Bool existsLabelExternalJ(labelListPtr *, char *,globalVariables *);
long EntryValueAfterSecondPass(labelListPtr *, char *);
void createLabelNode(labelListPtr labelToAdd, globalVariables *vars);
void freeLabelList (labelListPtr *);

#endif