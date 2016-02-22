/*
 *  MemoryChunk.h
 *
 *  Created by kevin calderone on 2/6/10.
 *
 */

#ifndef MemoryChunk_H_
#define MemoryChunk_H_

#include "MemoryAllocator.h"
class MemoryAllocator;

class MemoryChunk{
public:
	
	MemoryChunk(MemoryAllocator* _parent, char* _dataBegin, unsigned int _size, unsigned int _memoryIndex);
	~MemoryChunk();
	
	void resize(unsigned int newSize);
	
	inline char* getDataBegin(){ return dataBegin; }
	inline char* getDataEnd(){ return dataBegin + size; }
	inline unsigned int getMemoryIndex(){ return memoryIndex; }
	inline unsigned int getSize(){ return size; }	
		
private:
	friend class MemoryAllocator;
	
	void moveDataBegin(unsigned int distance);
	
	unsigned int memoryIndex;
	char* dataBegin;
	unsigned int size;
	
	MemoryAllocator* parent;
};


#endif
