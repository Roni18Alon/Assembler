/* Name: inputAnalyzed.c
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze the given input
 *
*/

#include "inputAnalyzed.h"


/*strip the given string from the white chars in the beginning and the end*/
void strip(char *str) {
    char newString[LINE_LENGTH] = {0};
    int left = 0;
    int right = strlen(str) - 1;

    while (isspace(str[left]) && left < right) {
        left++;
    }
    while (isspace(str[right]) && left < right) {
        right--;
    }
    strncpy(newString, str + left, right - left + 1);
    memset(str, 0, LINE_LENGTH);
    strcpy(str, newString);
}

int split(char *str, char *delimiter, char *before, char *after) {
    int i, j;
    memset(after, 0, LINE_LENGTH);
    memset(before, 0, LINE_LENGTH);
    for (i = 0; i < strlen(str); i++) {
        for (j = 0; j < strlen(delimiter); j++) {
            if (delimiter[j] == str[i]) {
                strncpy(before, str, i);
                strcpy(after, str + i + 1);
                return VALID_SPLIT;
            }
        }
    }
    strcpy(before, str);
    return INVALID_SPLIT;
}

/*This function checks if a label is valid by syntax */
int isLegalLabel(char *str, globalVariables *vars) {

    int length = strlen(str);
    Bool isKeepWord;
    if (!isspace(str[length-1]))/*a legal label*/
    {
        strip(str);
        if (length < LABEL_LENGTH) {
            int first = (int) str[0];
            if (isalpha(first)) /*a legal label starts with an alphabet */
            {
                int i, isAlphaNum;
                for (i = 0; i < strlen(str); i++) {
                    isAlphaNum = isalnum((int) str[i]); /*check if it's an alphabet or numeric */
                    if (isAlphaNum == 0)    /*neither an alphabet nor a digit.*/
                    {
                        foundError(vars, IllegalCharInLabel, str);
                        return LABEL_ERROR;
                    }
                }

            } else {
                foundError(vars, firstCharInLabelNotAlphabet, str);
                return LABEL_ERROR;
            } /*not a legal label first char*/

            isKeepWord=labelIsKnown(str);
            if(isKeepWord==False)
            {
                foundError(vars, LabelIsKnownWord, str);
                return LABEL_ERROR;/*a known word*/
            }
            return VALID_LABEL;
        }
        else {
            foundError(vars, TooLongLabel, str);
            return LABEL_ERROR;/*more than 31 char*/
        }
    }
    foundError(vars,InvalidWhiteChar,str);/*we found a white char before :*/
    return LABEL_ERROR;
}

/*This function checks if a given line is empty - only white chars or a comment line - starts with ;*/
int isEmptyOrCommentLine(char *str) {
    if (str[0] == ';'||isspace(str[0])!=0 )return EMPTY_OR_COMMENT;
    if(strlen(str)==0) return EMPTY_OR_COMMENT;
    else return NOT_EMPTY_OR_COMMENT;
}
/*check if the directive number is valid by syntax*/
Bool ValidNumberDirective(char *str,globalVariables *vars)
{
    int sign,i;
    long number;
    char num[LINE_LENGTH]={0};
    char *ptr;

    sign=POSITIVE_NUM;
    if (strcmp(str,"0")==0) /*strtol don't recognize 0*/
    {
        return True;
    }

    number=strtol(str,&ptr,10);
    if (number==0) /*not an integer*/
    {
        foundError(vars,DirectiveOperandNotAnInt,str);
        return False;/*error- not an integer*/
    }

    if(number<0)sign = NEGATIVE_NUM;/*negative num*/
    if(number>=0)sign = POSITIVE_NUM;/*negative num*/

    if((isdigit((int)(str[0]))==0)) /*doesnt start with a digit*/
    {
        if (str[0] != '+' && str[0] != '-') /*operand start with a sign but not with + or - , it's an error*/
        {
            foundError(vars, DirectiveOperandWrongSign, str);
            return False;/*error- not an integer*/
        }
    }

    for (i = 1; i < strlen(str); i++) {
        int Digit = (int) (str[i]);
        if (isdigit(Digit) == 0) {
            foundError(vars, DirectiveOperandNotAnInt, str);
            return False;/*error- not an integer*/
        }
    }

    strcpy(num,str);
    if (strcmp(str,"+0")==0 ||strcmp(str,"-0")==0) /* -0 and +0 it's not valid*/
    {
        foundError(vars, InvalidOperand, str);
        return False;/*error- not an integer*/
    }

    if(sign==POSITIVE_NUM)
    {
        if(number==INT_MAX && strcmp(num,"2147483647")!=0) /*strtol returns INT_MAX= 2147483647 but the num string is not equal so we ot a bigger number from INT_MAX*/
        {
            foundError(vars,ParamNotInBitRange,num);
            return False;/*error- not an integer*/
        }
    }
    if(sign==NEGATIVE_NUM)
    {
        if(number==INT_MIN && strcmp(str,"-2147483648")!=0) /*strtol returns INT_MIN= -2147483648 but the num string is not equal so we ot a smaller number from INT_MIN */
        {
            foundError(vars,ParamNotInBitRange,str);
            return False;/*error- not an integer*/
        }
    }
    return True;
}

