//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "FetchPhase.h"

void FetchPhase::doWork(PipelineStructure *pipeline, uint32_t *pc, Memory *memory) {
    uint32_t myInstruction = memory->read_32(*pc);
    *pc = *pc + 4;
    pipeline->fetch.instruction = myInstruction;
}