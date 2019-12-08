//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_EMULATOR_H
#define TACTICMODEL_EMULATOR_H

#include "Memory.h"
#include "FetchPhase.h"
#include "DecodePhase.h"
#include "ExecutePhase.h"
#include "MemoryPhase.h"
#include "WriteBackPhase.h"


class Emulator {
public:
    Emulator();
    ~Emulator();
    // Main memory
    Memory memory;

    // Pipeline phases
    FetchPhase fetchPhase;
    DecodePhase decodePhase;
    ExecutePhase executePhase;
    MemoryPhase memoryPhase;
    WriteBackPhase writeBackPhase;

    // Registers file
    unsigned int x[32];

    // Program counter
    unsigned int pc;


    void start();
    void end();
};


#endif //TACTICMODEL_EMULATOR_H
