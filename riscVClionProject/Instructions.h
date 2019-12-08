//
// Created by Глеб Уваркин on 2019-11-25.
//

#ifndef TACTICMODEL_INSTRUCTIONS_H
#define TACTICMODEL_INSTRUCTIONS_H


#include <cstdint>

#define R_TYPE_OPCODE       0x33
#define I_TYPE_OPCODE       0x13
#define I_TYPE_OPCODE_LOAD  0x03
#define I_TYPE_OPCODE_JALR  0x67
#define S_TYPE_OPCODE       0x23
#define B_TYPE_OPCODE       0x63
#define U_TYPE_OPCODE       0x37
#define J_TYPE_OPCODE       0x6f

#define add_value 0x33
#define xor_value 0x4033
#define sub_value 0x40000033
#define R_TYPE_MASK 0xfe00707f

#define addi_value 0x13
#define jalr_value 0x67
#define I_TYPE_MASK 0x707f

#define slli_value 0x1013
#define srai_value 0x40005013
#define I_TYPE_MASK_SHIFT 0xfc00707f

#define auipc_value 0x17
#define U_TYPE_MASK 0x7f

#define jal_value   0x6f
#define J_TYPE_MASK 0x7f

#define sw_value   0x2023
#define S_TYPE_MASK 0x707f

#define lw_value    0x2003
#define I_TYPE_MASK_LOAD  0x707f

#define blt_value 0x4063
#define beq_value 0x63
#define bne_value 0x1063
#define bge_value 0x5063
#define B_TYPE_MASK 0x707f

class rTypeInstruction {
public:
    rTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
};

class iTypeInstruction {
public:
    iTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint32_t imm12;
};

class uTypeInstruction {
public:
    uTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint32_t imm20;
};

class bTypeInstruction {
public:
    bTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint32_t imm12;
};

class jTypeInstruction {
public:
    jTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint32_t imm20;
};

class sTypeInstruction {
public:
    sTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint32_t imm12;
};


class iLoadTypeInstruction {
public:
    iLoadTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t func3;
    uint8_t rs1;
    uint16_t imm12;
};
#endif //RISCVCLIONPROJECT_INSTRUCTIONS_H
