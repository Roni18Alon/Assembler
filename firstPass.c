/* Name: firstPass.c
 * Author: Roni Alon & Noa Even
 * Description: in this function we will pass on the file for the first time and Start to analyzed it
 *
*/

#include "firstPass.h"


void firstPass(globalVariables *vars) {

    char line[LINE_LENGTH] = {0};
    char lineCpy[LINE_LENGTH] = {0};
    char before[LINE_LENGTH] = {0};
    char after[LINE_LENGTH] = {0};
    char lineCpyAfterLabel[LINE_LENGTH] = {0};
    char label[LABEL_LENGTH] = {0};

   // char fileName[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH]={0};
   // strcpy(vars->filename, fileName);


    Bool validLineLength;
    int  lineAnalyzed;

    while (!feof(vars->file)) {


        resetStrings(line,lineCpy,before,after,lineCpyAfterLabel,label);

        fgets(line, LINE_LENGTH, vars->file); /*vars->file*/

        validLineLength=getLine(line,lineCpy,vars);
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

    int finalMemory=vars->IC+vars->DC;
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
    Bool hasLabel;
    WordType word;
    int instructionNum;

    /*create a new word node*/
    WordNodePtr currentWord = (WordNodePtr) calloc(1, sizeof(WordNode));
    if (!currentWord) {
        exit(0);
    }

    /*create a new label node*/
    labelListPtr currentLabel = (labelListPtr) calloc(1, sizeof(labelListPtr));
    if (!currentLabel) {
        exit(0);
    }

    /*add bool function to check if we have a label*/
    hasLabel=labelAnalysis( lineCpy,before, after,label,lineCpyAfterLabel,vars ,currentLabel);

    strip(lineCpyAfterLabel);
    word = directiveOrInstruction(lineCpyAfterLabel, before, after, vars); /*check if Directive or Instruction or none*/
    if (word == Directive) {
        isDirectiveFirstPass(before, after,label ,vars, hasLabel, currentLabel, currentWord);
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
        getToNextLine(vars->file);
        return False;
    }
    return True;
}
