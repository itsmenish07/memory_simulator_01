#include "MemoryBlock.h"

MemoryBlock:: MemoryBlock(int start, int size, bool isFree, int blockId):
start(start), size(size), isFree(isFree), blockId(blockId) {}

