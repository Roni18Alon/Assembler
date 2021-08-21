/* Name: EntryAndExtern.c
 * Author: Roni Alon & Noa Even
 * Description: Include the function to add and create node of Entry or Extern Labels , and their linked lists
 *
*/


#ifndef RONIPROJECT_ENTRYANDEXTERN_H
#define RONIPROJECT_ENTRYANDEXTERN_H

#include "default.h"
#include "WordList.h"
#include "labelList.h"



void addExternalToList(externalListPtr *, externalListPtr );
void createExternalNode(char *, globalVariables *);

void addEntryToList(entryListPtr *, entryListPtr );
void createEntryNode(char *, long ,globalVariables *);

#endif
