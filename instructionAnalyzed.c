/* Name: instructionAnalyzed.c
 * Author: Roni Alon & Noa Even
 * Description: Include supporting functions to analyze the Instruction commands
 *
*/


#include "instructionAnalyzed.h"

void isInstructionFirstPass(char *before, char *after,char *label,globalVariables *vars, Bool hasLabel, labelListPtr currentLabel,WordNodePtr currentWord, int instructionNum) {


    Bool labelBeforeInstruction;
    InstructionWordType commandType;

    currentWord->word.wordType = Instruction;

    if (instructionNum < ADD || instructionNum > STOP) {
        foundError(vars,IllegalInstruction,before);
        return ;
    }

    if((strcmp(after,"")==0||strcmp(after," ")==0||strcmp(after,"\t")==0) && instructionNum!=STOP) /*check if we got an operands*/
    {
        foundError(vars,MissingOperand,after);
        return;
    }

    if (hasLabel == True) {
        labelBeforeInstruction=labelBeforeInstructionCommand(label,vars,currentLabel);
        if(labelBeforeInstruction==False) return; /*and get the next row, else continue */
    }

    strip(before);
    commandType = commandGroup(instructionNum);
    if (commandType == R_WORD) {
        RCommandFirstPass(before,after,commandType,instructionNum,vars,currentWord);
    }
    if (commandType == I_WORD) {
        ICommandFirstPass(before,after,commandType,instructionNum,vars,currentWord);
    }
    if (commandType == J_WORD) {
        JCommandFirstPass(after,instructionNum,vars,currentWord);
    }
}


/*analyzed the second pass Instructions*/
void isInstructionSecondPass(char *str,InstructionWordType commandType,int instructionNum,globalVariables *vars)
{

    if(commandType==R_WORD) return;
    if(commandType==I_WORD){ /*need to analyzed I Branch commands */

        if((instructionNum>=BNE && instructionNum<=BGT)) /*an I - Branch instruction - calculate the sub between*/
        {
            secondPassI(str,vars,commandType);
        }
        /*other I commands*/
    }
    if(commandType==J_WORD)
    {
        if ((instructionNum >= JMP && instructionNum <= CALL)) /*an J - Branch instruction*/
        {
            secondPassJ(str,vars,commandType);
        }
        /*other J commands*/
    }

}
/*This function analyzed R command in the first Pass*/
void RCommandFirstPass(char *before,char *after,InstructionWordType commandType,int instructionNum,globalVariables *vars,WordNodePtr currentWord)
{
    int numOfOperands;
    Bool validRCommand;

    currentWord->word.wordUnion.instruction.wordType = R_WORD;
    numOfOperands = numberOfOperands(commandType, instructionNum);
    strip(after);
    validRCommand = R_commandAnalyzed(after, before, after, instructionNum, numOfOperands, vars, currentWord);
    if (validRCommand == True) {
        /*need to add the word node to the list*/
        createWordNode(currentWord,vars); /*it's a valid R command -create a copy and add to list*/
    }
    /*not valid R Command*/
}


Bool R_commandAnalyzed(char *str,char *before ,char *after, int instructionNum,int numOfOperands,globalVariables *vars, WordNodePtr currentWord)
{
    Bool validOperandLine;
    int funct,opcodeR;

    opcodeR=opcodeInstruction(instructionNum); /*get R command opcode*/
    funct= Rfunct(instructionNum);/*get R command funct*/

    validOperandLine=validROperandLine(str,before,after,numOfOperands,vars,currentWord); /*analyzed the operands */

    if(validOperandLine==True) /*the R command line is valid update the word node and add to word list*/
    {
        currentWord->word.wordUnion.instruction.code.rWord.funct =funct; /*add funct to current word*/
        currentWord->word.wordUnion.instruction.code.rWord.opcode =opcodeR; /*add opcode to current word*/
        currentWord->word.wordUnion.instruction.code.rWord.unused =R_UNUSED; /*unused is 0 to all R */
        currentWord->word.wordUnion.instruction.address = vars->IC;
        return True;
    }
    else {return False; }/*not a valid R command line*/

}



