#ifndef CACHE_SYSTEM_H
#define CACHE_SYSTEM_H

#include "CacheLevel.h"

class CacheSystem {
private:
    CacheLevel L1;
    CacheLevel L2;
    static const int MEMORY_LATENCY = 100;

public:
    CacheSystem(int l1Size, int l2Size);
    void access(int address);
    void printStats();
    long long totalAccessTime = 0;

};

#endif
