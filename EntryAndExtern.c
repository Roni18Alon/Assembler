/* Name: EntryAndExtern.c
 * Author: Roni Alon & Noa Even
 * Description: Include the function to add and create node of Entry or Extern Labels , and their linked lists
 *
*/



#include "default.h"

/*This function add an external label to the external label list*/
void addExternalToList(externalListPtr *head, externalListPtr externalToAdd) {

    externalListPtr temp = *head;
    if (temp==NULL) {
        *head = externalToAdd;
        return;
    }

    while (temp->next) { /*find the right place to locate the new node*/
        temp = temp->next;
    }
    temp->next = externalToAdd;
    externalToAdd->next=NULL;

}

/*This function create an external label by given params - label name and address (value)*/
void createExternalNode(char *str, globalVariables *vars)
{
    externalListPtr externalLabel = (externalListPtr) calloc(1, sizeof(externalList));
    if(!externalLabel)
    {
        exit(0);
    }

    strcpy(externalLabel->labelName,str);
    externalLabel->value=vars->IC;
    addExternalToList(&(vars->headExternList),externalLabel); /*add to external list*/
}

/*free the external list*/
void freeExternList(externalListPtr *head)
{
    externalListPtr temp = *head;
    while(temp) /*free all except head*/
    {
        temp = (temp)->next;
        free(*head);
        *head=temp;
    }
}

/*This function add an entry label to the entry label list*/
void addEntryToList(entryListPtr *head, entryListPtr entryToAdd)
{
    entryListPtr temp = *head;
    if (temp==NULL) {
        *head = entryToAdd;
        return;
    }

    while (temp->next) { /*find the right place to locate the new node*/
        temp = temp->next;
    }
    temp->next = entryToAdd;
    entryToAdd->next=NULL;

}

/*This function create an entry label by given params - label name and address (value)*/
void createEntryNode(char *str, long address,globalVariables *vars)
{
    entryListPtr entryLabel = (entryListPtr) calloc(1, sizeof(entryList));
    if(!entryLabel)
    {
        exit(0);
    }

    strcpy(entryLabel->labelName,str);
    entryLabel->value=address;
    addEntryToList(&(vars->headEntryList),entryLabel); /*add to external list*/
}
/*free entry list*/
void freeEntryList(entryListPtr *head)
{
    entryListPtr temp = *head;
    while(temp)
    {
        temp = (temp)->next;
        free(*head);
        *head=temp;
    }
}
