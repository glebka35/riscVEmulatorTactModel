//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "ExecutePhase.h"

void ExecutePhase::doWork(PipelineStructure *pipeline) {
    switch(pipeline->execute.operation){
        case SUM:
            pipeline->execute.rd = pipeline->execute.rs1 + pipeline->execute.rs2;
            break;
        case SUB:
            pipeline->execute.rd = pipeline->execute.rs1 - pipeline->execute.rs2;
            break;
        case XOR:
            pipeline->execute.rd = pipeline->execute.rs1 ^ pipeline->execute.rs2;
            break;
        case SHIFT_LEFT:
            pipeline->execute.rd = pipeline->execute.rs1 << pipeline->execute.rs2;
            break;
        case SHIFT_RIGHT:
            pipeline->execute.rd = pipeline->execute.rs1 >> pipeline->execute.rs2;
            break;

        default:
            std::cout<<"Unrecognized operation in ALU"<<std::endl;
    }
}