/* Name: printErrors.c
 * Author: Roni Alon & Noa Even
 * Description: Print the errors we found in the FIRST PASS OR SECOND PASS
 *
*/

#include "printErrors.h"



void foundError(globalVariables *vars,errorType type,char *str)
{
    memset(vars->error,0,LINE_LENGTH);
    vars->type = type;
    strcpy(vars->error,str);
    vars->errorFound = True;
}




void printErrors(globalVariables *vars)
{
    setbuf(stdout, 0);
    if(vars->type==LineTooLong)
    {
        printf("\n%s:Line %d:Error - line is too long, line has 80 characters maximum \n", vars->filename, vars->currentLine);
    }

    if(vars->type==IllegalCharInLabel)
    {
        printf("\n%s:Line %d:Error - %s Illegal Label found a char that is neither an alphabet nor a digit\n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==TooLongLabel)
    {
        printf("\n%s:Line %d:Error - %s Illegal Label more than 31 characters\n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==firstCharInLabelNotAlphabet)
    {
        printf("\n%s:Line %d:Error - %s Illegal Label first char not an alphabet\n", vars->filename,vars->currentLine,vars->error);
    }

    if(vars->type==InvalidWhiteChar)
    {
        printf("\n%s:Line %d:Error '%s'  - we found before : white char \n", vars->filename,vars->currentLine,vars->error);
    }

    if(vars->type==CommaBeforeFirstParam)
    {
        printf("\n%s:Line %d:Illegal comma before the first param\n", vars->filename,vars->currentLine);
    }
    if(vars->type==CommaBetweenParams)
    {
        printf("\n%s:Line %d:Error - Extraneous comma between param\n", vars->filename, vars->currentLine);
    }
    if(vars->type==ParamNotInBitRange)
    {
        printf("\n%s:Line %d:Given param '%s' is not in bit range\n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==notDirectiveOrInstruction)
    {
        printf("\n%s:Line %d:Error- '%s' isn't a valid Instruction or Directive\n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==labelExistsInTable)
    {
        printf("\n%s:Line %d: Error - Label '%s' is already exists in Label table\n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==IllegalInstruction)
    {
        printf("\n%s:Line %d: Instruction name %s' is illegal \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==IllegalOperandNoComma)
    {
        printf("\n%s:Line %d:Illegal operand no comma\n", vars->filename,vars->currentLine);
    }

    if(vars->type==RegisterLength)
    {
        printf("\n%s:Line %d: Register '%s' is to0 long\n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==RegisterSign)
    {
        printf("\n%s:Line %d:Error -'%s' Register must start with $  \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==RegisterNegative)
    {
        printf("\n%s:Line %d: Register couldn't be negative '%s' \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==RegisterNotAnInt)
    {
        printf("\n%s:Line %d: Register must be an integer '%s'  \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==RegisterNotInRange)
    {
        printf("\n%s:Line %d:Error '%s' Register must be a number between 0 to 31 \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==ExtraneousComma)
    {
        printf("\n%s:Line %d:Extraneous Comma\n", vars->filename,vars->currentLine);
    }
    if(vars->type==ExtraneousText)
    {
        printf("\n%s:Line %d:Error -'%s' is Extraneous Text \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==ExtraneousOperand)
    {
        printf("\n%s:Line %d:Error -'%s' is Extraneous operand  \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==MissingOperand)
    {
        printf("\n%s:Line %d:Missing Operand\n", vars->filename,vars->currentLine);
    }
    if(vars->type==ImmediateNotAnInt)
    {
        printf("\n%s:Line %d:Error - %s Immediate must be an integer \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==ImmediateNotValid)
    {
        printf("\n%s:Line %d:Error - %s it is not a valid Immediate \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==ImmediateNotInRange)
    {
        printf("\n%s:Line %d:Error - %s - Immediate must be a number in 16 bits in two's complement range \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==InvalidOperand)
   {
        printf("\n%s:Line %d:Error - %s Invalid Operand\n", vars->filename,vars->currentLine,vars->error );
   }
    if(vars->type==ExtraneousImmediate)
    {
        printf("\n%s:Line %d:Error - '%s' is an Extraneous Immediate \n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==DirectiveOperandNotAnInt)
    {
        printf("\n%s:Line %d: '%s' is not an integer\n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==LabelIsKnownWord)
    {
        printf("\n%s:Line %d:Error '%s' is a known word, can't be a label\n", vars->filename,vars->currentLine,vars->error);
    }

    if(vars->type==StringNotValid)
    {
        printf("\n%s:Line %d:Error- %s Given asciz is not a valid string\n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==LabelExistsWithoutExternal)
    {
        printf("\n%s:Line %d: Error- Label '%s' exists in label list but without External attribute \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==LabelExistsInTable)
    {
        printf("\n%s:Line %d: Error '%s' Label already exists in label list \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==InvalidTextAfterStop)
    {
        printf("\n%s:Line %d: Extraneous text , stop command doesn't get any operands\n", vars->filename,vars->currentLine);
    }
    if(vars->type==EntryLabelDontExists)
    {
        printf("\n%s:Line %d: Error- Entry Label '%s' don't exists in Label Table \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==EntryAndExternalTogether)
    {
        printf("\n%s:Line %d: Error- Label '%s' can't be Entry and External label together \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==JCommandLabelDontExists)
    {
        printf("\n%s:Line %d: Error- Couldn't find the requested operand label - '%s' in label list \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==IBranchLabelIsExternal)
    {
        printf("\n%s:Line %d: Error- I-Branch operand label '%s' can't be an External label \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==IBranchLabelDontExists)
    {
        printf("\n%s:Line %d: Error- Couldn't find the requested Branch label - '%s' in label list \n", vars->filename,vars->currentLine,vars->error);
    }

    if(vars->type==InvalidDirective)
    {
        printf("\n%s:Line %d:Error- %s is Illegal Directive name\n", vars->filename, vars->currentLine,vars->error);
    }
    if(vars->type==DirectiveOperandWrongSign)
    {
        printf("\n%s:Line %d: Given Operand %s start with invalid sign  \n", vars->filename,vars->currentLine,vars->error);
    }
    if(vars->type==MaxMemory)
    {
        printf("\n%s:Line %d:We reached the maximum capacity of memory \n", vars->filename,vars->currentLine);
    }
}