Bool validROperandLine(char *str,char *before ,char *after,int numOfOperands,globalVariables *vars, WordNodePtr currentWord)
{
    int validReg;
    int firstReg,secondReg,thirdReg;
    int firstDelimiter,secondDelimiter,thirdDelimiter;

    /*look for the first comma */
    char operandLine[LINE_LENGTH]={0};
    strcpy(operandLine,str);
    firstDelimiter= split(operandLine,",",before,after);
    if (firstDelimiter==VALID_SPLIT) /*we found he first comma*/
    {
        strip(before);
        if(strlen(before)==0 ||strcmp(before," ")==0||strcmp(before,"\t")==0  ) /*the first operand is without a comma*/
        {
            foundError(vars,CommaBeforeFirstParam,before);
            return False;
        }
    }
    else { /*wwe couldn't find the first comma - R command have 3 or 2 operands */
        foundError(vars,IllegalOperandNoComma,before);
        return False;
    }
    /*if we haven't returned so we fount the comma and its valid one, check if a valid register*/
    validReg=isValidRegister(before,vars);
    if(validReg>=VALID_REGISTER) {
        firstReg = validReg;
        currentWord->word.wordUnion.instruction.code.rWord.rs = firstReg;
    }
    /*look for the second comma*/
    memset(operandLine,0,LINE_LENGTH);
    strcpy(operandLine,after);

    secondDelimiter= split(operandLine,",",before,after);

    strip(before);
    strip(after);
    if(secondDelimiter==VALID_SPLIT) /*we found the second comma */
    {
        if(strlen(before)==0||strcmp(before," ")==0||strcmp(before,"\t")==0 ) /*$3,,7...*/
        {
            foundError(vars,CommaBetweenParams,before);
            return False;
        }

        if(numOfOperands==TWO_REGISTERS)
        {
            if(strlen(after)==0||strcmp(after," ")==0||strcmp(after,"\t")==0 )/*after is an empty string, we just have a comma*/
            {
                foundError(vars,ExtraneousComma,after);
                return False;
            }
            else{ /*after isn't an empty string - check if a valid operand*/
                validReg=isValidRegister(after,vars);
                if(validReg>=VALID_REGISTER) /*we found a valid reg so we have more operands*/
                {
                    foundError(vars,ExtraneousOperand,after);
                    return False;
                }
                else{ /*if its not a valid reg - Extraneous Text*/
                    foundError(vars,ExtraneousText,after);
                    return False;
                }
            }
        }
        if(numOfOperands==THREE_REGISTERS) /*valid situation if we find a second comma*/
        {
            validReg=isValidRegister(before,vars);
            if(validReg>=VALID_REGISTER) {
                secondReg = validReg;
                currentWord->word.wordUnion.instruction.code.rWord.rt = secondReg;
            }
            else{ /*not a valid register*/
                return False; /*error type already been checked*/
            }
        }
    }
    else{ /*couldn't find the second comma */
        if(numOfOperands==THREE_REGISTERS) /*for example $3,$2    */
        {
            foundError(vars,MissingOperand,before);
            return False;
        }
        if(numOfOperands==TWO_REGISTERS) /*valid situation check if before is a valid register*/
        {
            validReg=isValidRegister(before,vars);
            if(validReg>=VALID_REGISTER) {
                secondReg = validReg;
                currentWord->word.wordUnion.instruction.code.rWord.rd = secondReg;
                currentWord->word.wordUnion.instruction.code.rWord.rt = 0;
                return True;
            }
            else{ /*not a valid register*/
                return False; /*error type already been checked*/
            }
        }
    }
    /*look for the third comma*/
    memset(operandLine,0,LINE_LENGTH);
    strcpy(operandLine,after);

    thirdDelimiter= split(operandLine,",",before,after);

    strip(before);
    strip(after);

    if(thirdDelimiter==VALID_SPLIT) /*if we found the third comma*/
    {
        if(strlen(before)==0||strcmp(before," ")==0||strcmp(before,"\t")==0) /*$3,$2,,$4...*/
        {
            foundError(vars,CommaBetweenParams,before);
            return False;
        }

        if(strlen(after)==0||strcmp(after," ")==0||strcmp(after,"\t")==0)/*after is an empty string, we just have a comma*/
        {
            foundError(vars,ExtraneousComma,after);
            return False;
        }
        else{ /*after isn't an empty string - check if a valid operand*/
            validReg=isValidRegister(after,vars);
            if(validReg>=VALID_REGISTER) /*we found a valid reg so we have more operands*/
            {
                foundError(vars,ExtraneousOperand,after);
                return False;
            }
            else{ /*if its not a valid reg - Extraneous Text*/

                foundError(vars,ExtraneousText,after);
                return False;
            }
        }
    }
    else{ /* we couldn't find the third comma, and we are in a 3 operands situation, so check if the third operand is valid register*/

        validReg=isValidRegister(before,vars);
        if(validReg>=VALID_REGISTER) {
            thirdReg = validReg;
            currentWord->word.wordUnion.instruction.code.rWord.rd = thirdReg;
            return True;
        }
        else{ /*not a valid register*/
            return False; /*error type already been checked*/
        }
    }

}
/*this function starts to analysis I commands*/
void ICommandFirstPass(char *before,char *after,InstructionWordType commandType,int instructionNum,globalVariables *vars,WordNodePtr currentWord)
{
    int type;
    Bool validICommand;
    currentWord->word.wordUnion.instruction.wordType = I_WORD;

    type = numberOfOperands(commandType, instructionNum);
    strip(after);
    validICommand = I_commandAnalyzed(after, before, after, instructionNum, type, vars, currentWord); /*analyzed the command */
    if (validICommand == True) {
        /*need to add the word node to the list*/
        createWordNode(currentWord,vars); /*it's a valid I command - create a copy and add to word list*/
    }
    /*not valid I Command*/
}

