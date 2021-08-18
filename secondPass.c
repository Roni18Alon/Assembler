//
// Created by ronia on 08/08/2021.
//

#include "secondPass.h"


void secondPass(globalVariables *vars) {

    int lineAnalyzed,instructionNum;
    Bool hasLabel;
    WordType word;
    Bool directiveSecondPass;


    char line[LINE_LENGTH] = {0};
    char lineCpy[LINE_LENGTH] = {0};
    char before[LINE_LENGTH] = {0};
    char after[LINE_LENGTH] = {0};
    char lineCpyAfterLabel[LINE_LENGTH] = {0};
    char label[LABEL_LENGTH] = {0};

    char fileName[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
    strcpy(vars->filename, fileName);

    varsResetForSecondPass(vars); /*reset IC=100,DC=0 , lineNumber=1*/

   while (!feof(vars->file)) {


        resetStrings(line,lineCpy,before,after,lineCpyAfterLabel,label);

        fgets(line, LINE_LENGTH,vars->file);
       vars->currentLine++;

        strcpy(lineCpy,line);
        strip(lineCpy); /*strip white chars*/
        lineAnalyzed = isEmptyOrCommandLine(lineCpy);
        if (lineAnalyzed == 1) continue; /*if the line is an empty line or command line - the assembler ignores*/


        /*create a new label node*/
        labelListPtr currentLabel = (labelListPtr) calloc(1, sizeof(labelListPtr));
        if (!currentLabel) {
            exit(0);
        }

        /*check if we have label - if we do - skip this label*/
        /*add bool function to check if we have a label*/
        hasLabel = foundLabel(lineCpy, before, after, vars, currentLabel);

        if (hasLabel == True) { /*we found a label*/
            strcpy(label, before);
            strcpy(lineCpyAfterLabel, after);
        }
        else { /*we couldn't fina d label, by split fun before=line*/
            strcpy(lineCpyAfterLabel, lineCpy);
        }

        strip(lineCpyAfterLabel);
        word = directiveOrInstruction(lineCpyAfterLabel, before, after, vars); /*check if Directive or Instruction or none*/
        if (word == Directive) {
            directiveSecondPass = isDirectiveSecondPass(before, after, vars, hasLabel, currentLabel);
            if (directiveSecondPass == False)
                continue; /* not an ENTRY directive - continue to the next line*/
            if(directiveSecondPass ==True) /*it's an Entry Directive*/
            {
                entryDirectiveSecondPass(vars,after);
            }
        }
        else{ /*if it is not a directive it must be an instruction*/

            instructionNum = instructionValidName(before); /*get the instruction number*/
            InstructionWordType commandType = commandGroup(instructionNum);
            isInstructionSecondPass(after,commandType,instructionNum,vars);
            vars->IC += 4;
        }
    }
   /*we passed on the file for the second time*/

   if(vars->type!=NoError) /*we found an error-print*/
   {
       printErrors(vars);
   }
}



void varsResetForSecondPass(globalVariables *vars)
{
    vars->DC=0;
    vars->IC=100;
    vars->currentLine=1;
}