//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_EXECUTEPHASE_H
#define TACTICMODEL_EXECUTEPHASE_H

#include <iostream>
#include "PipelineStructure.h"
#include "PipelineStructure.h"
#include "PCSelect.h"

class ExecutePhase{
public:
    void doWork(PipelineStructure *pipeline, PCSelect *pcSelect);
};


#endif //TACTICMODEL_EXECUTEPHASE_H