/*this function returns True is the I command analysis is valid and update I fields*/
Bool I_commandAnalyzed(char *str,char *before ,char *after, int instructionNum,int type,globalVariables *vars, WordNodePtr currentWord)
{
    Bool validOperandLine;
    int opcodeI;

    opcodeI= opcodeInstruction(instructionNum);
    currentWord->word.wordUnion.instruction.code.iWord.opcode =opcodeI; /*set opcode*/

    validOperandLine=validIOperandLine(str,before,after,type,vars,currentWord); /*analyzed the operands */
    if(validOperandLine==True)
    {
        currentWord->word.wordUnion.instruction.address = vars->IC;
        return True;
    }
    else {return False; }/*not a valid I command line*/

}

/*This function returns True if the operand of I command are valid - false otherwise*/
Bool validIOperandLine(char *str, char *before, char *after, int type, globalVariables *vars,  WordNodePtr currentWord)
{
    int validReg, validImmediate;
    int firstReg, secondReg, thirdReg;
    int firstDelimiter, secondDelimiter, thirdDelimiter;

    /*look for the first comma */
    char operandLine[LINE_LENGTH] = {0};

    strcpy(operandLine, str);
    firstDelimiter = split(operandLine, ",", before, after);
    strip(before);
    strip(after);
    if (firstDelimiter == VALID_SPLIT) /*we found a comma check if valid operand*/
    {
        if (strlen(before) == 0 || strcmp(before, " ") == 0 || strcmp(before, "\t") == 0) /*the first operand is without a comma*/
        {
            foundError(vars, CommaBeforeFirstParam, before);
            return False;
        }

        /*all I operators starts with register*/
        strip(before);
        validReg = isValidRegister(before, vars);
        if (validReg >= VALID_REGISTER) {
            firstReg = validReg;
            currentWord->word.wordUnion.instruction.code.iWord.rs = firstReg;
        } else { return False; }/*not a valid register*/
    } else {/*we couldn't find the first comma*/

        foundError(vars, IllegalOperandNoComma, before);
        return False;
    }

    /*look for the second comma */
    memset(operandLine, 0, LINE_LENGTH);
    strcpy(operandLine, after);
    secondDelimiter = split(operandLine, ",", before, after);

    strip(before);
    strip(after);
    if (secondDelimiter == VALID_SPLIT) /*we found the second comma*/
    {
        if (strlen(before) == 0 || strcmp(before," ") == 0 || strcmp(before, "\t") == 0) /*$3,,7...*/
        {
            foundError(vars, CommaBetweenParams, before);
            return False;
        }

        if (type == REG_IM_REG_ARI_LOG || type == REG_IM_REG_LOAD) /*supposed to be an immediate*/
        {
            validImmediate = isValidImmediate(before, vars);
            if (validImmediate == IMMEDIATE_ERROR) {
                return False;
            }
            currentWord->word.wordUnion.instruction.code.iWord.immed = validImmediate;
        } else {
            if (type == REG_REG_LABEL) /*supposed to be a register*/
            {
                validReg = isValidRegister(before, vars);
                if (validReg >= VALID_REGISTER) {
                    secondReg = validReg;
                    currentWord->word.wordUnion.instruction.code.iWord.rt = secondReg;
                } else { /*not a valid register*/
                    return False; /*error type already been checked*/
                }
            } else {
                foundError(vars, InvalidOperand, before);
                return False;
            }
        }
    } else { /*we couldn't find the second comma*/

        foundError(vars, MissingOperand, before);
        return False;
    }

    /*look for the third comma*/
    memset(operandLine, 0, LINE_LENGTH);
    strcpy(operandLine, after);

    thirdDelimiter = split(operandLine, ",", before, after);

    strip(before);
    strip(after);
    if (thirdDelimiter == VALID_SPLIT) /*if we found the third comma*/
    {
        if (strlen(before) == 0 || strcmp(before, " ") == 0 || strcmp(before, "\t") == 0) /*$3,$2,,$4...*/
        {
            foundError(vars, CommaBetweenParams, before);
            return False;
        }

        if (strlen(after) == 0 || strcmp(after, " ") == 0 ||
            strcmp(after, "\t") == 0)/*after is an empty string, we just have a comma $3,12,$6,  */
        {
            foundError(vars, ExtraneousComma, after);
            return False;
        } else { /*after isn't an empty string - check if a valid operand*/
            validReg = isValidRegister(after, vars);
            if (validReg >= VALID_REGISTER) /*we found a valid reg so we have more operands*/
            {
                foundError(vars, ExtraneousOperand, after);
                return False;
            } else { /*check if a valid immediate*/
                validImmediate = isValidImmediate(before, vars);
                if (validImmediate != IMMEDIATE_ERROR) { /*valid immediate but its extraneous*/
                    foundError(vars, ExtraneousImmediate, before);
                    return False;
                } else {
                    /*if its not a valid reg or an immediate - Extraneous Text*/
                    foundError(vars, ExtraneousText, before);
                    return False;
                }
            }
        }
    } else { /* we couldn't find the third comma, check if an Label or register or none*/
        strip(before);

        if (type == REG_IM_REG_LOAD || type == REG_IM_REG_ARI_LOG) {
            validReg = isValidRegister(before, vars);
            if (validReg >= VALID_REGISTER) {
                thirdReg = validReg;
                currentWord->word.wordUnion.instruction.code.iWord.rt = thirdReg;
                return True;
            }
                /*not a valid register*/
            else { return False; } /*error type already been checked*/
        } else {
            /*type==REG_REG_LABEL - in the first Pass we put the address as the current IC in immediate, will be handle in second Pass*/
            currentWord->word.wordUnion.instruction.code.iWord.immed = vars->IC;
            return True;
        }
    }
}