/*this function returns the directive number - we will reach to this function only in the number is valid by syntax*/
long directiveNumber(char *str)
{
    long number;
    char *ptr;

    if (strcmp(str,"0")==0) /*strtol don't recognize 0*/
    {
        return 0;
    }
    number=strtol(str,&ptr,10);
    return number;
}

/*by given integer and directive return if the num is in the bit range */
long validNumByDirective(int directive,long num,char *str,globalVariables *vars)
{
    int minValue,maxValue;

    if(directive==DIRECTIVE_BYTE)
    {
        minValue=D_BYTE_MIN_VALUE; /*-128*/
        maxValue=D_BYTE_MAX_VALUE;  /*127*/
    }
    if(directive==DIRECTIVE_HALF_WORD)
    {
        minValue=D_HALF_MIN_VALUE;  /*-32768*/
        maxValue=D_HALF_MAX_VALUE;  /*32767*/
    }
    if(directive==DIRECTIVE_WORD)
    {
        minValue=INT_MIN;  /*-2147483648*/
        maxValue=INT_MAX;  /* 2147483647*/
    }
    if(minValue<=num && num<=maxValue) /* range of nums [-2^(bitnum-1)....(2^bitnum)-1] */
    {
        return VALID_BIT_RANGE;
    }
    else {
        foundError(vars,ParamNotInBitRange,str);
        return INVALID_BIT_RANGE;
    }
}

/*to check if a given string is valid, between "" and only graphic characters*/
int isValidString(char *str,globalVariables *vars)
{
    int first=(int)str[0];
    int last=(int)str[strlen(str)-1];
    int i,isPrint;
    if(first!='"'||last!='"' ) {

        foundError(vars,StringNotValid,str);
        return STRING_ERROR; /*a valid string start&end with ""*/
    }

    for(i=0;i< strlen(str);i++)
    {
        isPrint=(isprint(str[i]));
        if(isPrint==0) {
            foundError(vars,StringNotValid,str);
            return STRING_ERROR; /*a valid string all the chars are graphic characters*/
        }
    }
    return VALID_STRING;
}


/*a valid register stars with $ and between 0-31*/
int isValidRegister(char *str,globalVariables *vars)
{
    char currentReg[REG_MAX_LENGTH]={0};
    int validNum;
    strip(str);
    if(strlen(str)>(REG_MAX_LENGTH-1)) {
        foundError(vars,RegisterLength,str);
        return REGISTER_ERROR;
    }

    if(str[0]!='$')/*register must begins with $ */
    {
        foundError(vars,RegisterSign,str);
        return REGISTER_ERROR;
    }

    strcpy(currentReg,str+1); /*copy to a new string without $  */
    if(currentReg[0]=='-') /*register must be positive number */
    {
        foundError(vars,RegisterNegative,str);
        return REGISTER_ERROR;
    }

    validNum= isValidRegisterNum(currentReg,vars); /*gets the string without $*/
    if(validNum>=VALID_REGISTER)
        return validNum;

    return REGISTER_ERROR;
}

/*a valid register num is an integer between 0-31*/
int isValidRegisterNum(char *str,globalVariables *vars)
{
    int i,num;
    char reg[REG_MAX_LENGTH]={0};
    strcpy(reg,str); /*copy to a new string */
    for(i=0;i< strlen(reg);i++) /*check if an integer*/
    {
        if(isdigit(reg[i])==0)
        {
            foundError(vars,RegisterNotAnInt,reg);
            return REGISTER_ERROR;
        }
    }
    if(strcmp(reg,"0")!=0)
    {
        num=atoi(reg); /*atoi returns 0 if its not an int*/
    }
    else{
        num=0;
    }
    if (num<MIN_REG || num>MAX_REG)
    {
        foundError(vars,RegisterNotInRange,reg);
        return REGISTER_ERROR;
    }
    return num;
}

