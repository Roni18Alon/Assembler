//
// Created by ronia on 30/07/2021.
//

#include "WordList.h"
#include "default.h"



/*this functions adds a word node to word list*/
void addWordToList(WordNodePtr *head, WordNodePtr nodeToAdd) {
    WordNodePtr temp = *head;
    if (temp == NULL) {
        *head = nodeToAdd;
        return;
    }
    while (temp->next) { /*find the right place to locate the new node*/
        temp = temp->next;
    }
    temp->next = nodeToAdd;
}


void addDirectiveByteToWordList(long validInput[LINE_LENGTH], WordNodePtr *head, int directive, DirectiveWordType givenWordType,globalVariables *vars)
{
    int i;
    if (givenWordType == D_BYTE) {
        for (i = 0; i < LINE_LENGTH && validInput[i]!=LONG_MAX ; i++) {
            WordNodePtr newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
            newNode->word.wordType = Directive;
            newNode->word.directive.wordType = givenWordType;
            newNode->word.directive.address = vars->DC++;
            newNode->word.directive.db = (long) validInput[i];
            addWordToList(head, newNode);
        }

    } else {
        if (givenWordType == D_HALF) {
            {
                for (i = 0; i < LINE_LENGTH && validInput[i]!=LONG_MAX; i++) {
                    WordNodePtr newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                    newNode->word.wordType = Directive;
                    newNode->word.directive.wordType = givenWordType;
                    newNode->word.directive.address = vars->DC+=2;
                    newNode->word.directive.dh = (long) validInput[i];
                    addWordToList(head, newNode);
                }
            }
        } else {
            /* givenWordType==D_WORD WORD=4 Bytes */
            for (i = 0; i < LINE_LENGTH && validInput[i]!=LONG_MAX; i++) {
                WordNodePtr newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                newNode->word.wordType = Directive;
                newNode->word.directive.wordType = givenWordType;
                newNode->word.directive.address = vars->DC+=4;
                newNode->word.directive.dw = (long) validInput[i];
                addWordToList(head, newNode);
            }
        }

    }
}

void addDirectiveAsciz(char *str, WordNodePtr *head, DirectiveWordType givenWordType, globalVariables *vars)
{
    ascizStr(str);
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        WordNodePtr newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
        newNode->word.wordType = Directive;
        newNode->word.directive.wordType = givenWordType;
        newNode->word.directive.address = vars->DC++;
        newNode->word.directive.asciz =  str[i];
        addWordToList(head, newNode);
    }

    /*add the \0 char to end the string*/
    WordNodePtr newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
    newNode->word.wordType = Directive;
    newNode->word.directive.wordType = givenWordType;
    newNode->word.directive.address = vars->DC++;
    newNode->word.directive.asciz =  '\0';
    addWordToList(head, newNode);


}
/*this function adds after the first pass to each directive node in the word list the final IC value to the address*/
void addDirectiveICF(WordNodePtr *head,globalVariables *vars)
{
    WordNodePtr temp = *head;

    while(temp) {
        if(temp->word.wordType == Directive) {
            temp->word.directive.address +=vars->ICF;
        }
        temp = temp->next;
    }

}

void addLabelAddress(WordNodePtr *head,globalVariables *vars,long labelAddress,InstructionWordType commandType, Bool isExtern)
{
    long finalIAddress;
    WordNodePtr temp = *head;
    while (temp != NULL)
    {
        if(temp->word.instruction.address == vars->IC) /*find the right node */
        {
            if(commandType==J_WORD)  /*if it's a J - just update the address from label list*/
            {
                if(isExtern==True)
                {
                    temp->word.instruction.jWord.address=0;
                }
                else {temp->word.instruction.jWord.address=labelAddress;}
            }
            else{ if(commandType==I_WORD) /*if it's an I-Branch update the immed */
                {
                    finalIAddress= labelAddress- (temp->word.instruction.address); /*the final address (Immediate value) will be the sub between address from label list and current address*/
                    temp->word.instruction.iWord.immed=finalIAddress;
                }
            }
            return;
        }
        temp = temp->next;
    }
}