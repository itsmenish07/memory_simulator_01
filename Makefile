CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/main.cpp \
      src/allocator/MemoryBlock.cpp \
      src/allocator/MemoryManager.cpp \
      src/cache/CacheLevel.cpp\
	  src/cache/CacheSystem.cpp

TARGET = memsim

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f memsim
