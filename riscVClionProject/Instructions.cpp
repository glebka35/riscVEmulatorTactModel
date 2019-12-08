//
// Created by Глеб Уваркин on 2019-11-25.
//

#include "Instructions.h"

rTypeInstruction::rTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    funct7 = (instruction >> 25) & 0x7F;
}

iTypeInstruction::iTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    imm12 = (instruction >> 20) & 0xFFF;
}

uTypeInstruction::uTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    imm20 = (instruction >> 12) & 0xFFFFF;
}

jTypeInstruction::jTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    imm20 = (((instruction >> 21) & 0x3FF) + (((instruction >> 20) & 0x1) << 10) + (((instruction >> 12) & 0xFF) << 12) + (((instruction >> 31) & 0x1) << 20)) << 1;
}

iLoadTypeInstruction::iLoadTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    func3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    imm12 = (instruction >> 20) & 0xFFF;

}


sTypeInstruction::sTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm12 = ((instruction >> 7) & 0x1F) + (((instruction >> 25) & 0xFF) << 5);
}

bTypeInstruction::bTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    imm12 = (((instruction >> 8) & 0xF) + (((instruction >> 25) & 0x3F)<<4) + (((instruction >> 7) & 0x1)<<10) + (((instruction >> 31) & 0x1)<<11)) << 1;
}
