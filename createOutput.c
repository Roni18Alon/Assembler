
/* Name: createOutput.c
 * Author: Roni Alon & Noa Even
 * Description: Include functions to create the output from the assembler process.
*/

#include "createOutput.h"
//void outputObject(globalVariables *vars) {

//    char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
 //   FILE *file;
//    /* create object file with the title the lengths */
 //   sprintf(filename, "%s.ob", vars->filename);

 //   file = fopen(filename, "w");

 //   int i = 0;

    // first line
    // vars->IC

    //vars->DC
    // iterate over labelListPtr for labels and headWordList for memory data
//    labelListPtr headLabelTable = vars->headLabelTable;
 //   WordNodePtr temp = vars->headWordList;

 //   while (temp) {
 //       if(temp->word.wordType==Instruction){
 //           printf("%04ld ", headLabelTable->address);
 //       }
 //       printf("%04ld ", headLabelTable->address); // print label address
 //       for (i = 0; i < 4; ++i) {
  //          if (!temp) {
  //              break;
 //           }
 //           printf("%ld ", headLabelTable->address); // print label address
 //           if (temp->word.wordType == Instruction) {
  //              printf("%x ", temp->word.instruction);
  //          } else {
  //              if (temp->word.wordType == Directive) {
  //                  printf("%x ", temp->word.directive);
  //              }
  //              temp = temp->next;
   //         }
   //         headLabelTable = headLabelTable->next;
  //      }
  //  }
//}

    void outputEntries(globalVariables *vars) {

       char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
       FILE *file;
       // /* create object file with the title the lengths */
       sprintf(filename, "%s.ent", vars->filename);

       file = fopen(filename, "w");
       entryListPtr entryLabel = vars->headEntryList;
        while (entryLabel)
        {
            //(stdout, 0);
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
//    outputObject(vars);
    outputEntries(vars);
    outputExternals(vars);
}