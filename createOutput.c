
/* Name: createOutput.c
 * Author: Roni Alon & Noa Even
 * Description: Include functions to create the output from the assembler process.
*/

#include "createOutput.h"

void outputInstruction(InstructionWord ,FILE *);
void outputDirective(DirectiveWord ,FILE *);
void outputByte(char,unsigned long,FILE *);

/*print the word list - first instructions- code and than the directives - data*/
void outputObject(globalVariables *vars) {

    char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
    FILE *file;
    WordNodePtr temp;
    /* create object file with the title the lengths */
    temp = vars->headWordList;

    sprintf(filename, "%s.ob", vars->filename);
    file = fopen(filename, "w");

    fprintf(file,"      %02d  %02d \n", (vars->ICF-IC_START),vars->DCF);

    /*print instruction */
    while (temp) {
        if (temp->word.wordType == Instruction) {
            outputInstruction(temp->word.wordUnion.instruction, file);
        }
        temp=temp->next;
    }

    temp = vars->headWordList;
    /*print Directive */
    while (temp) {
        if (temp->word.wordType == Directive) {
            outputDirective(temp->word.wordUnion.directive, file);
        }
        temp=temp->next;
    }
}
/*print a word from instruction type*/
void outputInstruction(InstructionWord wordToPrint,FILE *file)
{
    unsigned long mask= 0xff;
    unsigned long result;
    int i;
    fprintf(file,"%04lu  ", wordToPrint.address);
    for ( i = 0; i <NUM_OF_BYTES ; i++) {
        result=((wordToPrint.code.bytes & mask) >> (BITS_IN_BYTE*i));
        fprintf(file,"%02lX  ", result);
        mask<<=BITS_IN_BYTE;                       /*mask=maks<<8*/
    }
    fprintf(file,"\n");
}
/*print a word from directive type*/
void outputDirective(DirectiveWord wordToPrint,FILE *file) {
    long mask=0xFF;
    long wordToPrintValue,shifted;
    char result;
    int i;

    if (wordToPrint.wordType == D_BYTE) {
        outputByte(wordToPrint.data.db, wordToPrint.address, file);
    } else if (wordToPrint.wordType == D_HALF) {
        outputByte(mask & wordToPrint.data.dh, wordToPrint.address, file); /*print the first byte*/
        outputByte(mask & (wordToPrint.data.dh >> 8), wordToPrint.address + 1, file); /*print the second byte*/
    } else {
        if (wordToPrint.wordType == D_WORD) {
            mask = 0xFF;
            for (i = 0; i < NUM_OF_BYTES; i++) {
                wordToPrintValue = wordToPrint.data.dw;
                shifted = wordToPrintValue >> (i*BITS_IN_BYTE);
                 result = mask & shifted;
                outputByte(result, wordToPrint.address+i, file);
            }
        } else {
            outputByte(wordToPrint.data.asciz, wordToPrint.address, file);
        }
    }
}

/*print a single byte in hexa*/
void outputByte(char byte,unsigned long address,FILE *file)
{

    if(address%4==0)
    {
        fprintf(file,"%04lu  ",address);
    }
    fprintf(file,"%02X  ",byte&0xFF);
    if((address+1)%NUM_OF_BYTES==0)
    {
        fprintf(file,"\n");
    }
}
/*This function print the entry labels if we have*/
void outputEntries(globalVariables *vars) {

    char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
    FILE *file;
    entryListPtr entryLabel;

    entryLabel = vars->headEntryList;
    if (entryLabel == NULL) return; /* don't create output file*/

    /* create object file with the title the lengths */
    sprintf(filename, "%s.ent", vars->filename);
    file = fopen(filename, "w");

    while (entryLabel) {
        fprintf(file, "%s %04lu\n", entryLabel->labelName, entryLabel->value);
        entryLabel = entryLabel->next;
    }

    fclose(file);

}

/*This function print the external labels if we have*/
void outputExternals(globalVariables *vars) {

   char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
   FILE *file;
    externalListPtr externalLabel ;
    externalLabel = vars->headExternList;
    if (externalLabel==NULL) return; /* don't create output file*/
    /* create object file with the title the lengths */
   sprintf(filename, "%s.ext", vars->filename);

   file = fopen(filename, "w");

    while (externalLabel)
    {
        fprintf( file,"%s %04lu\n", externalLabel->labelName, externalLabel->value);
        externalLabel=externalLabel->next;
    }

    fclose(file);
}

/*create output files*/
void createOutput(globalVariables *vars) {
    outputObject(vars);
    outputEntries(vars);
    outputExternals(vars);
}