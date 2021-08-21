
/* Name: createOutput.c
 * Author: Roni Alon & Noa Even
 * Description: Include functions to create the output from the assembler process.
*/

#include "createOutput.h"

void outputInstruction(InstructionWord ,FILE *);
void outputDirective(DirectiveWord ,FILE *);
void outputByte(char,long,FILE *);

void outputObject(globalVariables *vars) {

    char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
    FILE *file;
    /* create object file with the title the lengths */
    sprintf(filename, "%s.ob", vars->filename);

    file = fopen(filename, "w");

    WordNodePtr temp = vars->headWordList;

    fprintf(file,"   %02d  %02d \n", (vars->ICF-IC_START),vars->DCF);

    /*print instruction */
    while (temp) {
        if (temp->word.wordType == Instruction) {
            outputInstruction(temp->word.instruction, file);
        }
        temp=temp->next;
    }

    temp = vars->headWordList;
    /*print Directive */
    while (temp) {
        if (temp->word.wordType == Directive) {
            outputDirective(temp->word.directive, file);
        }
        temp=temp->next;
    }


}

void outputInstruction(InstructionWord wordToPrint,FILE *file)
{
    unsigned long mask= 0xff;
    int i;
    fprintf(file,"%04lu  ", wordToPrint.address);
    for ( i = 0; i <4 ; i++) {
        unsigned long result= (wordToPrint.bytes & mask) >> (8*i);
        fprintf(file,"%02lX  ", result);
        mask<<=8;                       /*mask=maks<<8*/
    }
    fprintf(file,"\n");
}

void outputDirective(DirectiveWord wordToPrint,FILE *file) {
    unsigned long mask;
    if (wordToPrint.wordType == D_BYTE || wordToPrint.wordType == ASCIZ) {
        outputByte(wordToPrint.db, wordToPrint.address, file);
    } else if (wordToPrint.wordType == D_HALF) {
        unsigned char result;
        mask = 0xFF00;
        result = (mask & wordToPrint.dh) >> 8;
        outputByte(result, wordToPrint.address, file);
        mask = 0xFF;
        outputByte(mask & wordToPrint.dh, wordToPrint.address + 1, file);
    } else {
        mask = 0xFF000000;
        int i;
        for (i = 0; i < 4; i++) {
            unsigned char result = mask & wordToPrint.dw;
            result >>= (3 - i) * 8;
            outputByte(result, wordToPrint.address++, file);
            mask >>= 8;
        }

    }
}

void outputByte(char byte,long address,FILE *file)
{
    if(byte%4==0)
    {
        fprintf(file,"%04lu ",address);
    }
    fprintf(file,"%02lx ",byte&0xFF);
    if((address-100+1)%4==0)
    {
        fprintf(file,"\n ");
    }

}

    void outputEntries(globalVariables *vars) {

       char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
       FILE *file;
       /* create object file with the title the lengths */
       sprintf(filename, "%s.ent", vars->filename);

       file = fopen(filename, "w");
       entryListPtr entryLabel = vars->headEntryList;
        while (entryLabel)
        {

            fprintf( file,"%s %04lu\n", entryLabel->labelName, entryLabel->value);
            entryLabel=entryLabel->next;
        }

        fclose(file);

    }


void outputExternals(globalVariables *vars) {

   char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
   FILE *file;
    /* create object file with the title the lengths */
   sprintf(filename, "%s.ext", vars->filename);

   file = fopen(filename, "w");
    externalListPtr externalLabel = vars->headExternList;
    while (externalLabel)
    {
        //setbuf(stdout, 0);
        fprintf( file,"%s %04lu\n", externalLabel->labelName, externalLabel->value);
        externalLabel=externalLabel->next;
    }

    fclose(file);


}


void createOutput(globalVariables *vars) {
    outputObject(vars);
    outputEntries(vars);
    outputExternals(vars);
}