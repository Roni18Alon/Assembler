/* Name: WordList.h
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze and handle  the word list like add, search for a node in the word list
 *
*/

#ifndef RONIPROJECT_WORDLIST_H
#define RONIPROJECT_WORDLIST_H

#include "default.h"
#include "inputAnalyzed.h"


void addWordToList(WordNodePtr *, WordNodePtr );
void addDirectiveByteToWordList(long [], WordNodePtr *, int , DirectiveWordType ,globalVariables *);
void addDirectiveAsciz(char *, WordNodePtr *, DirectiveWordType , globalVariables *);
void addDirectiveICF(WordNodePtr *,globalVariables *);
void addLabelAddress(WordNodePtr *,globalVariables *,long ,InstructionWordType ,Bool );


#endif
