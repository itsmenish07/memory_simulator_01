#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

class MemoryBlock{
    public:
    int start;
    int size;
    bool isFree;
    int blockId;

    MemoryBlock(int start, int size, bool isFree, int blockId = -1);


};
#endif