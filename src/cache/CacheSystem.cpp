#include <iostream>
#include "CacheSystem.h"

CacheSystem::CacheSystem(int l1Size, int l2Size)
    : L1(l1Size,1 , 1), L2(l2Size,1 ,10 ) {}

void CacheSystem::access(int address) {

    totalAccessTime += L1.latency;
    L1.accessCount++;

    if (L1.access(address)) {
        return;
    }
    totalAccessTime += L2.latency;
    L2.accessCount++;

    if (L2.access(address)) {
        // Promote to L1
        L1.access(address);
        return;
    }
    totalAccessTime += MEMORY_LATENCY;

    L2.access(address);
    L1.access(address);
}

void CacheSystem::printStats() {
    std::cout << "\nCache Statistics:\n";
    std::cout << "L1 Hits: " << L1.hits << "\n";
    std::cout << "L1 Misses: " << L1.misses << "\n";
    std::cout << "L2 Hits: " << L2.hits << "\n";
    std::cout << "L2 Misses: " << L2.misses << "\n";
    std::cout << "L1 Hit Ratio: " << L1.getHitRatio() * 100 << "%\n";
std::cout << "L2 Hit Ratio: " << L2.getHitRatio() * 100 << "%\n";

}
