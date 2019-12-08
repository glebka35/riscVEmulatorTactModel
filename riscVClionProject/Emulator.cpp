//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "Emulator.h"

Emulator::Emulator() {

}

Emulator::~Emulator() {

}
void Emulator::loadProgramToMemory(std::string fileName) {
    uint32_t address;
    uint32_t instruction;
    uint32_t startAddress;
    std::ifstream F;

    F.open(fileName, std::ios::in);
    if (F) {
        F >> startAddress;
        while (!F.eof()) {
            F >> address >> instruction;
            memory.write_32(address, instruction);
        }
    }
    pc = startAddress;
    std::cout << pc << std::endl;
}

//void Emulator::start() {
//    // читаем инструкции из файла и пишем их в память эмулятора
//    // TODO
//
//    // ининциализиурем PC
//    // TODO
//}

void Emulator::doWork() {
    while (pc != 0) {

        // increment tact
        if (!pipeline.fetch.isStole) {
            pipeline.decode.instruction = pipeline.fetch.instruction;
        }

        if (!pipeline.decode.isStole) {
            pipeline.execute.rs1 = pipeline.decode.rd1;
            pipeline.execute.rs2 = pipeline.decode.rd2;
            pipeline.execute.operation = pipeline.decode.operation;
            pipeline.execute.isMemoryNeed = pipeline.decode.isMemoryNeed;
            pipeline.execute.isWriteBackNeed = pipeline.decode.isWriteBackNeed;
            pipeline.execute.regNumForWB = pipeline.decode.regNumForWB;
        }

        if (!pipeline.execute.isStole) {
            if (!pipeline.execute.isMemoryNeed) {
                pipeline.writeBack.wd = pipeline.execute.rd;
                pipeline.writeBack.regNumForWB = pipeline.execute.regNumForWB;
            } else {
                pipeline.memory.wdata = pipeline.execute.data;
                pipeline.memory.addr = pipeline.execute.rd;
                pipeline.memory.isWriteBackNeed = pipeline.execute.isWriteBackNeed;
            }
        }

        if (!pipeline.memory.isStole && pipeline.memory.isWriteBackNeed && pipeline.memory.isMemoryNeed) {
            pipeline.writeBack.wd = pipeline.memory.rdata;
            pipeline.writeBack.regNumForWB = pipeline.memory.regNumForWB;
        }
    }
}

    void Emulator::printState() {
        for(int i = 0; i < 32; i ++){
            std::cout << "R[" << i << "] = " << x[i] << std::endl;
        }
}