//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "MemoryPhase.h"

void MemoryPhase::doWork(PipelineStructure *pipeline, Memory *memory) {
    unsigned int address = pipeline->memory.addr;

    if(pipeline->memory.writeEnable)
        memory->write_32(address, pipeline->memory.wdata);
    else
        pipeline->memory.rdata = memory->read_32(address);
}