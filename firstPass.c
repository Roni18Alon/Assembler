/* Name: firstPass.c
 * Author: Roni Alon & Noa Even
 * Description: in this function we will pass on the file for the first time and Start to analyzed it
 *
*/

#include "firstPass.h"

void firstPassAnalysis(globalVariables *,char *,char *, char * , char *,char *);
void getToNextLine(FILE *f);
Bool getLine(char *,char *,globalVariables *);


void firstPass(globalVariables *vars) {

    char line[LINE_LENGTH] = {0};
    char lineCpy[LINE_LENGTH] = {0};
    char before[LINE_LENGTH] = {0};
    char after[LINE_LENGTH] = {0};
    char lineCpyAfterLabel[LINE_LENGTH] = {0};
    char label[LABEL_LENGTH] = {0};

    Bool validLineLength;
    int  lineAnalyzed, finalMemory;

    while (!feof(vars->file)) {

        resetStrings(line,lineCpy,before,after,lineCpyAfterLabel,label);

        fgets(line, LINE_LENGTH, vars->file); /*get a new line from the file*/

        validLineLength=getLine(line,lineCpy,vars); /*check if the line is in the valid length - 80 chars*/
        if (validLineLength==False)
        {
           vars->currentLine++;
           continue;  /*get the next line*/
        }

        strip(lineCpy); /*strip white chars from the side*/

        lineAnalyzed = isEmptyOrCommentLine(lineCpy);
        if (lineAnalyzed == EMPTY_OR_COMMENT) {
            vars->currentLine++;
            continue; /*if the line is an empty line or command line - the assembler ignores*/
        }

        /*analyze if its a directive or instruction*/

        firstPassAnalysis(vars,lineCpy,before,after,label,lineCpyAfterLabel);

        if(vars->type != NoError)
        {
            printErrors(vars); /*print the error in the current line*/
            vars->type=NoError;
        }
        vars->currentLine++;

    }

    finalMemory=vars->IC+vars->DC;
    if(finalMemory>=MAX_MEMORY)
    {
        vars->type = MaxMemory;
        vars->errorFound = True;
        printErrors(vars);
    }

    /*we finished to read the file*/
    if(vars->errorFound == False) /*we found errors - don't continue to second Pass */
    {
        /*we haven't found any errors */
        vars->ICF=vars->IC;
        vars->DCF=vars->DC;

        updateLabelTableICF(&(vars->headLabelTable),vars); /*update the value of data labels with final IC*/
        addDirectiveICF(&(vars->headWordList),vars); /*add the final IC value to the directive values in Word list*/
    }

}



void firstPassAnalysis(globalVariables *vars,char *lineCpy,char *before, char *after , char *label,char *lineCpyAfterLabel)
{
    Bool hasLabel,found_Label;
    WordType word;
    int instructionNum;
    int validLabel;

    /*create a new word node*/
    WordNodePtr currentWord;
    labelListPtr currentLabel;

    currentWord = (WordNodePtr) calloc(1, sizeof(WordNode));
    if (!currentWord) {
        exit(0);
    }

    /*create a new label node*/
     currentLabel = (labelListPtr) calloc(1, sizeof(labelList));
    if (!currentLabel) {
        exit(0);
    }


   hasLabel=False;
    /*add bool function to check if we have a label*/
    found_Label = foundLabel(lineCpy, before, after, vars); /*look for a label and the checks if it's a valid label*/
    if(found_Label==True) /*if we found a label - check if a valid label*/
    {
        validLabel = isLegalLabel(before, vars);
        /*to find if we have a label*/
        if (validLabel == VALID_LABEL) {
            strip(before);
            hasLabel = True;
            strcpy(label, before);  /*update label name*/
            strcpy(currentLabel->labelName, before); /*update label name in current label*/
            strcpy(lineCpyAfterLabel, after);
        }
        else{ /*we found label but it's not a valid one*/
            return;
        }
    }
    else{ /*we didn't find label at all- continue*/
        strcpy(lineCpyAfterLabel, lineCpy);
    }

    strip(lineCpyAfterLabel);
    word = directiveOrInstruction(lineCpyAfterLabel, before, after, vars); /*check if Directive or Instruction or none*/

    if (word == Directive) {
        isDirectiveFirstPass(before, after,label ,vars, hasLabel, currentLabel);
    }
    else {
        if (word == Instruction) {
            instructionNum = instructionValidName(before); /*get the instruction number*/
            isInstructionFirstPass(before, after,label, vars, hasLabel, currentLabel, currentWord, instructionNum);

            vars->IC+=4;
        }
        else { /*not a directive and not an instruction than - None - error*/
            foundError(vars,notDirectiveOrInstruction,before);
        }
    }

    free(currentLabel); /*re-allocate currentLabel*/
    free(currentWord); /*re-allocate currentWord*/

}



/*if we got line with more than 80 chars, "empty" the line*/
void getToNextLine(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n')
            return;
    }
}

Bool getLine(char *line,char *lineCpy,globalVariables *vars)
{
    /*checks if the row is in the length boundaries*/
   int i;
    for (i = 0; i <= LAST_CHAR_IN_LINE; i++) {
        if (line[i] == '\0') {
            strncpy(lineCpy, line, i + 1);
            break;
        }
    }
    /*Check if the line we got is to long - more than 80 chars*/
    if (((i - 1) == LAST_CHAR_IN_LINE) && line[i - 1] != '\0') {

        foundError(vars,LineTooLong,line);
        printErrors(vars);
        vars->type=NoError; /*reset type*/
        getToNextLine(vars->file);
        return False;
    }
    return True;
}
