/* Name: assembler.c
 * Author: Roni Alon & Noa Even
 * Description: Gets the file and run the assembler process.
*/

#include "assembler.h"


int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        globalVariables *vars;
        char filename[FILE_NAME_LENGTH + AS_EXTENSION_LENGTH];
        char shortFileName[FILE_NAME_LENGTH];
        vars = (globalVariables *) calloc(1, sizeof(globalVariables));

        sprintf(shortFileName, "%s", argv[i]);
        sprintf(filename, "%s.as", argv[i]);

        strcpy(vars->filename, shortFileName);

        vars->file = fopen(filename, "r"); /*open .as file*/

        if (!vars->file) {
            printf("%s: Cannot open file!\n", filename);
            continue;
        }
        printf("Opened File :%s\n", filename);

        /* check that the file isn't empty */
        fseek(vars->file, 0, SEEK_END);

        if (ftell(vars->file) == 0)
            continue; /*to the next file*/
        rewind(vars->file);

        resetVars(vars); /*reset Vars values*/

        firstPass(vars);
        if (vars->errorFound == True) {
            printf("\n");
            freeVars(vars);
            continue;
        }

        printf("Completed First Pass!\n");
        rewind(vars->file);

        secondPass(vars);
        if (vars->errorFound == True) {
            printf("\n");
            freeVars(vars);
            continue;
        }

        printf("Completed Second Pass!\n");
        createOutput(vars);
        freeVars(vars);
        printf("\n");
    }
    return 0;
}

/*reset the global vars*/
void resetVars(globalVariables *vars) {
    vars->IC = IC_START;
    vars->DC = START_VALUE;
    vars->DCF = START_VALUE;
    vars->ICF = START_VALUE;
    vars->errorFound = False;
    vars->currentLine = FIRST_ROW;
}

/*free vars*/
void freeVars(globalVariables *vars) {
    freeLists(vars);
    fclose(vars->file);
    free(vars);
}

/*free all lists and the memory we allocated*/
void freeLists(globalVariables *vars) {
    freeExternList(&vars->headExternList);
    freeEntryList(&vars->headEntryList);
    freeWordList(&vars->headWordList);
    freeLabelList(&vars->headLabelTable);
}


