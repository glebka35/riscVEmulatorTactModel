//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "Emulator.h"

int lostCount = 0;

Emulator::Emulator() {
    // Init registers
    for (int i = 0; i < 32 ; i++) {
        x[i] = 0;
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
}


void Emulator::doWork() {
    int count = 0;
    while (pc != 0) {
        std::cout << count << " : ";
        //Do FETCH Phase
        if (!pipeline.fetch.isStole) {
            fetchPhase.doWork(&pipeline, &memory, &pcSelect, &pc);
            std::cout << "Fetch " << pipeline.fetch.instruction << "; ";
        } else
            std::cout << "_Fetch_ " << pipeline.fetch.instruction << "; ";

        //Do DECODE Phase
        if (count > 0 && !pipeline.decode.bubble && !pipeline.decode.isBranch) {
            decodePhase.doWork(&pipeline, x, &pc, &pcSelect);
            if (!pipeline.decode.isStole) {
                pipeline.fetch.isStole = false;
                std::cout << "Decode " << pipeline.decode.instruction << "; ";
            } else
                std::cout << "_Decode_ " << pipeline.decode.instruction << "; ";
        }

        //Do EXECUTE Phase
        if (count > 1) {
            if (!pipeline.execute.bubble) {
                if (!pipeline.execute.isStole && !pipeline.execute.isBranch) {
                    executePhase.doWork(&pipeline, &pcSelect);
                    std::cout << "Execute " << pipeline.execute.instruction << "; ";
                    if (pcSelect.select == 3) {
                        pipeline.execute.isBranch = true;
                        pipeline.decode.isBranch = true;
                        lostCount = 0;
                    }

                }
            }
        }


        if (!pipeline.memory.isStole) {
            if (pipeline.memory.isMemoryNeed) {
                memoryPhase.doWork(&pipeline, &memory);
                std::cout << "Memory " << pipeline.memory.instruction << "; ";
            }
        }


        if (!pipeline.writeBack.isStole) {
            if (pipeline.writeBack.isWriteBackNeed) {
                writeBackPhase.doWork(&pipeline, x);
                std::cout << "WriteBack " << pipeline.writeBack.instruction << "; ";
            }
        }

        // Do increment tact

        if (!pipeline.memory.isStole && pipeline.memory.isWriteBackNeed && pipeline.memory.isMemoryNeed) {
            pipeline.writeBack.instruction = pipeline.memory.instruction;
            pipeline.writeBack.wd = pipeline.memory.rdata;
            pipeline.writeBack.regNumForWB = pipeline.memory.regNumForWB;
        }

        if (!pipeline.execute.isStole && count > 1) {
            if (!pipeline.execute.isMemoryNeed) {
                if (pipeline.execute.isWriteBackNeed) {
                    pipeline.writeBack.wd = pipeline.execute.rd;
                    pipeline.writeBack.regNumForWB = pipeline.execute.regNumForWB;
                    pipeline.writeBack.instruction = pipeline.execute.instruction;
                    pipeline.writeBack.isWriteBackNeed = pipeline.execute.isWriteBackNeed;
                }
            } else {
                pipeline.memory.wdata = pipeline.execute.wData;
                pipeline.memory.addr = pipeline.execute.rd;
                pipeline.memory.isWriteBackNeed = pipeline.execute.isWriteBackNeed;
                pipeline.memory.isMemoryNeed = pipeline.execute.isMemoryNeed;
                pipeline.memory.instruction = pipeline.execute.instruction;
                pipeline.memory.writeEnable = pipeline.execute.writeEnable;
            }
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
                if (pipeline.decode.bubble) {
                    pipeline.execute.bubble = true;
                    pipeline.decode.bubble = false;
                }
            } else {
                pipeline.fetch.isStole = true;
                pipeline.execute.isStole = true;
            }
        }

        if (pcSelect.select == 1) {
            pipeline.decode.bubble = true;
        } else {
            if(pipeline.decode.isBranch || pipeline.execute.isBranch){
                if(lostCount == 1){
                    pipeline.decode.isBranch = false;
                }
                if(lostCount == 2){
                    pipeline.execute.isBranch = false;
                }
                lostCount += 1;
            }


            if (!pipeline.fetch.isStole)
                pipeline.decode.instruction = pipeline.fetch.instruction;
        }
        count += 1;
        std::cout << std::endl;
    }

    std::cout << count << " : ";
    // Last writeBack
    if (!pipeline.writeBack.isStole) {
        if (pipeline.writeBack.isWriteBackNeed) {
            writeBackPhase.doWork(&pipeline, x);
            std::cout << "WriteBack " << pipeline.writeBack.instruction << ";" << std::endl;
        }
    }
}


    void Emulator::printState() {
        for(int i = 0; i < 32; i ++){
            std::cout << "R[" << i << "] = " << x[i] << std::endl;
        }
}