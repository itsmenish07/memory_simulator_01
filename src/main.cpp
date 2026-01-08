#include <iostream>
#include <string>
#include "MemoryManager.h"
#include "CacheSystem.h"

int main() {
    int size;
    MemoryManager mem(1024, AllocationStrategy:: WORST_FIT);
    CacheSystem cache(2, 4);

    std::string command;

    std::cout << "Memory Simulator Started\n";

    while (true) {
        std::cout << "\n> ";
        std::cin >> command;

        if (command == "malloc") {
            int size;
            std::cin >> size;
            int id = mem.malloc(size);
            if (id == -1) {
                std::cout << "Allocation failed\n";
            } else {
                std::cout << "Allocated block id=" << id << "\n";
            }
        }
        else if (command == "free") {
            int id;
            std::cin >> id;
            mem.freeBlock(id);
        }
        else if (command == "dump") {
            mem.dump();
        }
        else if (command == "stats") {
            std::cout << "\nMemory Statistics:\n";
            std::cout << "Used Memory: " << mem.getUsedMemory() << "\n";
            std::cout << "Free Memory: " << mem.getFreeMemory() << "\n";
            std::cout << "Internal Fragmentation: 0%\n";
            std::cout << "External Fragmentation: "
                      << mem.getExternalFragmentation() * 100 << "%\n";
            int total = mem.allocSuccess + mem.allocFailure;
            if (total > 0) {
                std::cout << "Allocation Success Rate: "
              << (double)mem.allocSuccess / total * 100 << "%\n";

            std::cout << "Memory Utilization: "
          << (double)mem.getUsedMemory() / size * 100 << "%\n";

}



            cache.printStats();
            std::cout << "Total Cache Access Time: "
          << cache.totalAccessTime << " cycles\n";

        }
        else if (command == "access") {
            int address;
            std::cin >> address;
            cache.access(address);
        }

        else if (command == "init") {
    std::string sub;
    std::cin >> sub;

    if (sub == "memory") {
        std::cin >> size;
        mem.initMemory(size);
        std::cout << "Memory initialized to " << size << "\n";
    }
}

else if (command == "set") {
    std::string type;
    std::cin >> type;

    if (type == "allocator") {
        std::string alg;
        std::cin >> alg;

        if (alg == "first_fit") {
            mem.setStrategy(AllocationStrategy::FIRST_FIT);
            std::cout << "Allocator set to First Fit\n";
        }
        else if (alg == "best_fit") {
            mem.setStrategy(AllocationStrategy::BEST_FIT);
            std::cout << "Allocator set to Best Fit\n";
        }
        else if (alg == "worst_fit") {
            mem.setStrategy(AllocationStrategy::WORST_FIT);
            std::cout << "Allocator set to Worst Fit\n";
        }
        else {
            std::cout << "Unknown allocation strategy\n";
        }
    }
}



        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
