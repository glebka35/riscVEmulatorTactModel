//
// Created by Глеб Уваркин on 2019-12-09.
//

#include "PCSelect.h"

unsigned int PCSelect::getPC() {
    switch(select){
        case 0:
            return PCplus4;
        case 1:
            return jabs;
        case 2:
            return rind;
        case 3:
            return branch;
        default:
            return 0;
    }
}

void PCSelect::setPCplus4(unsigned int pc) {
    PCplus4 = pc + 4;
    select = 0;
}

void PCSelect::setJabs(unsigned int pc) {
    jabs = pc;
    select = 1;
}

void PCSelect::setRind(unsigned int pc) {
    rind = pc;
    select = 2;
}

void PCSelect::setBranch(unsigned int pc) {
    branch = pc;
    select = 3;
}