/*this function analysis J commands in the first pass*/
void JCommandFirstPass(char *after,int instructionNum,globalVariables *vars,WordNodePtr currentWord)
{
    Bool validICommand;
    currentWord->word.wordType=Instruction;
    currentWord->word.wordUnion.instruction.wordType = J_WORD;
    strip(after);
    validICommand = J_commandAnalyzed(after, instructionNum, vars, currentWord);
    if (validICommand == True) {
        /*need to add the word node to the list*/
        createWordNode(currentWord,vars); /*it's a valid J command - create a copy and add to word list*/
    }
    /*not valid J Command*/
}


Bool J_commandAnalyzed(char *str, int instructionNum,globalVariables *vars, WordNodePtr currentWord)
{
    Bool validOperandLine;
    int opcode;
    opcode=opcodeInstruction(instructionNum);
    currentWord->word.wordUnion.instruction.code.jWord.opcode =opcode;

    validOperandLine= validJOperandLine(str,instructionNum,vars,currentWord);

    if(validOperandLine==True)
    {
        currentWord->word.wordUnion.instruction.address = vars->IC;
        return True;
    }
    else {return False; }/*not a valid J command line*/
}


int opcodeInstruction(int instructionNum)
{
    if(ADD<=instructionNum && instructionNum<=NOR) return OP_R_ARI_LOG; /*OPCODE=0*/
    if(MOVE<=instructionNum && instructionNum<=MVLO)return OP_R_COPY;  /*OPCODE=1*/
    if(instructionNum==ADDI)  return OP_ADDI; /*OPCODE=10*/
    if(instructionNum==SUBI)  return OP_SUBI; /*OPCODE=11*/
    if(instructionNum==ANDI)  return OP_ANDI; /*OPCODE=12*/
    if(instructionNum==ORI)  return OP_ORI;  /*OPCODE=13*/
    if(instructionNum==NORI)  return OP_NORI; /*OPCODE=14*/
    if(instructionNum==BNE)  return OP_BNE; /*OPCODE=15*/
    if(instructionNum==BEQ)  return OP_BEQ; /*OPCODE=16*/
    if(instructionNum==BLT)  return OP_BLT; /*OPCODE=17*/
    if(instructionNum==BGT)  return OP_BGT; /*OPCODE=18*/
    if(instructionNum==LB)  return OP_LB; /*OPCODE=19*/
    if(instructionNum==SB)  return OP_SB; /*OPCODE=20*/
    if(instructionNum==LW)  return OP_LW; /*OPCODE=21*/
    if(instructionNum==SW)  return OP_SW; /*OPCODE=22*/
    if(instructionNum==LH)  return OP_LH; /*OPCODE=23*/
    if(instructionNum==SH)  return OP_SH; /*OPCODE=24*/
    if(instructionNum==JMP)  return OP_JMP; /*OPCODE=30*/
    if(instructionNum==LA)  return OP_LA; /*OPCODE=31*/
    if(instructionNum==CALL) return OP_CALL; /*OPCODE=32*/
    if(instructionNum==STOP)  return OP_STOP;  /*OPCODE=63*/
    else return INSTRUCTION_ERROR;
}

