#ifndef CACHE_LEVEL_H
#define CACHE_LEVEL_H

#include <vector>

class CacheLevel {
private:
    int capacity;
    std::vector<int> entries;

public:
    int hits;
    int misses;
    double getHitRatio() const;
    int blockSize;
    int latency;
    long long accessCount = 0;




    CacheLevel(int capacity, int blockSize, int latency);
    bool access(int address);
    int getBlockSize() const;
};

#endif
