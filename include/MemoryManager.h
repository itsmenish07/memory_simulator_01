#ifndef MEMORY_MANAGER_H

#define MEMORY_MANAGER_H

#include <vector>
#include "MemoryBlock.h"

    enum class AllocationStrategy {
    FIRST_FIT =0,
    BEST_FIT =1,
    WORST_FIT = 2
};



class MemoryManager{


    private:
    int totalsize;
    int nextBlockId;
    std:: vector<MemoryBlock> blocks;
    AllocationStrategy strategy;

    public:
    MemoryManager(int totalSize, AllocationStrategy strategy);
    int malloc(int size);
    void freeBlock(int blockId);
    int allocSuccess = 0;
    int allocFailure = 0;


    void dump();
    int getUsedMemory();
    int getFreeMemory();
    double getExternalFragmentation();
    void setStrategy(AllocationStrategy newStrategy);
    void initMemory(int size);



};




#endif