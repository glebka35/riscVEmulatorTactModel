//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "ExecutePhase.h"

void ExecutePhase::doWork(PipelineStructure *pipeline, PCSelect *pcSelect) {
    if(pipeline->execute.instruction) {
        switch (pipeline->execute.operation) {
            case ADD:
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
            case BLT:
                if (pipeline->execute.rs1 < pipeline->execute.rs2) {
                    pcSelect->select = 3;
                }
                break;
            case BEQ:
                if (pipeline->execute.rs1 == pipeline->execute.rs2) {
                    pcSelect->select = 3;
                }
                break;
            case BNE:
                if (pipeline->execute.rs1 != pipeline->execute.rs2) {
                    pcSelect->select = 3;
                }
                break;
            case BGE:
                if (pipeline->execute.rs1 >= pipeline->execute.rs2) {
                    pcSelect->select = 3;
                }
                break;

            default:
                std::cout << "Unrecognized operation in ALU" << std::endl;
        }
    }
}