//
// Created by Глеб Уваркин on 2019-12-08.
//

#ifndef TACTICMODEL_PIPELINESTRUCTURE_H
#define TACTICMODEL_PIPELINESTRUCTURE_H
enum {
    ADD,
    SUB,
    XOR,
    SHIFT_LEFT,
    SHIFT_RIGHT

} AluOperations;


typedef struct FetchVar{
    //Variables for Fetch Phase
    unsigned int instruction;
    bool isStole;
}FetchVar;

typedef struct DecodeVar{//Variables for Decode Phase
    unsigned int instruction;
    unsigned int rs1;
    unsigned int rs2;
    unsigned int rd1;
    unsigned int rd2;
    unsigned int imm;
    unsigned int regNumForWB;
    int operation;
    bool isImmSelect;
    bool isStole;
    bool isMemoryNeed;
    bool isWriteBackNeed;
    bool writeEnable;
}DecodeVar;

typedef struct ExecuteVar{//Variables for Execute Phase
    unsigned int rs1;
    unsigned int rs2;
    unsigned int rd;
    unsigned int data;
    unsigned int regNumForWB;
    int operation;
    bool isStole;
    bool isMemoryNeed;
    bool isWriteBackNeed;
    bool writeEnable;
}ExecuteVar;

typedef struct MemoryVar{//Variables for Memory Phase
    unsigned int addr;
    unsigned int wdata;
    unsigned int rdata;
    unsigned int regNumForWB;
    bool writeEnable;
    bool isStole;
    bool isWriteBackNeed;
    bool isMemoryNeed;
}MemoryVar;

typedef struct WriteBackVar{//Variables for Write Back
    unsigned int wd;
    unsigned int regNumForWB;
    bool isStole;

}WriteBackVar;


typedef struct PipelineStructure{
    FetchVar fetch;
    DecodeVar decode;
    ExecuteVar execute;
    MemoryVar memory;
    WriteBackVar writeBack;
} PipelineStructure;

#endif //TACTICMODEL_PIPELINESTRUCTURE_H
