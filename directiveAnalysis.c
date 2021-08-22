/* Name: directiveAnalysis.c
 * Author: Roni Alon & Noa Even
 * Description: Include functions for Directive command analysis
 *
*/
#include "directiveAnalysis.h"

/*This function analyzes Directive command in the first pass */
void isDirectiveFirstPass(char *before, char *after,char *label ,globalVariables *vars, Bool hasLabel, labelListPtr currentLabel) {

    int directiveNum;
    directiveNum = isValidDirectiveName(before); /*find if it's a valid directive and the num*/

    /* first pass step 6 */
    if (directiveNum != DIRECTIVE_ERROR ) {
        DirectiveWordType directiveType = getDirectiveType(directiveNum); /*find the directive word type*/

        if (directiveNum == DIRECTIVE_BYTE || directiveNum == DIRECTIVE_HALF_WORD || directiveNum == DIRECTIVE_WORD) { /*dw,db,dh*/

            byteDirectiveFirstPass(before,after,label,hasLabel,vars,directiveNum,directiveType, currentLabel); /*dw,db,dh command analysis*/
        }
        else{
            if (directiveNum == DIRECTIVE_ASCIZ) { /*asciz command analysis*/
                ascizDirectiveFirstPass(after,label, hasLabel,vars,directiveType,currentLabel);
            }
            /*not a db,dw,dh,asciz - check if an entry or extern or non=invalid directive*/
            else{
                labelAndEntryOrExtern(hasLabel, directiveNum,vars); /*if we have a label before entry or extern - it's not an error just ignore- don't insert label to label list*/
                if (directiveNum == DIRECTIVE_EXTERN) {
                    Bool externFirstPass = externDirectiveFirstPass(after, vars, currentLabel);
                    if (externFirstPass == False)return;
                    }
                /*directiveNum == DIRECTIVE_ENTRY -in the first pass if we see an entry label - don't do nothing just continue to the next row**/
                }
            }
        }
    else{ /*it's not a valid directive*/
        foundError(vars,InvalidDirective,before);
    }
}

/*This function analyzes dw,db,dh command in First Pass*/
void byteDirectiveFirstPass(char *before, char *after,char *label,Bool hasLabel,globalVariables *vars,int directiveNum,DirectiveWordType directiveType,labelListPtr currentLabel)
{
    long validInput[LINE_LENGTH] = {0};
    Bool validDirectiveParam = dataAnalysis(after, before, after, vars, validInput,directiveNum);/*analyzed the operands of directive row*/
    if (validDirectiveParam == False) return;
    if (hasLabel == True)
        /*we have a label and a data - add to symbol table the value is the DC before insert the numbers to the list*/
    {
        Bool labelBeforeDirective = labelBeforeDirectiveCommand(label, vars, currentLabel);
        if (labelBeforeDirective == False) return ; /*if False - return false and get the next row, else continue*/
    }
    /*not a label only directive */
    addDirectiveByteToWordList(validInput, &(vars->headWordList), directiveType, vars);
}


/*This function analyzes asciz command in First Pass*/
void ascizDirectiveFirstPass(char *after,char *label,Bool hasLabel,globalVariables *vars,DirectiveWordType directiveType,labelListPtr currentLabel)
{
   Bool validAsciz,labelBeforeDirective;
    validAsciz = ascizAnalysis(after, vars);
    if (validAsciz == False) return;

    /*a valid param to asciz directive a valid string starts and ends with " */

    if (hasLabel == True) { /*if the label flag is on - we have label*/
        labelBeforeDirective = labelBeforeDirectiveCommand(label, vars, currentLabel);
        if (labelBeforeDirective == False) return; /*if False - return false and get the next row, else continue*/
    }
    /*no label just a directive - add to word table*/
    addDirectiveAsciz(after, &(vars->headWordList), directiveType, vars);
}



Bool isDirectiveCommand(char *command) {
    return command[0] == '.' ? True : False;
}

