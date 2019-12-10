//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "FetchPhase.h"


void FetchPhase::doWork(PipelineStructure *pipeline, Memory *memory, PCSelect *pcselect, unsigned int *pc) {
    *pc =  pcselect->getPC();
    uint32_t myInstruction = memory->read_32(*pc);
    pipeline->fetch.instruction = myInstruction;
    pipeline->fetch.pc = *pc;
    pcselect->setPCplus4(*pc);
}