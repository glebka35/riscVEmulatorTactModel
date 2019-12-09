//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_FETCHPHASE_H
#define TACTICMODEL_FETCHPHASE_H

#include <cstdint>
#include "PipelineStructure.h"
#include "Memory.h"
#include "PCSelect.h"

class FetchPhase{
public:
    void doWork(PipelineStructure *pipeline, Memory *memory, PCSelect *pcSelect, unsigned int *pc);

};


#endif //TACTICMODEL_FETCHPHASE_H
