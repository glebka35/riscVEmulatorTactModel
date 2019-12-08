//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_WRITEBACKPHASE_H
#define TACTICMODEL_WRITEBACKPHASE_H

#include "PipelineStructure.h"

class WriteBackPhase {
public:
    void doWork(PipelineStructure *pipeline, unsigned int *x);

};


#endif //TACTICMODEL_WRITEBACKPHASE_H
