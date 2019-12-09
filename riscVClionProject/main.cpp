#include <iostream>
#include "Emulator.h"

int main() {
    Emulator riscV;

    riscV.loadProgramToMemory("ptloadIF.txt");
    riscV.doWork();
    riscV.printState();
    return 0;
}