/*this function returns True if the operands of J command is valid - false otherwise*/
Bool validJOperandLine(char *str, int instructionNum, globalVariables *vars, WordNodePtr currentWord) {

    int isReg;
    Bool JwithReg, JwithLabel;

    strip(str);
    if (instructionNum == JMP) /* jmp cen receive a register or label*/
    {
        isReg = validJRegister(str, vars); /*check if a register and returns*/
        if (isReg >= VALID_REGISTER) { /*a valid reg number is 0-31*/
            JwithReg = regJCommand(str + 1, vars, currentWord);
            if (JwithReg == False)return False;
            /*than True it's a valid register*/
            return True;
        } else { /*not a register - check if a valid label by syntax. in the second pass we will check in the Label Table*/

            JwithLabel = labelJCommand(str, vars, currentWord);
            if (JwithLabel == False) /* not a register and not a label by syntax - operand error*/
            {
                foundError(vars, InvalidOperand, str);
                return False;
            } else { return True; /*it's a valid label by syntax*/}
        }
    } else {
        if (instructionNum == LA || instructionNum == CALL) {
            JwithLabel = labelJCommand(str, vars, currentWord);
            if (JwithLabel == False) /* not a register and not a label by syntax - operand error*/
            {
                return False;
            }
        } else {
            if (instructionNum == STOP) { /*stop doesn't get any operands*/
                if (strcmp(str, "") != 0) /*we found text after stop command*/
                {
                    foundError(vars, InvalidTextAfterStop, str);
                    return False;
                }
                currentWord->word.wordUnion.instruction.code.jWord.reg = J_WITH_LABEL;
                currentWord->word.wordUnion.instruction.code.jWord.address = STOP_ADDRESS;
                return True;
            }
        }
    }
    return True;
}

