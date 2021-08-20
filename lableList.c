/* Name: labelList.c
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze and handle  the label list like add, search for a label in the list
 *
*/

#include "lableList.h"

/*add a label node to the label list*/
void addLabelToList(labelListPtr *head, labelListPtr labelToAdd) {

    labelListPtr temp = *head;
    if(temp == NULL) {
        *head = labelToAdd;
        return;
    }

    while(temp->next) {
        temp = temp->next;
    }
    temp->next = labelToAdd;
    labelToAdd->next=NULL;
}



/*This function create an external label by given params - label name and address (value)*/
void createLabelNode(labelListPtr labelToAdd, globalVariables *vars)
{
    labelListPtr labelCpy = (labelListPtr) calloc(1, sizeof(labelList));
    if(!labelCpy)
    {
        exit(0);
    }

    strcpy(labelCpy->labelName,labelToAdd->labelName);
    labelCpy->address=labelToAdd->address;
    labelCpy->codeOrData=labelToAdd->codeOrData;
    labelCpy->entryOrExtern=labelToAdd->entryOrExtern;
    addLabelToList(&(vars->headLabelTable), labelCpy);
}

/*to identify if we already have this label in this label table*/
int labelNameCompare(labelListPtr *head,char *labelName,globalVariables *vars)
{
    labelListPtr temp = *head;
    int res;
    while (temp)
    {
        res= strcmp(temp->labelName,labelName);
        if(res==0) /*we already have this label name - Error*/
        {
            foundError(vars,LabelExistsInTable,labelName);
            return LABEL_EXISTS;
        }
        temp = temp->next;
    }
    return VALID_LABEL;
}

/*this function search for a given operand label name the value (address) of the label in the list*/
long findLabel(labelListPtr *head, char *str,globalVariables *vars, InstructionWordType commandType)
{
    labelListPtr temp = *head;
    int res;
    while (temp != NULL)
    {
        res= strcmp(temp->labelName,str);
        if(res==0) /*we found the label*/
        {
            return temp->address;
        }
        temp = temp->next;
    }
    if(commandType==J_WORD)
    {
        foundError(vars,JCommandLabelDontExists,str);
    }
    if(commandType==I_WORD)
    {
        foundError(vars,IBranchLabelDontExists,str);
    }
    return LABEL_ERROR;
}


/*This function return False if  the external label we want to add is already exists without external attribute , True otherwise*/
Bool isLabelExternal(labelListPtr *head, char *labelName,globalVariables *vars)
{
    labelListPtr temp = *head;
    int res;
    while (temp != NULL )
    {
        res= strcmp(temp->labelName,labelName);
        if(res==0) /*we already have this label name*/
        {
            if(temp->entryOrExtern==NoEntryExtern) /*check if the existed label is an extern*/
            {
                foundError(vars,LabelExistsWithoutExternal,labelName);
                return False;
            }
        }
        temp = temp->next;
    }
    return True;
}

/*This function return False if given I branch operand label is External Label -  an I Branch cannot be an external,True otherwise*/
Bool existsLabelExternalIBranch(labelListPtr *head, char *str,globalVariables *vars)
{
    labelListPtr temp = *head;
    int res;
    while (temp != NULL )
    {
        res= strcmp(temp->labelName,str);
        if(res==0) /*we already have this label name*/
        {
            if(temp->entryOrExtern==Extern) /*check if the existed label is an extern*/
            {
                foundError(vars,IBranchLabelIsExternal,str);
                return False;
            }
        }
        temp = temp->next;
    }
    return True;
}

/*this function returns True- if the J label is external ,otherwise False*/
Bool existsLabelExternalJ(labelListPtr *head, char *str,globalVariables *vars)
{
    labelListPtr temp = *head;
    int res;
    while (temp != NULL )
    {
        res= strcmp(temp->labelName,str);
        if(res==0) /*we already have this label name*/
        {
            if(temp->entryOrExtern==Extern) /*check if the existed label is an extern*/
            {
                return True;
            }
        }
        temp = temp->next;
    }
    return False;
}


/*This function checks if an entry label exists in the label table and add 'Entry' to the attribute*/
Bool isLabelEntry(labelListPtr *head, char *after,globalVariables *vars)
{
    strip(after);
    labelListPtr temp = *head;
    int res,flag=0;
    while (temp != NULL)
    {
        res= strcmp(temp->labelName,after);
        if(res==0) /*we already have this label name*/
        {
            temp->entryOrExtern=Entry;
            flag=1;
        }
        temp = temp->next;
    }

    if(flag==0)/*we couldn't find this label*/
    {
        foundError(vars,EntryLabelDontExists,after);
        return False;
    }
    return True;
}

/*update current label node with data*/
void updateLabel(labelListPtr currentLabel,int address,Location DataOrCode,LabelType EntryOrExtern)
{
    currentLabel->address = address;
    currentLabel->codeOrData = DataOrCode;
    currentLabel->entryOrExtern = EntryOrExtern;
}





/*this function updates the data labels with final IC value after the first pass*/
void  updateLabelTableICF(labelListPtr *head,globalVariables *vars)
{
    labelListPtr temp = *head;

    while(temp) {
        if(temp->codeOrData==Data) {
            temp->address+=vars->ICF;
        }
        temp = temp->next;
    }

}


long EntryValueAfterSecondPass(labelListPtr *head, char *str)
{
    labelListPtr temp = *head;
    int res;
    while (temp != NULL)
    {
        res= strcmp(temp->labelName,str);
        if(res==0 && temp->entryOrExtern==Entry) /*we already have this label name*/
        {
            return temp->address;
        }
        temp = temp->next;
    }

    return LABEL_ERROR;
}
