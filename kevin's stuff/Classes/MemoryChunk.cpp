/*
 *  MemoryBlock.cpp
 *
 *  Created by kevin calderone on 2/6/10.
 *
 */

#include "MemoryChunk.h"

MemoryChunk::MemoryChunk(MemoryAllocator* _parent, char* _dataBegin, unsigned int _size, unsigned int _memoryIndex)
:	parent(_parent), dataBegin(_dataBegin), size(_size), memoryIndex(_memoryIndex)
{
	
}

MemoryChunk::~MemoryChunk(){
	
	parent->deleteBlock(this);
	
}

void MemoryChunk::resize(unsigned int newSize){

	parent->resizeBlock(this,newSize);

}

void MemoryChunk::moveDataBegin(unsigned int distance){
	
	dataBegin += distance;
	memoryIndex += distance;
	
}