/*This function returns True im the J command -jmp receive e valid register.False - otherwise */
Bool regJCommand(char *str,globalVariables *vars, WordNodePtr currentWord)
{
    int regNum;
    regNum= isValidRegisterNum(str,vars);
    if(regNum<VALID_REGISTER)/* not valid reg num */
        return False;
    currentWord->word.wordUnion.instruction.code.jWord.reg= J_WITH_REG; /*if we have register - enter 1*/
    currentWord->word.wordUnion.instruction.code.jWord.address =regNum;
    return True;
}

/*This function return True if the label J command gets as operand is a valid label- in the first pass- false otherwise*/
Bool labelJCommand(char *str,globalVariables *vars, WordNodePtr currentWord)
{
    int isLabel;
    isLabel=isLegalLabel(str,vars);
    if(isLabel==LABEL_ERROR) /*not a valid label*/
        return False;
    /*than a valid label - by syntax. in the second pass we will update the address. */
    currentWord->word.wordUnion.instruction.code.jWord.reg= J_WITH_LABEL; /*if we have label - enter 0*/
    return True;
}


void secondPassJ(char *str,globalVariables *vars, InstructionWordType commandType)
{
    int validRegister;
    long labelAddress;
    Bool isExtern;
    /*all J instructions (beside stop) have one operand*/
    strip(str);

    validRegister= validJRegister(str,vars); /*jmp can get a register*/
    if (validRegister==REGISTER_ERROR) /*not a register so it's a label*/
    {
        /*we need to find the label in label list and update the address*/
        labelAddress= findLabel(&(vars->headLabelTable),str,vars,commandType);
        if (labelAddress==LABEL_ERROR) /*couldn't find the label*/
            return;
        isExtern= existsLabelExternalJ(&(vars->headLabelTable),str,vars); /*check if the operand label is external or not*/
        addLabelAddress(&(vars->headWordList),vars,labelAddress,commandType,isExtern);
        if (isExtern==True) /*if it is a J command and the label is extern add to extern list*/
        {
            createExternalNode(str,vars);
        }
    }


}


/*this function analyzed I commands in the second pass- for Branch command complete the address*/
void secondPassI(char *str,globalVariables *vars, InstructionWordType commandType) {
    int firstSplit, secondSplit;
    long currentLabelAddress;
    Bool isExternal;
    /*in I-Branch the label is the third operand*/

    char before[LINE_LENGTH] = {0};
    char after[LINE_LENGTH] = {0};
    char operandLine[LINE_LENGTH] = {0};
    strip(str);

    firstSplit = split(str, ",", before, after);
    if (firstSplit == INVALID_SPLIT) {
        return;
    }
    memset(operandLine,0,LINE_LENGTH);
    strcpy(operandLine,after);

    secondSplit = split(operandLine, ",", before, after);
    if (secondSplit == INVALID_SPLIT) /*after second split the label will be in after string*/
    {
        return;
    }
    /*after second split the label will be in after string*/
    strip(after);
    /*look for branch label in label list*/
    currentLabelAddress = findLabel(&(vars->headLabelTable), after, vars, commandType);
    if (currentLabelAddress == LABEL_ERROR) /*couldn't find the label*/
        return ;
    isExternal = existsLabelExternalIBranch(&(vars->headLabelTable), after, vars);
    if (isExternal == False) /*the I Branch label is external - error*/
        return;
    addLabelAddress(&(vars->headWordList),vars , currentLabelAddress, commandType,isExternal);

}



/*This function handles cases where there is a label before instruction command. check if the label is already in the label list and if not update the label list*/
Bool labelBeforeInstructionCommand(char *labelName, globalVariables *vars, labelListPtr currentLabel)
{
    int ValidLabelName;
    ValidLabelName = labelNameCompare(&(vars->headLabelTable),labelName,vars); /*check if the label name wasn't shown in the table already*/
    if (ValidLabelName == VALID_LABEL) { /* a label isn't in the table*/
        updateLabel(currentLabel,vars->IC,Code,NoEntryExtern); /*update the current label node*/
        createLabelNode(currentLabel,vars); /*create copy of label and add to label list*/
        return True;
    }

    else{ return False; } /*we found the label in the label table*/
}

