//
// Created by Глеб Уваркин on 2019-12-06.
//

#include "Memory.h"

int Memory::write_32(uint32_t addr, uint32_t value) {
    if((addr % 4))
        return 1;
    uint32_t page = addr & PAGE_MASK;
    uint32_t addrInPage = (addr & (~PAGE_MASK))/4;
    auto it = memory.find(page);
    if(it != memory.end()){
        it->second[addrInPage] = value;
    }
    else{
        uint32_t* pageAddr = (uint32_t*)malloc(sizeof(uint32_t) * PAGE_SIZE);
        pageAddr[addrInPage] = value;
        memory.insert(std::pair<uint32_t, uint32_t*>(page, pageAddr));
    }
    return 0;
}

uint32_t Memory::read_32(uint32_t addr) {
    if((addr % 4) || (addr < 0))
        return 1;

    uint32_t page = addr & PAGE_MASK;
    uint32_t addrInPage = (addr & (~PAGE_MASK))/4;
    auto it = memory.find(page);
    if(it != memory.end()){
        return it->second[addrInPage];
    }
    else{
        uint32_t* pageAddr = (uint32_t*)malloc(sizeof(uint32_t) * PAGE_SIZE);
        memory.insert(std::pair<uint32_t, uint32_t*>(page, pageAddr));
        return pageAddr[addrInPage];
    }
}

Memory::~Memory() {
    for(auto & it : memory){
        free(it.second);
    }
}

void Memory::printMemory() {
    for(auto & it : memory)
        for(int i = 0; i < PAGE_SIZE; i++)
            std::cout << it.first + 4 * i << ":" << it.second[i] << std::endl;
}