/*this function checks if a given immediate */
int isValidImmediate(char *str,globalVariables *vars) {

    char positive[LINE_LENGTH]={0};
    char negative[LINE_LENGTH]={0};

    int i;
    int validNum = 0;
    int minRange= IMM_MIN_VALUE;
    int maxRange= IMM_MAX_VALUE;

    int sign = POSITIVE_NUM;
    if (str[0] == '-') sign = NEGATIVE_NUM;   /*immediate can be a negative number*/

    if (str[0] == '-' || isdigit(str[0]) != 0) {  /*if negative start with - or if positive starts with digit*/
        for (i = 1; i < strlen(str); i++) /*check if an integer*/
        {
            if (isdigit(str[i]) == 0) { /*check if all chars are digits*/
                foundError(vars,ImmediateNotAnInt,str);
                return IMMEDIATE_ERROR;
            }
        }
    }
    else {
        foundError(vars,ImmediateNotValid,str);
        return IMMEDIATE_ERROR;
    }

    /*check if the num is in the correct range 16 bits with negative [-2^15...(2^15)-1]*/

    if (str[0] == '-') {
        sign = NEGATIVE_NUM;   /*immediate can be a negative number*/
        strcpy(negative, str + 1);
        if (strcmp(negative, "0") != 0) {
            validNum = atoi(negative); /*atoi returns 0 if its not an int ,and we cant have a negative zero*/
        }
        validNum=sign*validNum;
        if (validNum < minRange || validNum > maxRange) {
            foundError(vars,ImmediateNotInRange,str);
            return IMMEDIATE_ERROR;
        }
        return validNum;
    }
    else{ /*if its not a - it a digit -already checked*/
        strcpy(positive, str);
        if (strcmp(positive, "0") != 0) {
            validNum = atoi(positive); /*atoi returns 0 if its not an int*/
        } else {
            validNum = 0;
        }
        if (validNum < minRange || validNum > maxRange) {
            foundError(vars,ImmediateNotInRange,str);
            return IMMEDIATE_ERROR;
        }
        return validNum;
    }
}
/*this function returns True if we found a label - by :*/
Bool foundLabel(char *lineCpy,char *before,char *after) {

    int labelDelimiter;
    labelDelimiter = split(lineCpy, ":", before, after);
    if (labelDelimiter == VALID_SPLIT)/*we found a ':' - Label*/
    {
        return True;
    }
    else return False; /*we couldn't find ":"*/
}
/*This Function returns the word type -Instruction,Directive, or None by given string*/
WordType directiveOrInstruction(char *str,char *before,char *after,globalVariables *vars)
{
    WordType word;
    int lineAnalyzed, instructionNum;
    Bool isDirective;
    strip(after);
    instructionNum = instructionValidName(after);
    lineAnalyzed = split(str, " \t", before, after);
    if (lineAnalyzed == VALID_SPLIT) { /*we found a tab*/
        strip(before);
        strip(after);
        isDirective = isDirectiveCommand(before); /*if we find a '.' it's a directive*/
        if (isDirective == True) { /*check if a valid directive*/
                word = Directive;
        } else { /*check if instruction or not*/
            instructionNum = instructionValidName(before);
            if (instructionNum != INSTRUCTION_ERROR) /*we found a valid instruction*/
            {
                word = Instruction;
            } else { /*if it's not a directive and not an instruction - error*/
                foundError(vars, notDirectiveOrInstruction, before);
                word = None;
            }
        }
    } else { /* check if a valid Instruction / directive name - but we couldn't find \t or space*/
        if (instructionNum >= ADD && instructionNum <= STOP) {
            word = Instruction;
        } else {
            isDirective = isDirectiveCommand(before); /*if we find a '.' it's a directive*/
            if (isDirective == True) {
                word = Directive; /*it's a valid directive*/
            }
            else {
                foundError(vars, notDirectiveOrInstruction, before);
                word = None;
            }
        }
    }
    return word;

}


/*This function check if the operand of J is a valid Register*/
int validJRegister(char *str,globalVariables *vars)
{
    char currentReg[REG_MAX_LENGTH]={0};
    strip(str);
    if(strlen(str)>REG_MAX_LENGTH) {/*check while debug if in length \0 include*/
        return REGISTER_ERROR;
    }

    if(str[0]!='$')/*register must begging with $ */
    {
        return REGISTER_ERROR;
    }

    strcpy(currentReg,str+1);/*register must be positive number */
    if(currentReg[0]=='-')
    {
        return REGISTER_ERROR;
    }

    return VALID_REGISTER;
}


/*This function reset the strings after every iteration of line from input file*/
void resetStrings(char *line,char *lineCpy,char *before , char *after, char *lineCpyAfterLabel,char *label)
{
    memset(line, 0, LINE_LENGTH);
    memset(lineCpy, 0, LINE_LENGTH);
    memset(before, 0, LINE_LENGTH);
    memset(after, 0, LINE_LENGTH);
    memset(lineCpyAfterLabel, 0, LINE_LENGTH);
    memset(label, 0, LABEL_LENGTH);
}

/*this function check if a valid label by syntax is not a keep word in our language (valid Instruction/Directive)*/
Bool labelIsKnown(char *label)
{
    int isInstruction=instructionValidName(label);
    if (isInstruction!=INSTRUCTION_ERROR) return False;/*it's a valid instruction Name - return False*/
    else{ /*check maybe a keep directive word*/
        if(strcmp(label,"asciz")==0) return False;
        if(strcmp(label,"db")==0) return False;
        if(strcmp(label,"dh")==0) return False;
        if(strcmp(label,"dw")==0) return False;
        if(strcmp(label,"entry")==0) return False;
        if(strcmp(label,"extern")==0) return False;
    }
    return True;
}