#include "CacheLevel.h"

CacheLevel::CacheLevel(int capacity, int blockSize, int latency)
    : capacity(capacity),
      blockSize(blockSize),
      latency(latency),
      hits(0),
      misses(0) {}

bool CacheLevel::access(int address) {
    for (int addr : entries) {
        if (addr == address) {
            hits++;
            return true; 
        }
    }

    misses++;

    if (entries.size() == capacity) {
        entries.erase(entries.begin());
    }
    

    entries.push_back(address);
    return false;
}
double CacheLevel::getHitRatio() const {
    int total = hits + misses;
    if (total == 0) return 0.0;
    return (double)hits / total;
}
int CacheLevel::getBlockSize() const {
    return blockSize;
}


