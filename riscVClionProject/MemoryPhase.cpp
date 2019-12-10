//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "MemoryPhase.h"

void MemoryPhase::doWork(PipelineStructure *pipeline, Memory *memory) {
    if(pipeline->memory.instruction) {
        if (pipeline->memory.isMemoryNeed) {
            unsigned int address = pipeline->memory.addr;
            if (pipeline->memory.writeEnable)
                memory->write_32(address, pipeline->memory.wdata);
            else
                pipeline->memory.rdata = memory->read_32(address);
            pipeline->memory.isMemoryNeed = false;
        } else {
            pipeline->memory.rdata = pipeline->memory.wdata;
        }
    }
}