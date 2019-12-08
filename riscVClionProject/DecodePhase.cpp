//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "DecodePhase.h"
void DecodePhase::doWork(PipelineStructure *pipeline, uint32_t *x, uint32_t *pc) {
    uint32_t myInstruction = pipeline->fetch.instruction;
    switch (myInstruction & 0x7F) {
        case R_TYPE_OPCODE:
            decode(rTypeInstruction(myInstruction), pipeline, x);
            break;
        case I_TYPE_OPCODE:
            decode(iTypeInstruction(myInstruction), pipeline, x, pc);
            break;
//        case U_TYPE_OPCODE:
//            decode(uTypeInstruction(myInstruction), pipeline, x);
//            break;
//        case B_TYPE_OPCODE:
//            decode(bTypeInstruction(myInstruction), pipeline, x);
//            break;
        case J_TYPE_OPCODE:
            decode(jTypeInstruction(myInstruction), pipeline, x, pc);
            break;
        case S_TYPE_OPCODE:
            decode(sTypeInstruction(myInstruction), pipeline, x);
            break;
        case I_TYPE_OPCODE_LOAD:
            decode(iLoadTypeInstruction(myInstruction), pipeline, x);
        case I_TYPE_OPCODE_JALR:
            decode(iTypeInstruction(myInstruction), pipeline, x, pc);
            break;
//        default:
//            isEnd = true;
//            end = clock();
//            double t = ((double)end - start)/((double)CLOCKS_PER_SEC);
//            std::cout<<"Unrecognized instruction: " << myInstruction << std::endl;
//            std::cout<<"Program counter: " << pc << std::endl;
//            std::cout<<"Instructions amount: " << counter << std::endl;
//            std::cout<<"Time is " << t << "sec" << std::endl;
//            std::cout<<"Speed is " << counter/t/1000000 << " Mill of instr/sec"<<std::endl;
    }
}

void DecodePhase::decode(rTypeInstruction rType, PipelineStructure *pipeline, uint32_t *x) {
    uint8_t rs1 = rType.rs1;
    uint8_t rs2 = rType.rs2;
    uint8_t rd = rType.rd;
    pipeline->decode.rs1 = x[rs1];
    pipeline->decode.rs2 = x[rs2];
    pipeline->decode.isImmSelect = false;
    pipeline->decode.isMemoryNeed = false;
    pipeline->decode.isWriteBackNeed = true;
    switch (rType.fullInstruction & R_TYPE_MASK) {
        case add_value:
            pipeline->decode.operation = ADD;
            break;
        case xor_value:
            pipeline->decode.operation = XOR;
            break;
        case sub_value:
            pipeline->decode.operation = SUB;
            break;
    }
}

void DecodePhase::decode(iTypeInstruction iType, PipelineStructure *pipeline, uint32_t *x, uint32_t *pc) {
    uint8_t rs1 = iType.rs1;
    uint32_t imm12 = iType.imm12;
    uint8_t rd = iType.rd;
    if ((imm12 & 0x800) == 2048){
        imm12 = imm12 | 0xFFFFF000;
    }
    pipeline->decode.rs1 = x[rs1];
    pipeline->decode.rs2 = imm12;
    pipeline->decode.isImmSelect = true;
    pipeline->decode.isMemoryNeed = false;
    pipeline->decode.isWriteBackNeed = true;
    switch (iType.fullInstruction & I_TYPE_MASK) {
        case addi_value:
        pipeline->decode.operation = ADD;
            break;

        case jalr_value:

            pipeline->decode.operation = ADD;
            x[rd] = *pc + 4;
            *pc = (x[rs1] + imm12) & 0xFFFFFFFE;
            break;
    }
    switch (iType.fullInstruction & I_TYPE_MASK_SHIFT) {
        case slli_value:
            pipeline->decode.operation = SHIFT_LEFT;
            break;

        case srai_value:
            pipeline->decode.operation = SHIFT_RIGHT;
            break;
    }

}

