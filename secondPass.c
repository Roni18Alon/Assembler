/* Name: secondPass.c
 * Author: Roni Alon & Noa Even
 * Description: in this function we will pass on the file for the second time and complete the missing data in the code Instructions
 *
*/
#include "secondPass.h"

void secondPassAnalysis(globalVariables *,char *,char *, char *, char *,char *);
void varsResetForSecondPass(globalVariables *);

void secondPass(globalVariables *vars) {

    int lineAnalyzed;

    char line[LINE_LENGTH] = {0};
    char lineCpy[LINE_LENGTH] = {0};
    char before[LINE_LENGTH] = {0};
    char after[LINE_LENGTH] = {0};
    char lineCpyAfterLabel[LINE_LENGTH] = {0};
    char label[LABEL_LENGTH] = {0};


    varsResetForSecondPass(vars); /*reset IC=100,DC=0 , lineNumber=1*/

    while (!feof(vars->file)) {


        resetStrings(line, lineCpy, before, after, lineCpyAfterLabel, label);

        fgets(line, LINE_LENGTH, vars->file); /*get a line*/

        strcpy(lineCpy, line);
        strip(lineCpy); /*strip white chars*/

        lineAnalyzed = isEmptyOrCommentLine(lineCpy);/*analyzed if empty or command*/
        if (lineAnalyzed == EMPTY_OR_COMMENT) {
            vars->currentLine++;
            continue; /*if the line is an empty line or command line - the assembler ignores*/
        }
        secondPassAnalysis(vars,lineCpy,before, after ,label,lineCpyAfterLabel);

        if (vars->type != NoError) /*we found an error-print*/
        {
            printErrors(vars);
            vars->type=NoError;
        }
        vars->currentLine++;
    }
    /*we passed on the file for the second time*/
}



void secondPassAnalysis(globalVariables *vars,char *lineCpy,char *before, char *after , char *label,char *lineCpyAfterLabel)
{
    Bool hasLabel,directiveSecondPass;
    WordType word;
    int instructionNum;
    InstructionWordType commandType;

    /*add bool function to check if we have a label*/
    hasLabel = foundLabel(lineCpy, before, after);

    if (hasLabel == True) { /*we found a label*/
        strcpy(label, before);
        strcpy(lineCpyAfterLabel, after);
    } else { /*we couldn't fina d label, by split fun before=line*/
        strcpy(lineCpyAfterLabel, lineCpy);
    }

    strip(lineCpyAfterLabel);
    word = directiveOrInstruction(lineCpyAfterLabel, before, after,vars); /*check if Directive or Instruction or none*/
    if (word == Directive) {
        directiveSecondPass = isDirectiveSecondPass(before);
        if (directiveSecondPass == True) /*it's an Entry Directive*/
        {
            entryDirectiveSecondPass(vars, after);
        }
    } else { /*if it is not a directive it must be an instruction*/

        instructionNum = instructionValidName(before); /*get the instruction number*/
         commandType = commandGroup(instructionNum);
        isInstructionSecondPass(after, commandType, instructionNum, vars);
        vars->IC += 4;
    }

}


void varsResetForSecondPass(globalVariables *vars) {
    vars->DC = START_VALUE;
    vars->IC = IC_START;
    vars->currentLine = FIRST_ROW;
}