/* Name: defalut.h
 * Author: Roni Alon & Noa Even
 * Description: Include the definition of structs ,data structures , enum and define macros for the use of the rest project
*/


#ifndef DEFAULT_H
#define DEFAULT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LINE_LENGTH 82
#define LAST_CHAR_IN_LINE 80
#define FILE_NAME_LENGTH 30
#define LABEL_LENGTH 32
#define AS_EXTENSION_LENGTH 3
#define EMPTY_OR_COMMENT 1
#define NOT_EMPTY_OR_COMMENT -1

#define NEGATIVE_NUM -1
#define POSITIVE_NUM 1

#define DIRECTIVE_WORD 4
#define DIRECTIVE_HALF_WORD 2
#define DIRECTIVE_BYTE 1
#define DIRECTIVE_ASCIZ 3
#define DIRECTIVE_EXTERN 5
#define DIRECTIVE_ENTRY 6
#define DIRECTIVE_ERROR -1
#define D_B_BYTE_NUM 1  /*db number of bytes for each param = 1*/
#define D_H_BYTE_NUM 2  /*dh number of bytes for each param = 2*/
#define D_W_BYTE_NUM 4  /*dw number of bytes for each param = 4*/
#define ASCIZ_BYTE_NUM 1 /*asciz number of bytes for each char = 1*/

#define IC_START 100
#define START_VALUE 0
#define FIRST_ROW 1
#define D_BYTE_MIN_VALUE -128 /*1 byte=8 bits the range is [-2^7...2^7-1]=[-128,127]*/
#define D_BYTE_MAX_VALUE  127 /*1 byte=8 bits the range is [-2^7...2^7-1]=[-128,127]*/
#define D_HALF_MIN_VALUE -32768 /*2 byte=16 bits the range is [-2^15...2^15-1]=[-32768,32767]*/
#define D_HALF_MAX_VALUE  32767 /*2 byte=16 bits the range is [-2^15...2^15-1]=[-32768,32767]*/
#define D_WORD_MAX_VALUE 2147483647  /*4 byte=32 bits the range is [-2^31...2^31-1]=[-2147483648,2147483647]*/
#define D_WORD_MIN_VALUE -2147483648 /*4 byte=32 bits the range is [-2^31...2^31-1]=[-2147483648,2147483647]*/


#define STRING_ERROR -1
#define VALID_STRING 1

#define LABEL_ERROR -1
#define VALID_LABEL 1
#define LABEL_EXISTS -1

#define VALID_SPLIT 1
#define INVALID_SPLIT -1

#define REGISTER_ERROR -1
#define VALID_REGISTER 0
#define REG_MAX_LENGTH 4 /*the max register is $31*/


#define VALID_IMMEDIATE 1
#define IMMEDIATE_ERROR 40000 /*out of 16 bits range [-2^15...2^15-1]=[-32768,32767] */


#define IMM_MIN_VALUE -32768 /*immediate is 16 bits - the range is [-2^15...2^15-1]=[-32768,32767] */
#define IMM_MAX_VALUE 32767 /*immediate is 16 bits - the range is [-2^15...2^15-1]=[-32768,32767] */
#define VALID_BIT_RANGE 1
#define INVALID_BIT_RANGE -1


#define ADD 1
#define SUB 2
#define AND 3
#define OR 4
#define NOR 5
#define MOVE 6
#define MVHI 7
#define MVLO 8
#define ADDI 9
#define SUBI 10
#define ANDI 11
#define ORI 12
#define NORI 13
#define BNE 14
#define BEQ 15
#define BLT 16
#define BGT 17
#define LB 18
#define SB 19
#define LW 20
#define SW 21
#define LH 22
#define SH 23
#define JMP 24
#define LA 25
#define CALL 26
#define STOP 27
#define INSTRUCTION_ERROR -1

#define MIN_REG 0
#define MAX_REG 31

#define ADD_FUNCT 1
#define SUB_FUNCT 2
#define AND_FUNCT 3
#define OR_FUNCT 4
#define NOR_FUNCT 5
#define MOVE_FUNCT 1
#define MVHI_FUNCT 2
#define MVLO_FUNCT 3
#define OP_R_ARI_LOG 0
#define OP_R_COPY 1
#define OP_ADDI 10
#define OP_SUBI 11
#define OP_ANDI 12
#define OP_ORI 13
#define OP_NORI 14
#define OP_BNE 15
#define OP_BEQ 16
#define OP_BLT 17
#define OP_BGT 18
#define OP_LB 19
#define OP_SB 20
#define OP_LW 21
#define OP_SW 22
#define OP_LH 23
#define OP_SH 24
#define OP_JMP 30
#define OP_LA 31
#define OP_CALL 32
#define OP_STOP 63