/*by given string (char array) returns the number of directive command*/
int isValidDirectiveName(char *str)
{
    if(strcmp(str,".db")==0)
        return DIRECTIVE_BYTE; /*1*/
    if(strcmp(str,".dw")==0)
        return DIRECTIVE_WORD;  /*4*/
    if(strcmp(str,".dh")==0)
        return DIRECTIVE_HALF_WORD; /*2*/
    if(strcmp(str,".asciz")==0)
        return DIRECTIVE_ASCIZ; /*3*/
    if(strcmp(str,".extern")==0)
        return DIRECTIVE_EXTERN; /*5*/
    if(strcmp(str,".entry")==0)
        return DIRECTIVE_ENTRY; /*6*/
    else {return DIRECTIVE_ERROR;}  /*-1*/

}
/*this function returns the directive word type by given command number*/
DirectiveWordType getDirectiveType(int directiveNum)
{
    if(directiveNum==DIRECTIVE_BYTE) return D_BYTE; /*.db*/
    if(directiveNum==DIRECTIVE_HALF_WORD) return D_HALF; /*.dh*/
    if(directiveNum==DIRECTIVE_WORD) return D_WORD; /*.dw*/
    if(directiveNum==DIRECTIVE_ASCIZ) return ASCIZ;  /*.asciz*/

}

/*This function analysis the operands of db,dw,dh directive commands*/
Bool dataAnalysis(char *str,char *before,char *after,globalVariables *vars,long validInput [LINE_LENGTH],int directive) {
    int  i;
    long number;
    int counter=0;
    int delimiter;
    long validBitRange;
    char line[LINE_LENGTH] = {0};
    int lastChar;

    strcpy(line, after);
    lastChar = strlen(line);

    if (line[lastChar-1] == ',') /* 3,4,5,7, situation*/
    {
        foundError(vars,ExtraneousComma,line);
        return False;
    }
    /*maybe add a check for non digit in the last char??*/
    for (i = 0; i < (LINE_LENGTH - 2) && line[i] != '\0'; i++) /* '\0' is the end of string char */
    {
        memset(line, 0, LINE_LENGTH);
        strcpy(line, after);

        memset(before, 0, LINE_LENGTH);
        memset(after, 0, LINE_LENGTH);

        delimiter = split(line, ",", before, after);
        strip(before);
        strip(after);

        if (delimiter == VALID_SPLIT) {
            strip(before);
            if ((strlen(before)==0||strcmp(before," ")==0||strcmp(before,"\t")==0) && i == 0) /*the first num starts without a comma before - ,3,4,...*/
            {
                foundError(vars,CommaBeforeFirstParam,before);
                return False;
            }
            if ((strlen(before)==0||strcmp(before," ")==0||strcmp(before,"\t")==0) && i != 0) /*+65,,7...*/
            {
                foundError(vars,CommaBetweenParams,before);
                return False;
            }
            number = isValidNumberDirective(before, vars); /*errors will update in the function*/
            if (number == LONG_MIN) {
                return False; /*error - not a valid number*/
            }
            validBitRange = validNumByDirective(directive, number,before,vars); /*check if the num is in the correct range according directive type*/
            if (validBitRange == VALID_BIT_RANGE) {
                validInput[i] = number;
                counter++;
                continue;
            } else {return False;}

        } else {/*we couldn't find a comma*/
            if (strlen(before)==0||strcmp(before," ")==0||strcmp(before,"\t")==0) /*if we couldn't find a comma, by split function before gets line value,if empty- missing operands*/
            {
                foundError(vars,MissingOperand,before);
                return False;
            } else {/*not an empty string check if it's a valid operand*/
                number = isValidNumberDirective(before, vars); /*errors will update in the function*/
                if (number == LONG_MIN) {
                    return False; /*error - not a valid number*/
                }
                validBitRange = validNumByDirective(directive, number,before,vars); /*check if the num is in the correct range according directive type*/
                if (validBitRange == VALID_BIT_RANGE) {
                    validInput[i] = number;
                    counter++;
                    break; /*couldn't find a comma and we updates the last number in array*/
                }
            }
            break; /*couldn't find a comma */
        }
    }
    /*block the operands long array*/
    validInput[counter]=LONG_MAX;
    return True;
}


