
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
    long mask;
    if (wordToPrint.wordType == D_BYTE) {
        outputByte(wordToPrint.db, wordToPrint.address, file);
    } else if (wordToPrint.wordType == D_HALF) {
        mask = 0xFF;
        outputByte(mask & wordToPrint.dh, wordToPrint.address, file);
        mask = 0xFF00;
        outputByte((mask & wordToPrint.dh) >> 8, wordToPrint.address + 1, file);
    } else {
        if (wordToPrint.wordType == D_WORD) {
            mask = 0xFF;
            int i;
            for (i = 0; i < 4; i++) {
                long wordToPrintValue = wordToPrint.dw;
                long shifted = wordToPrintValue >> i*8;
                char result = mask & shifted;
                outputByte(result, wordToPrint.address+i, file);
            }
        } else {
            outputByte(wordToPrint.asciz, wordToPrint.address, file);
        }
    }
}

void outputByte(char byte,long address,FILE *file)
{

    if(address%4==0)
    {
//        fprintf(file,"\n");
        fprintf(file,"%04lu  ",address);
    }
//    printf("%02X  ",byte&0xFF);
    fprintf(file,"%02X  ",byte&0xFF);
    if((address+1)%4==0)
    {
        fprintf(file,"\n");
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