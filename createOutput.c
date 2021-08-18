//
// Created by ronia on 18/08/2021.
//

#include "createOutput.h"
void outputObject(globalVariables *vars) {

    char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
    FILE *file;
    /* create object file with the title the lengths */
    sprintf(filename, "%s.ob", vars->filename);

    file = fopen(filename, "w");

    int i = 0;

    // first line
    // vars->IC

    //vars->DC
    // iterate over labelListPtr for labels and headWordList for memory data
    labelListPtr headLabelTable = vars->headLabelTable;
    WordNodePtr headWordList = vars->headWordList;

    while (headLabelTable) {
        printf("%ld", headLabelTable->address); // print label address
        for (i = 0; i < 4; ++i) {
            if (!headWordList) {
                break;
            }
            printf("%ld ", headLabelTable->address); // print label address
            if (headWordList->word.wordType == Instruction) {
                printf("%x ", headWordList->word.instruction);
            } else {
                if (headWordList->word.wordType == Directive) {
                    printf("%x ", headWordList->word.directive);
                }
                headWordList = headWordList->next;
            }
            headLabelTable = headLabelTable->next;
        }
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
            fprintf(file, "%s %07lu\n", entryLabel->labelName, entryLabel->value);
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
        fprintf(file, "%s %07lu\n", externalLabel->labelName, externalLabel->value);
        externalLabel=externalLabel->next;
    }

    fclose(file);


}


void createOutput(globalVariables *vars) {
    outputObject(vars);
    outputEntries(vars);
    outputExternals(vars);
}