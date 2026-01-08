#include <iostream>
#include "MemoryManager.h"

MemoryManager::MemoryManager(int totalsize, AllocationStrategy strategy): totalsize(totalsize),strategy(strategy), nextBlockId(1){
blocks.push_back(MemoryBlock(0, totalsize, true));
}

int MemoryManager::malloc(int size) {
    int selected = -1;
    std::cout << "Current strategy = " << static_cast<int>(strategy) << "\n";


    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].isFree && blocks[i].size >= size) {

            if (strategy == AllocationStrategy::FIRST_FIT) {
                selected = i;
                break;
            }

            if (strategy == AllocationStrategy::BEST_FIT) {
                if (selected == -1 || blocks[i].size < blocks[selected].size)
                    selected = i;
            }

            if (strategy == AllocationStrategy::WORST_FIT) {
                if (selected == -1 || blocks[i].size > blocks[selected].size)
                    selected = i;
            }
        }
        allocSuccess++;
    }

    if (selected == -1) {
            allocFailure++;
                return -1;
    }

    MemoryBlock &block = blocks[selected];

            MemoryBlock allocated(
                block.start,
                size,
                false,
                nextBlockId++
            );

            block.start += size;
            block.size -= size;

            blocks.insert(blocks.begin() + selected, allocated);

            if (blocks[selected + 1].size == 0) {
            blocks.erase(blocks.begin() + selected + 1);
}
            return allocated.blockId;
        }

void MemoryManager::dump() {
    std::cout << "\nMemory Layout:\n";
    for (auto &block : blocks) {
        int end = block.start + block.size - 1;
        if (block.isFree) {
            std::cout << "[" << block.start << " - " << end << "] FREE\n";
        } else {
            std::cout << "[" << block.start << " - " << end
                      << "] USED (id=" << block.blockId << ")\n";
        }
    }
}

void MemoryManager::freeBlock(int blockId) {
    for (int i = 0; i < blocks.size(); i++) {
        if (!blocks[i].isFree && blocks[i].blockId == blockId) {

            blocks[i].isFree = true;
            blocks[i].blockId = -1;

            if (i > 0 && blocks[i - 1].isFree) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
                i--;
            }

            if (i < blocks.size() - 1 && blocks[i + 1].isFree) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            return;
        }
    }

    std::cout << "Block ID not found!\n";

    
}

int MemoryManager::getUsedMemory() {
    int used = 0;
    for (auto &block : blocks) {
        if (!block.isFree) {
            used += block.size;
        }
    }
    return used;
}

int MemoryManager::getFreeMemory() {
    int freeMem = 0;
    for (auto &block : blocks) {
        if (block.isFree) {
            freeMem += block.size;
        }
    }
    return freeMem;
}

double MemoryManager::getExternalFragmentation() {
    int totalFree = 0;
    int largestFree = 0;

    for (auto &block : blocks) {
        if (block.isFree) {
            totalFree += block.size;
            if (block.size > largestFree) {
                largestFree = block.size;
            }
        }
    }

    if (totalFree == 0) return 0.0;

    return 1.0 - (double)largestFree / totalFree;
}

void MemoryManager::setStrategy(AllocationStrategy newStrategy) {
    strategy = newStrategy;
}
void MemoryManager::initMemory(int size) {
    totalsize = size;
    blocks.clear();
    nextBlockId = 1;

    blocks.push_back(MemoryBlock(0, totalsize, true));
}