/*by given instruction number and command type returns the num of expected operands*/
int numberOfOperands(InstructionWordType command,int instructionNum) {
    int numOfOperands;
    if (command == R_WORD) {
        if (ADD <= instructionNum && instructionNum <= NOR)
            numOfOperands=THREE_REGISTERS;
        if (MOVE <= instructionNum && instructionNum <= MVLO)
            numOfOperands=TWO_REGISTERS;
    } else {
        if (command == I_WORD) {
            /*all I commands gets 3 operand so we will define by type*/
            if (ADDI <= instructionNum && instructionNum <= NORI)
                numOfOperands=REG_IM_REG_ARI_LOG; /*arithmetic and logic - will be 4*/
            if (BNE <= instructionNum && instructionNum <= BGT)
                numOfOperands=REG_REG_LABEL;
            if (LB <= instructionNum && instructionNum <= SH)
                numOfOperands=REG_IM_REG_LOAD; /*load and store in the memory - will be 6*/
        } else { /*command==J_WORD */
            if (instructionNum == JMP) /*JMP*/
                numOfOperands=REG_OR_LABEL;
            if (instructionNum == LA || instructionNum == CALL)
                numOfOperands=ONE_LABEL;
            if (instructionNum == STOP)
                numOfOperands=NONE;
        }
    }
    return numOfOperands;
}

/*This function returns the number of Instruction command by given string*/
int instructionValidName(char *command) {
    if (strcmp(command, "add") == 0) return ADD;
    if (strcmp(command, "sub") == 0) return SUB;
    if (strcmp(command, "and") == 0) return AND;
    if (strcmp(command, "or") == 0) return OR;
    if (strcmp(command, "nor") == 0) return NOR;
    if (strcmp(command, "move") == 0) return MOVE;
    if (strcmp(command, "mvhi") == 0) return MVHI;
    if (strcmp(command, "mvlo") == 0) return MVLO;
    if (strcmp(command, "addi") == 0) return ADDI;
    if (strcmp(command, "subi") == 0) return SUBI;
    if (strcmp(command, "andi") == 0) return ANDI;
    if (strcmp(command, "ori") == 0) return ORI;
    if (strcmp(command, "nori") == 0) return NORI;
    if (strcmp(command, "bne") == 0) return BNE;
    if (strcmp(command, "beq") == 0) return BEQ;
    if (strcmp(command, "blt") == 0) return BLT;
    if (strcmp(command, "bgt") == 0) return BGT;
    if (strcmp(command, "lb") == 0) return LB;
    if (strcmp(command, "sb") == 0) return SB;
    if (strcmp(command, "lw") == 0) return LW;
    if (strcmp(command, "sw") == 0) return SW;
    if (strcmp(command, "lh") == 0) return LH;
    if (strcmp(command, "sh") == 0) return SH;
    if (strcmp(command, "jmp") == 0) return JMP;
    if (strcmp(command, "la") == 0) return LA;
    if (strcmp(command, "call") == 0) return CALL;
    if (strcmp(command, "stop") == 0) return STOP;
    else return INSTRUCTION_ERROR;

}

/*returns the funct of a given R command*/
int Rfunct(int instructionNum)
{
    if(instructionNum==ADD) return ADD_FUNCT; /*command add funct 1*/
    if(instructionNum==SUB)return SUB_FUNCT;/*command sub funct 2*/
    if(instructionNum==AND) return AND_FUNCT; /*command and funct 3*/
    if(instructionNum==OR)return OR_FUNCT; /*command or funct 4*/
    if(instructionNum==NOR) return NOR_FUNCT; /*command nor funct 5*/
    if(instructionNum==MOVE)return MOVE_FUNCT; /*command move funct 1*/
    if(instructionNum==MVHI) return MVHI_FUNCT;/*command mvhi funct 2*/
    if(instructionNum==MVLO) return MVLO_FUNCT; /*command mvlo funct 3*/
    else return  INSTRUCTION_ERROR;

}
/*by given instruction number returns the instruction word type*/
InstructionWordType commandGroup (int instructionNum)
{
    if (instructionNum >= ADD && instructionNum <= MVLO) return R_WORD;
    else if (instructionNum >= ADDI && instructionNum <= SH)  return I_WORD;
    else /*if(instructionNum>=JMP &&instructionNum<=STOP )*/ return J_WORD;

}