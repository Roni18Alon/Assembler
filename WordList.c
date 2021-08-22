/* Name: WordList.c
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze and handle  the word list like add, search for a node in the word list
 *
*/
#include "WordList.h"


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

void createWordNode(WordNodePtr nodeToAdd,globalVariables *vars)
{
    WordNodePtr wordCpy = (WordNodePtr) calloc(1, sizeof(WordNode));
    if(!wordCpy)
    {
        exit(0);
    }

    if(nodeToAdd->word.instruction.wordType== R_WORD)
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.instruction.wordType=R_WORD;
        wordCpy->word.instruction.address= nodeToAdd->word.instruction.address;
        wordCpy->word.instruction.rWord.opcode=nodeToAdd->word.instruction.rWord.opcode;
        wordCpy->word.instruction.rWord.rs= nodeToAdd->word.instruction.rWord.rs;
        wordCpy->word.instruction.rWord.rt= nodeToAdd->word.instruction.rWord.rt;
        wordCpy->word.instruction.rWord.rd= nodeToAdd->word.instruction.rWord.rd;
        wordCpy->word.instruction.rWord.funct= nodeToAdd->word.instruction.rWord.funct;
        wordCpy->word.instruction.rWord.unused= nodeToAdd->word.instruction.rWord.unused;
        addWordToList(&(vars->headWordList),wordCpy);
    }
    if(nodeToAdd->word.instruction.wordType== I_WORD )
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.instruction.wordType=I_WORD;
        wordCpy->word.instruction.address= nodeToAdd->word.instruction.address;
        wordCpy->word.instruction.iWord.opcode=nodeToAdd->word.instruction.iWord.opcode;
        wordCpy->word.instruction.iWord.rs=  nodeToAdd->word.instruction.iWord.rs;
        wordCpy->word.instruction.iWord.rt=  nodeToAdd->word.instruction.iWord.rt;
        wordCpy->word.instruction.iWord.immed=  nodeToAdd->word.instruction.iWord.immed;
        addWordToList(&(vars->headWordList),wordCpy);
    }
    if(nodeToAdd->word.instruction.wordType== J_WORD)
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.instruction.wordType=J_WORD;
        wordCpy->word.instruction.address= nodeToAdd->word.instruction.address;
        wordCpy->word.instruction.jWord.opcode=nodeToAdd->word.instruction.jWord.opcode;
        wordCpy->word.instruction.jWord.reg=  nodeToAdd->word.instruction.jWord.reg;
        wordCpy->word.instruction.jWord.address=  nodeToAdd->word.instruction.jWord.address;
        addWordToList(&(vars->headWordList),wordCpy);
    }


}


void addDirectiveByteToWordList(signed long validInput[LINE_LENGTH], WordNodePtr *head, DirectiveWordType givenWordType,globalVariables *vars)
{
    int i;
    WordNodePtr newNode;
    if (givenWordType == D_BYTE) {
        for (i = 0; i < LINE_LENGTH && validInput[i]!='\0' ; i++) {
            newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
            newNode->word.wordType = Directive;
            newNode->word.directive.wordType = givenWordType;
            newNode->word.directive.address = vars->DC;
            newNode->word.directive.db = validInput[i];
            addWordToList(head, newNode);
        }
        vars->DC+=(vars->DC+i);

    } else {
        if (givenWordType == D_HALF) {
            {
                for (i = 0; i < LINE_LENGTH && validInput[i]!='\0'; i++) {
                     newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                    if(!newNode)
                    {
                        exit(0);
                    }
                    newNode->word.wordType = Directive;
                    newNode->word.directive.wordType = givenWordType;
                    newNode->word.directive.address = vars->DC;
                    newNode->word.directive.dh =validInput[i];
                    addWordToList(head, newNode);
                }
                vars->DC+=(vars->DC+i*2);
            }
        } else {
            /* givenWordType==D_WORD WORD=4 Bytes */
            for (i = 0; i < LINE_LENGTH && validInput[i]!='\0'; i++) {
                 newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                if(!newNode)
                {
                    exit(0);
                }
                newNode->word.wordType = Directive;
                newNode->word.directive.wordType = givenWordType;
                newNode->word.directive.address = vars->DC;
                newNode->word.directive.dw = validInput[i];
                addWordToList(head, newNode);
            }
            vars->DC+=(vars->DC+i*4);
        }

    }
}

void addDirectiveAsciz(char *str, WordNodePtr *head, DirectiveWordType givenWordType, globalVariables *vars)
{
    ascizStr(str);
    int i;
    WordNodePtr newNode;
    for (i = 0; i < strlen(str); i++)
    {
         newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
        if(!newNode)
        {
            exit(0);
        }
        newNode->word.wordType = Directive;
        newNode->word.directive.wordType = givenWordType;
        newNode->word.directive.address = (vars->DC);
        newNode->word.directive.asciz =  str[i];
        addWordToList(head, newNode);
    }


    /*add the \0 char to end the string*/
    newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
    if(!newNode)
    {
        exit(0);
    }
    newNode->word.wordType = Directive;
    newNode->word.directive.wordType = givenWordType;
    newNode->word.directive.address = vars->DC;
    newNode->word.directive.asciz =  '\0';
    addWordToList(head, newNode);
    vars->DC+=(vars->DC+1+i);
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

/*free word list*/
void freeWordList(WordNodePtr *head)
{
    WordNodePtr temp = *head;
    while(temp)
    {
        temp = (temp)->next;
        free(*head);
        *head=temp;
    }
}