//void DecodePhase::decode(uTypeInstruction uType) {
//    uint8_t rd = uType.rd;
//    uint32_t imm20 = uType.imm20;
//    switch (uType.fullInstruction & U_TYPE_MASK) {
//        case auipc_value:
//            x[rd] = x[pc] + x[imm20];
//            break;
//    }
//}

void DecodePhase::decode(jTypeInstruction jType, PipelineStructure *pipeline, uint32_t *x, uint32_t *pc) {
    uint8_t rd = jType.rd;
    uint32_t imm20 = jType.imm20;
    switch (jType.fullInstruction & J_TYPE_MASK) {
        case jal_value:
            if ((imm20 & 0x80000) == 524288){
                imm20 = imm20 | 0xFFF00000;
            }
//            pipeline->decode.rs1 = ;
//            pipeline->decode.rs2 = imm20;
//            pipeline->decode.operation = ADD;
            x[rd] = *pc + 4;
            *pc = *pc + imm20;
            break;
    }
}

void DecodePhase::decode(iLoadTypeInstruction iLoadType, PipelineStructure *pipeline, uint32_t *x) {
    uint8_t rs1 = iLoadType.rs1;
    uint32_t imm12 = iLoadType.imm12;
    uint8_t rd = iLoadType.rd;
    switch (iLoadType.fullInstruction & I_TYPE_MASK_LOAD) {
        case lw_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            pipeline->decode.rs1 = x[rs1];
            pipeline->decode.rs2 = imm12;
            pipeline->decode.operation = ADD;
            pipeline->decode.isImmSelect = true;
            pipeline->decode.isMemoryNeed = true;
            pipeline->decode.isWriteBackNeed = true;
//            x[rd] = memory.read_32(x[rs1] + imm12);
//            pc+=4;
            break;
    }
}

void DecodePhase::decode(sTypeInstruction sType, PipelineStructure *pipeline, uint32_t *x) {
    uint8_t rs1 = sType.rs1;
    uint8_t rs2 = sType.rs2;
    uint32_t imm12 = sType.imm12;
    switch (sType.fullInstruction & S_TYPE_MASK) {
        case sw_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            pipeline->decode.rs1 = x[rs1];
            pipeline->decode.rs2 = imm12;
            pipeline->decode.operation = ADD;
            pipeline->decode.isImmSelect = true;
            pipeline->decode.isMemoryNeed = true;
            pipeline->decode.isWriteBackNeed = true;
//            memory.write_32(x[rs1] + imm12, x[rs2]);
//            pc+=4;
            break;
    }
}

//void DecodePhase::decode(bTypeInstruction bType, PipelineStructure *pipeline, uint32_t *x) {
//    uint8_t rs1 = bType.rs1;
//    uint8_t rs2 = bType.rs2;
//    uint32_t imm12 = bType.imm12;
//
//    switch (bType.fullInstruction & B_TYPE_MASK) {
//        case blt_value:
//            if ((imm12 & 0x800) == 2048) {
//                imm12 = imm12 | 0xFFFFF000;
//            }
//            if (x[rs1] < x[rs2]) {
//                pc = pc + imm12;
//            } else{
//                pc += 4;
//            }
//            break;
//
//        case beq_value:
//            if ((imm12 & 0x800) == 2048) {
//                imm12 = imm12 | 0xFFFFF000;
//            }
//            if (x[rs1] == x[rs2]) {
//                pc = pc + imm12;
//            } else{
//                pc += 4;
//            }
//            break;
//
//        case bne_value:
//            if ((imm12 & 0x800) == 2048) {
//                imm12 = imm12 | 0xFFFFF000;
//            }
//            if (x[rs1] != x[rs2]) {
//                pc = pc + imm12;
//            } else{
//                pc += 4;
//            }
//            break;
//
//        case bge_value:
//            if ((imm12 & 0x800) == 2048) {
//                imm12 = imm12 | 0xFFFFF000;
//            }
//            if (x[rs1] >= x[rs2]) {
//                pc = pc + imm12;
//            } else{
//                pc += 4;
//            }
//            break;
//    }
//}