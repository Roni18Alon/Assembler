//
// Created by ronia on 27/07/2021.
//

#include "default.h"


void addExternalToList(externalListPtr *head, externalListPtr externalToAdd) {

    externalListPtr temp = *head;
    if (temp == NULL) {
        *head = externalToAdd;
        return;
    }

    while (temp->next) { /*find the right place to locate the new node*/
        temp = temp->next;
    }
    temp->next = externalToAdd;
    externalToAdd->next=NULL;

}


void createExternalNode(char *str, globalVariables *vars,externalListPtr *head)
{
    externalListPtr externalLabel = (externalListPtr) calloc(1, sizeof(externalList));
    if(!externalLabel)
    {
        exit(0);
    }

    strcpy(externalLabel->labelName,str);
    externalLabel->value=vars->IC;
    addExternalToList(head,externalLabel); /*add to external list*/
}



void addEntryToList(entryListPtr *head, entryListPtr entryToAdd)
{
    entryListPtr temp = *head;
    if (temp == NULL) {
        *head = entryToAdd;
        return;
    }

    while (temp->next) { /*find the right place to locate the new node*/
        temp = temp->next;
    }
    temp->next = entryToAdd;
    entryToAdd->next=NULL;

}

void createEntryNode(char *str, long address,entryListPtr *head)
{
    entryListPtr entryLabel = (entryListPtr) calloc(1, sizeof(entryList));
    if(!entryLabel)
    {
        exit(0);
    }

    strcpy(entryLabel->labelName,str);
    entryLabel->value=address;
    addEntryToList(head,entryLabel); /*add to external list*/
}