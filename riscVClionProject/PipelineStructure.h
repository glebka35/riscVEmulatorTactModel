//
// Created by Глеб Уваркин on 2019-12-08.
//

#ifndef TACTICMODEL_PIPELINESTRUCTURE_H
#define TACTICMODEL_PIPELINESTRUCTURE_H

#define NO_STOLE 32
enum {
    ADD,
    SUB,
    XOR,
    SHIFT_LEFT,
    SHIFT_RIGHT,
    BNE,
    BGT,
    BEQ,
    BGE,
    BLT
} AluOperations;


typedef struct FetchVar{
    //Variables for Fetch Phase
    unsigned int instruction = 0;
    bool isStole;
}FetchVar;

typedef struct DecodeVar{//Variables for Decode Phase
    unsigned int instruction = 0;
    unsigned int rs1;
    unsigned int rs2;
    unsigned int rd1;
    unsigned int rd2;
    unsigned int imm;
    unsigned int wData;
    unsigned int regNumForWB = NO_STOLE;
    int operation;
    bool isImmSelect;
    bool isStole;
    bool isMemoryNeed = false;
    bool isWriteBackNeed = false;
    bool writeEnable;
    bool bubble = false;
    bool isBranch = false;
}DecodeVar;

typedef struct ExecuteVar{//Variables for Execute Phase
    unsigned int instruction = 0;
    unsigned int rs1;
    unsigned int rs2;
    unsigned int rd;
    unsigned int wData;
    unsigned int regNumForWB;
    int operation;
    bool isStole;
    bool isMemoryNeed = false;
    bool isWriteBackNeed = false;
    bool writeEnable;
    bool bubble = false;
    bool isBranch = false;
}ExecuteVar;

typedef struct MemoryVar{//Variables for Memory Phase
    unsigned int instruction = 0;
    unsigned int addr;
    unsigned int wdata;
    unsigned int rdata;
    unsigned int regNumForWB;
    bool writeEnable;
    bool isStole ;
    bool isWriteBackNeed = false;
    bool isMemoryNeed = false;
}MemoryVar;

typedef struct WriteBackVar{//Variables for Write Back
    unsigned int instruction = 0;
    unsigned int wd;
    unsigned int regNumForWB;
    bool isStole;
    bool isWriteBackNeed = false;
}WriteBackVar;


typedef struct PipelineStructure{
    FetchVar fetch;
    DecodeVar decode;
    ExecuteVar execute;
    MemoryVar memory;
    WriteBackVar writeBack;
} PipelineStructure;

#endif //TACTICMODEL_PIPELINESTRUCTURE_H
