//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "WriteBackPhase.h"

void WriteBackPhase::doWork(PipelineStructure *pipeline, unsigned int *x) {
    x[pipeline->writeBack.regNumForWB] = pipeline->writeBack.wd;
}