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

/*create a copy fore a given word node - Instruction*/
void createWordNode(WordNodePtr nodeToAdd,globalVariables *vars)
{
    WordNodePtr wordCpy = (WordNodePtr) calloc(1, sizeof(WordNode));
    if(!wordCpy)
    {
        exit(0);
    }

    if(nodeToAdd->word.wordUnion.instruction.wordType== R_WORD)
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.wordUnion.instruction.wordType=R_WORD;
        wordCpy->word.wordUnion.instruction.address= nodeToAdd->word.wordUnion.instruction.address;
        wordCpy->word.wordUnion.instruction.code.rWord.opcode=nodeToAdd->word.wordUnion.instruction.code.rWord.opcode;
        wordCpy->word.wordUnion.instruction.code.rWord.rs= nodeToAdd->word.wordUnion.instruction.code.rWord.rs;
        wordCpy->word.wordUnion.instruction.code.rWord.rt= nodeToAdd->word.wordUnion.instruction.code.rWord.rt;
        wordCpy->word.wordUnion.instruction.code.rWord.rd= nodeToAdd->word.wordUnion.instruction.code.rWord.rd;
        wordCpy->word.wordUnion.instruction.code.rWord.funct= nodeToAdd->word.wordUnion.instruction.code.rWord.funct;
        wordCpy->word.wordUnion.instruction.code.rWord.unused= nodeToAdd->word.wordUnion.instruction.code.rWord.unused;
        addWordToList(&(vars->headWordList),wordCpy);
    }
    if(nodeToAdd->word.wordUnion.instruction.wordType== I_WORD )
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.wordUnion.instruction.wordType=I_WORD;
        wordCpy->word.wordUnion.instruction.address= nodeToAdd->word.wordUnion.instruction.address;
        wordCpy->word.wordUnion.instruction.code.iWord.opcode=nodeToAdd->word.wordUnion.instruction.code.iWord.opcode;
        wordCpy->word.wordUnion.instruction.code.iWord.rs=  nodeToAdd->word.wordUnion.instruction.code.iWord.rs;
        wordCpy->word.wordUnion.instruction.code.iWord.rt=  nodeToAdd->word.wordUnion.instruction.code.iWord.rt;
        wordCpy->word.wordUnion.instruction.code.iWord.immed=  nodeToAdd->word.wordUnion.instruction.code.iWord.immed;
        addWordToList(&(vars->headWordList),wordCpy);
    }
    if(nodeToAdd->word.wordUnion.instruction.wordType== J_WORD)
    {
        wordCpy->word.wordType=Instruction;
        wordCpy->word.wordUnion.instruction.wordType=J_WORD;
        wordCpy->word.wordUnion.instruction.address= nodeToAdd->word.wordUnion.instruction.address;
        wordCpy->word.wordUnion.instruction.code.jWord.opcode=nodeToAdd->word.wordUnion.instruction.code.jWord.opcode;
        wordCpy->word.wordUnion.instruction.code.jWord.reg=  nodeToAdd->word.wordUnion.instruction.code.jWord.reg;
        wordCpy->word.wordUnion.instruction.code.jWord.address=  nodeToAdd->word.wordUnion.instruction.code.jWord.address;
        addWordToList(&(vars->headWordList),wordCpy);
    }


}

/*this function adds the dw,dh,db operand to word list*/
void addDirectiveByteToWordList( long validInput[LINE_LENGTH], WordNodePtr *head, DirectiveWordType givenWordType,globalVariables *vars, int counter)
{
    int i;
    WordNodePtr newNode;
    if (givenWordType == D_BYTE) {
        for (i = 0; i < counter; i++) {
            newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
            newNode->word.wordType = Directive;
            newNode->word.wordUnion.directive.wordType = givenWordType;
            newNode->word.wordUnion.directive.address = vars->DC;
            newNode->word.wordUnion.directive.data.db = validInput[i];
            vars->DC += D_B_BYTE_NUM;
            addWordToList(head, newNode);
        }

    } else {
        if (givenWordType == D_HALF) {
            {
                for (i = 0; i < counter; i++) {
                    newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                    if (!newNode) {
                        exit(0);
                    }
                    newNode->word.wordType = Directive;
                    newNode->word.wordUnion.directive.wordType = givenWordType;
                    newNode->word.wordUnion.directive.address = vars->DC;
                    newNode->word.wordUnion.directive.data.dh = validInput[i];
                    vars->DC += D_H_BYTE_NUM;
                    addWordToList(head, newNode);
                }

            }
        } else {
            /* givenWordType==D_WORD WORD=4 Bytes */
            for (i = 0; i < counter; i++) {
                newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
                if (!newNode) {
                    exit(0);
                }
                newNode->word.wordType = Directive;
                newNode->word.wordUnion.directive.wordType = givenWordType;
                newNode->word.wordUnion.directive.address = vars->DC;
                newNode->word.wordUnion.directive.data.dw = validInput[i];
                vars->DC += D_W_BYTE_NUM;
                addWordToList(head, newNode);
            }

        }

    }
}
/*this function adds the asciz string to word list , each char to a node and add \0 */
void addDirectiveAsciz(char *str, WordNodePtr *head, DirectiveWordType givenWordType, globalVariables *vars)
{
    int i;
    WordNodePtr newNode;
    ascizStr(str);
    for (i = 0; i < strlen(str); i++)
    {
         newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
        if(!newNode)
        {
            exit(0);
        }
        newNode->word.wordType = Directive;
        newNode->word.wordUnion.directive.wordType = givenWordType;
        newNode->word.wordUnion.directive.address = (vars->DC);
        newNode->word.wordUnion.directive.data.asciz =  str[i];
        vars->DC+=ASCIZ_BYTE_NUM;
        addWordToList(head, newNode);
    }


    /*add the \0 char to end the string*/
    newNode = (WordNodePtr) calloc(1, sizeof(WordNode)); /*creat new node*/
    if(!newNode)
    {
        exit(0);
    }
    newNode->word.wordType = Directive;
    newNode->word.wordUnion.directive.wordType = givenWordType;
    newNode->word.wordUnion.directive.address = (vars->DC);
    newNode->word.wordUnion.directive.data.asciz =  '\0';
    addWordToList(head, newNode);
    vars->DC+=ASCIZ_BYTE_NUM;
}

/*this function adds after the first pass to each directive node in the word list the final IC value to the address*/
void addDirectiveICF(WordNodePtr *head,globalVariables *vars)
{
    WordNodePtr temp = *head;

    while(temp) {
        if(temp->word.wordType == Directive) {
            temp->word.wordUnion.directive.address +=vars->ICF;
        }
        temp = temp->next;
    }

}

void addLabelAddress(WordNodePtr *head,globalVariables *vars,long labelAddress,InstructionWordType commandType, Bool isExtern)
{
    long finalIAddress;
    WordNodePtr temp = *head;
    while (temp != NULL) {
        if (temp->word.wordUnion.instruction.address == vars->IC) /*find the right node */
        {
            if (commandType == J_WORD)  /*if it's a J - just update the address from label list*/
            {
                if (isExtern == True) {
                    temp->word.wordUnion.instruction.code.jWord.address = 0;
                } else { temp->word.wordUnion.instruction.code.jWord.address = labelAddress; }
            } else {
                if (commandType == I_WORD) /*if it's an I-Branch update the immed */
                {
                    finalIAddress = labelAddress -(temp->word.wordUnion.instruction.address); /*the final address (Immediate value) will be the sub between address from label list and current address*/
                    temp->word.wordUnion.instruction.code.iWord.immed = finalIAddress;
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