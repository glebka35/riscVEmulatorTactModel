//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_MEMORYPHASE_H
#define TACTICMODEL_MEMORYPHASE_H

#include "PipelineStructure.h"
#include "Memory.h"

class MemoryPhase{
public:
    void doWork(PipelineStructure *pipeline, Memory *memory);

};


#endif //TACTICMODEL_MEMORYPHASE_H