/*This function returns True if the asciz operand is a valid string, False otherwise*/
Bool ascizAnalysis(char *str,globalVariables *vars)
{
    int valid=isValidString(str,vars); /*check if a valid string*/
    if(valid==VALID_STRING)return True;
    else{ return False;}
}



/*print a warning if we have a label before directive entry or extern Print Dynamically*/
void labelAndEntryOrExtern(Bool hasLabel,int directiveNum,globalVariables *vars)
{
    if (directiveNum==DIRECTIVE_ENTRY && hasLabel==True) /*we have a label and a directive entry - error*/
    {
        vars->type=labelBeforeEntry;
        printf("\n%s:Line %d:Warning!Illegal Label before Entry\n", vars->filename,vars->currentLine);
    }
    if(directiveNum==DIRECTIVE_EXTERN && hasLabel==True)
    {
        vars->type=labelBeforeExtern;
        printf("\n%s:Line %d:Warning!Illegal Label before External\n", vars->filename,vars->currentLine);
    }
}

/*This function return True if in the second Pass it's an entry command , False otherwise*/
Bool isDirectiveSecondPass(char *before) {
    int directiveNum;
    directiveNum = isValidDirectiveName(before); /*find if it's a valid directive and the num*/
    if (directiveNum != DIRECTIVE_ENTRY)
    {
        return False; /*if it's not an entry continue to the next line*/
    }
    /*an entry label */
    return True;
}

/*This function handles cases where there is a label before db,dw,dh,asciiz directives. check if the label is already in the label list and if not update the label list*/
Bool labelBeforeDirectiveCommand(char *labelName, globalVariables *vars, labelListPtr currentLabel)
{
    int ValidLabelName;
    ValidLabelName = labelNameCompare(&(vars->headLabelTable),labelName,vars); /*check if the label name wasn't shown in the table already*/
    if (ValidLabelName == VALID_LABEL) { /* a label isn't in the table*/
        updateLabel(currentLabel,vars->DC,Data,NoEntryExtern); /*update the current label node*/
        createLabelNode(currentLabel,vars); /*create a copy and add to label list*/
        return True;
    }

    else{ return False;  /*we found the label in the label table*/}
}

/*This function checks the operand label in directive extern command*/
Bool externDirectiveFirstPass(char *after ,globalVariables *vars,labelListPtr currentLabel)
{
    int ValidLabelName;
    Bool labelWithExtern,externLabel;

    strip(after);
    externLabel = isLegalLabel(after, vars); /*check if  the operand label is valid label by syntax*/

    if (externLabel == LABEL_ERROR) { /*not a valid label - return an error*/
        return False;
    }
    /*else- a valid label check if already exists without external type or with */

    ValidLabelName = labelNameCompare(&(vars->headLabelTable), after, vars);
    labelWithExtern = isLabelExternal(&(vars->headLabelTable), after, vars);


    if (ValidLabelName == VALID_LABEL || labelWithExtern ==True) {
        /*label is not exists or if exists with external label and add to label table*/
        strcpy(currentLabel->labelName,after); /*update the label we want to add name*/
        updateLabel(currentLabel,0,NoCodeOrData,Extern);
        createLabelNode(currentLabel,vars); /* create a copy and add to label list*/
        return True;
    } else {
        return False;
    }
}


/*this function handle in the second pass on entry directive commands*/
void entryDirectiveSecondPass(globalVariables *vars,char *str)
{
    Bool EntryLabel;

    EntryLabel=isLabelEntry(&(vars->headLabelTable),str,vars); /*check if the given entry label exists and add to the label list the attribute to this label as -entry*/
    if(EntryLabel==True) /*add to entry list*/
    {
        long entryValue=EntryValueAfterSecondPass(&(vars->headLabelTable),str);
        if(entryValue!=LABEL_ERROR)
        {
            createEntryNode(str,entryValue,vars);/*add to entry list*/
        }
    }
}