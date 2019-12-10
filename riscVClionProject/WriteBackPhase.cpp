//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "WriteBackPhase.h"

void WriteBackPhase::doWork(PipelineStructure *pipeline, unsigned int *x, bool *xWriteBack) {
    if(pipeline->writeBack.isWriteBackNeed) {
        if(pipeline->writeBack.instruction) {
            x[pipeline->writeBack.regNumForWB] = pipeline->writeBack.wd;
            if(pipeline->writeBack.regNumForWB == 13){
                pipeline->writeBack.regNumForWB = 13;
            }
            xWriteBack[pipeline->writeBack.regNumForWB] = false;
            pipeline->writeBack.isWriteBackNeed = false;
        }
    }
    pipeline->writeBack.instruction = 0;
    x[0] = 0;

}