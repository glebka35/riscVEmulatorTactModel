//
// Created by Глеб Уваркин on 2019-12-06.
//

#include <fstream>
#include "WriteBackPhase.h"

#define COSIM 1

void WriteBackPhase::doWork(PipelineStructure *pipeline, unsigned int *x, bool *xWriteBack, std::ofstream &R) {
    if (pipeline->writeBack.isWriteBackNeed) {
        if (pipeline->writeBack.instruction) {
            x[pipeline->writeBack.regNumForWB] = pipeline->writeBack.wd;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                    R << x[i] << " ";
            }
            R << std::endl;
#endif
            xWriteBack[pipeline->writeBack.regNumForWB] = false;
            pipeline->writeBack.isWriteBackNeed = false;
        }
    }
    pipeline->writeBack.instruction = 0;
    x[0] = 0;

}