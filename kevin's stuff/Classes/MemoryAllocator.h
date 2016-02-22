/*
 *  MemoryAllocator.h
 *
 *  Created by Kevin Calderone on 10/3/09.
 *
 */

#ifndef MEMORYALLOCATOR_H_
#define MEMORYALLOCATOR_H_

#include <vector>

#include "MemoryChunk.h"
class MemoryChunk;

class MemoryAllocator{
public:
	
	MemoryAllocator(unsigned int _size);													
	~MemoryAllocator();
	
	MemoryChunk* newBlock(unsigned int blockSize);
	MemoryChunk* getBlock(unsigned int index);
	void deleteBlock(MemoryChunk* block);
	void resizeBlock(MemoryChunk* block, unsigned int newSize);
	void defrag();
	
	void clear();
	void setMemory(void* memory, unsigned int memorySize);
	void reserve(unsigned int reserveSize);
	unsigned int usedMemory();
	
	inline char* getDataBegin(){ return dataBegin; }
	inline char* getDataEnd(){ return dataBegin+size; }
	inline unsigned int getSize(){ return size; }	
	
private:
	
	void resize(unsigned int newSize);
	unsigned int unusedMemory();
	
	void moveBlocks(unsigned int firstToMove, unsigned int lastToMove, char* destination);	// requires non-fragmented blocks
		
	char* dataBegin;
	unsigned int size;
	
	std::vector< MemoryChunk* > blocks;														// stored in order of memory
	bool fragmented;
	
	static const unsigned int ALLOC_EXTRA_SIZE = 1024;										// Extra alloced when ran out of memory, prevent furure alloc
	
};

#endif
