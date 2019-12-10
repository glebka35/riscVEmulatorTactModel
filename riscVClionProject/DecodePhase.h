//
// Created by Глеб Уваркин on 2019-12-06.
//

#ifndef TACTICMODEL_DECODEPHASE_H
#define TACTICMODEL_DECODEPHASE_H

#include "PipelineStructure.h"
#include "Instructions.h"
#include "PCSelect.h"

class DecodePhase{
public:
    void doWork(PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack, uint32_t *pc, PCSelect *pcSelect);

    void decode(rTypeInstruction rType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack);
    void decode(iTypeInstruction iType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack, uint32_t *pc, PCSelect *pcSelect);
    void decode(uTypeInstruction uType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack );
    void decode(jTypeInstruction jType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack, uint32_t *pc, PCSelect *pcSelect);
    void decode(iLoadTypeInstruction iLoadType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack );
    void decode(bTypeInstruction bType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack ,uint32_t *pc, PCSelect *pcSelect);
    void decode(sTypeInstruction sType, PipelineStructure *pipeline, uint32_t *x, bool *xWriteBack );

};


#endif //TACTICMODEL_DECODEPHASE_H