#define R_UNUSED 0 /*the unused is 0 to all R commands*/
#define J_WITH_REG 1
#define J_WITH_LABEL 0

#define THREE_REGISTERS 3
#define TWO_REGISTERS 2
#define REG_IM_REG_ARI_LOG  4
#define REG_REG_LABEL 5
#define REG_IM_REG_LOAD  6

#define REG_OR_LABEL 1
#define ONE_LABEL 1
#define NONE 0

#define MAX_MEMORY 33554432 /*we have 2^25 volume of memory*/


typedef enum {Instruction, Directive,None} WordType;
typedef enum {R_WORD, I_WORD, J_WORD} InstructionWordType;
typedef enum {D_BYTE, D_HALF, D_WORD, ASCIZ} DirectiveWordType;
typedef enum {False = 0, True = 1} Bool;
typedef enum {Code, Data,NoCodeOrData } Location;
typedef enum {Entry, Extern, NoEntryExtern} LabelType;
typedef enum {NoError,LineTooLong,IllegalCharInLabel,TooLongLabel,firstCharInLabelNotAlphabet,
              CommaBeforeFirstParam,CommaBetweenParams,ParamNotInBitRange,labelBeforeEntry,labelBeforeExtern,notDirectiveOrInstruction,labelExistsInTable,
              IllegalInstruction,IllegalOperandNoComma,RegisterLength,RegisterSign,RegisterNegative,RegisterNotAnInt,RegisterNotInRange,ExtraneousComma,ExtraneousText,
              ExtraneousOperand,MissingOperand,ImmediateNotAnInt,ImmediateNotValid,ImmediateNotInRange,InvalidOperand,ExtraneousImmediate,DirectiveOperandNotAnInt,StringNotValid,
              LabelExistsWithoutExternal,LabelExistsInTable,InvalidTextAfterStop,EntryLabelDontExists,JCommandLabelDontExists,IBranchLabelIsExternal,IBranchLabelDontExists
              ,InvalidDirective,DirectiveOperandWrongSign,MaxMemory,InvalidWhiteChar,LabelIsKnownWord,EntryAndExternalTogether} errorType; /*add error each time, at the end of firstPass - print*/


typedef struct Rfunc {
    unsigned int unused:6;
    unsigned int funct:5;
    unsigned int rd:5;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
} R_cmd;

typedef struct Ifunc {
    int immed:16;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
} I_cmd;

typedef struct Jfunc {

    unsigned int address:25;
    unsigned int reg:1;
    unsigned int opcode:6;

} J_cmd;

 union instructionWord {
    R_cmd rWord;
    I_cmd iWord;
    J_cmd jWord;
    unsigned int bytes:32;
};

typedef struct InstructionWord {
    InstructionWordType wordType;
    unsigned long address;
    union instructionWord code;
} InstructionWord;

union directiveWord {
    int db:8;
    int dh:16;
    int dw:32;
    char asciz;
};

typedef struct DirectiveWord {
    DirectiveWordType wordType;
    unsigned long address;
    union directiveWord data;
} DirectiveWord;

union WordUnion{
    InstructionWord instruction;
    DirectiveWord directive;
};
typedef struct Word {
    WordType wordType;
   union WordUnion wordUnion;
} Word;

typedef struct WordNode *WordNodePtr;
typedef struct WordNode {
    Word word;
    WordNodePtr next;
} WordNode;

typedef struct labelList *labelListPtr;
typedef struct labelList{
    char labelName[LABEL_LENGTH];
    long address;
    Location codeOrData;
    LabelType entryOrExtern;
    labelListPtr next;
}labelList;


typedef struct externalList *externalListPtr;
typedef struct externalList{
    char labelName[LABEL_LENGTH];
    long value;
    externalListPtr next;
}externalList;


typedef struct entryList *entryListPtr;
typedef struct entryList{
    char labelName[LABEL_LENGTH];
    long value;
    entryListPtr next;
}entryList;

typedef struct globalVariables{
    Bool errorFound;
    errorType type;
    int IC;
    int DC;
    int DCF;
    int ICF;
    int currentLine;
    char filename[FILE_NAME_LENGTH];
    char error[LINE_LENGTH];
    FILE *file;
    labelListPtr headLabelTable;
    WordNodePtr headWordList;
    externalListPtr headExternList;
    entryListPtr  headEntryList;
} globalVariables;



#endif