//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "Emulator.h"
#define DEBUG 1
#define COSIM 1

Emulator::Emulator() {
    // Init registers
    for (int i = 0; i < 32; i++) {
        x[i] = 0;
        xWriteBack[i] = false;
    }
    pipeline.fetch.isStole = false;
    pipeline.decode.isStole = false;
    pipeline.execute.isStole = false;
    pipeline.memory.isStole = false;
    pipeline.writeBack.isStole = false;
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
    pcSelect.setPCplus4(pc - 4);
    std::cout << pc << std::endl;
    F.close();
}


void Emulator::doWork() {
#ifdef COSIM
    std::ofstream R;
    R.open("tacticRegisters.txt", std::ios::out);
#endif
    int count = 0;
    while (pipeline.fetch.instruction || pipeline.decode.instruction || pipeline.execute.instruction || pipeline.memory.instruction
    || pipeline.writeBack.instruction || pc) {
#ifdef DEBUG
        std::cout << count << " : ";
#endif

        //Do FETCH Phase
        if (!pipeline.fetch.isStole && pc)
            fetchPhase.doWork(&pipeline, &memory, &pcSelect, &pc);
#ifdef DEBUG
        std::cout << "Fetch " << pipeline.fetch.instruction << "; ";
#endif

        //Do DECODE Phase

        if (count > 0 && !pipeline.decode.isBranch) {
            decodePhase.doWork(&pipeline, x, xWriteBack, &pc, &pcSelect);
            if (!pipeline.decode.isStole) {
                pipeline.fetch.isStole = false;
            }
        }
#ifdef DEBUG
        std::cout << "Decode " << pipeline.decode.instruction << "; ";
#endif

        //Do EXECUTE Phase
#ifdef DEBUG
        std::cout << "Execute " << pipeline.execute.instruction << "; ";
#endif
        if (count > 1) {

            if (!pipeline.execute.isStole && !pipeline.execute.isBranch) {
                executePhase.doWork(&pipeline, &pcSelect);
                if (pcSelect.select == 3) {
//                        pipeline.execute.isBranch = true;
//                        pipeline.decode.isBranch = true;
//                        lostCount = 0;
                    pipeline.fetch.instruction = 0;
                    pipeline.execute.instruction = 0;
                    pipeline.decode.instruction = 0;

                    pipeline.decode.isMemoryNeed = false;
                    pipeline.decode.isWriteBackNeed = false;

                    pipeline.execute.isMemoryNeed = false;
                    pipeline.execute.isWriteBackNeed = false;
                }
            }
        }
#ifdef DEBUG
        std::cout << "Memory " << pipeline.memory.instruction << "; ";
#endif
        if (!pipeline.memory.isStole)
            memoryPhase.doWork(&pipeline, &memory);

#ifdef DEBUG
        std::cout << "WriteBack " << pipeline.writeBack.instruction << "; ";
#endif
        if (!pipeline.writeBack.isStole) {
            if (pipeline.writeBack.isWriteBackNeed) {
                writeBackPhase.doWork(&pipeline, x, xWriteBack, R);
            }
        }

        // Do increment tact

        if (!pipeline.memory.isStole) {
            pipeline.writeBack.instruction = pipeline.memory.instruction;
            pipeline.writeBack.wd = pipeline.memory.rdata;
            pipeline.writeBack.regNumForWB = pipeline.memory.regNumForWB;
            pipeline.writeBack.isWriteBackNeed = pipeline.memory.isWriteBackNeed;
            pipeline.memory.instruction = 0;
        }

        if (!pipeline.execute.isStole && count > 1) {
            pipeline.memory.instruction = pipeline.execute.instruction;
            pipeline.memory.isMemoryNeed = pipeline.execute.isMemoryNeed;
            pipeline.memory.isWriteBackNeed = pipeline.execute.isWriteBackNeed;
            pipeline.memory.regNumForWB = pipeline.execute.regNumForWB;
            if (pipeline.execute.isMemoryNeed) {
                pipeline.memory.wdata = pipeline.execute.wData;
                pipeline.memory.addr = pipeline.execute.rd;
                pipeline.memory.writeEnable = pipeline.execute.writeEnable;
            } else
                pipeline.memory.wdata = pipeline.execute.rd;

            pipeline.execute.instruction = 0;
        }

        if (count > 0) {
            if (!pipeline.decode.isStole) {
                pipeline.execute.rs1 = pipeline.decode.rd1;
                pipeline.execute.rs2 = pipeline.decode.rd2;
                pipeline.execute.operation = pipeline.decode.operation;
                pipeline.execute.isMemoryNeed = pipeline.decode.isMemoryNeed;
                pipeline.execute.isWriteBackNeed = pipeline.decode.isWriteBackNeed;
                pipeline.execute.regNumForWB = pipeline.decode.regNumForWB;
                pipeline.execute.instruction = pipeline.decode.instruction;
                pipeline.execute.wData = pipeline.decode.wData;
                pipeline.execute.isStole = false;
                pipeline.execute.writeEnable = pipeline.decode.writeEnable;
                pipeline.decode.instruction = 0;
            } else {
                pipeline.fetch.isStole = true;
                pipeline.execute.isStole = true;
            }
        }

        if (pcSelect.select == 1) {
            pipeline.fetch.instruction = 0;
            pipeline.decode.instruction = 0;

            pipeline.decode.isMemoryNeed = false;
            pipeline.decode.isWriteBackNeed = false;
        } else {
//            if (pipeline.decode.isBranch || pipeline.execute.isBranch) {
//                if (lostCount == 1) {
//                    pipeline.decode.isBranch = false;
//                }
//                if (lostCount == 2) {
//                    pipeline.execute.isBranch = false;
//                }
//                lostCount += 1;
//            }


            if (!pipeline.fetch.isStole) {
                pipeline.decode.instruction = pipeline.fetch.instruction;
                pipeline.decode.pc = pipeline.fetch.pc;
            }

        }
        count += 1;
#ifdef DEBUG
        std::cout << std::endl;
#endif
    }
#ifdef COSIM
    R.close();
#endif

//    std::cout << count << " : ";
//    // Last writeBack
//    if (!pipeline.writeBack.isStole) {
//        if (pipeline.writeBack.isWriteBackNeed) {
//            writeBackPhase.doWork(&pipeline, x);
//            std::cout << "WriteBack " << pipeline.writeBack.instruction << ";" << std::endl;
//        }
//    }
}


void Emulator::printState() {
    for (int i = 0; i < 32; i++) {
        std::cout << "R[" << i << "] = " << x[i] << std::endl;
    }
}