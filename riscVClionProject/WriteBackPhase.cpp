//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "WriteBackPhase.h"

void WriteBackPhase::doWork(PipelineStructure *pipeline, unsigned int *x) {
    x[pipeline->writeBack.regNumForWB] = pipeline->writeBack.wd;
    if(pipeline->writeBack.regNumForWB == pipeline->decode.regNumForWB)
        pipeline->decode.regNumForWB = NO_STOLE;
    pipeline->writeBack.isWriteBackNeed = false;
}