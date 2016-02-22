/*
 *  MemoryAllocator.cpp
 *
 *  Created by Kevin Calderone on 10/3/09.
 *
 */

#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator(unsigned int _size)
	:	size(_size), fragmented(0)
{		 
	dataBegin = (char*)malloc(size);
}


MemoryAllocator::~MemoryAllocator(){

	while( blocks.size() ){
		delete blocks.back();
		printf("MemoryAllocator::~MemoryAllocator: Block in use being deallocated.");
	}
	
	free(dataBegin);				

}

void MemoryAllocator::clear(){

	while( blocks.size() ){
		delete blocks.back();
		blocks.pop_back();
	}	
	
}

void MemoryAllocator::setMemory(void* memory, unsigned int memorySize){
	
	reserve(memorySize);
	
	memcpy(dataBegin,memory,memorySize);
	
}

unsigned int MemoryAllocator::usedMemory(){

	char* usedDataEnd = NULL;
	
	if( blocks.size() != 0 )
		usedDataEnd = blocks.back()->getDataEnd();
	else
		usedDataEnd = dataBegin;
	
	return usedDataEnd - dataBegin;	
	
}

unsigned int MemoryAllocator::unusedMemory(){
	
	char* unusedDataBegin = NULL;
	
	if( blocks.size() != 0 )
		unusedDataBegin = blocks.back()->getDataEnd();
	else
		unusedDataBegin = dataBegin;
	
	return (dataBegin + size) - unusedDataBegin;
}

void MemoryAllocator::reserve(unsigned int reserveSize){

	unsigned int memoryLeft = unusedMemory();

	if( reserveSize <= memoryLeft )
		return;

	// try to defrag, or else allocate more memory
	defrag();
	memoryLeft = unusedMemory();
	
	if( reserveSize > memoryLeft ){
		unsigned int increasedSize = size + (reserveSize - memoryLeft);		
		resize( increasedSize + ALLOC_EXTRA_SIZE );						
	}
		
}

MemoryChunk* MemoryAllocator::newBlock(unsigned int blockSize){
	
	char* newDataBegin = NULL;
	
	reserve( blockSize );
	
	if( blocks.size() != 0 )
		newDataBegin = blocks.back()->getDataEnd();
	else
		newDataBegin = dataBegin;
	
	MemoryChunk* newBlock = new MemoryChunk(this,newDataBegin,blockSize,newDataBegin-dataBegin);
	
	blocks.push_back( newBlock );
	
	return newBlock;
}

MemoryChunk* MemoryAllocator::getBlock(unsigned int index){
	
	if( blocks.size() < index + 1 )
		return NULL;
	
	return blocks[index];
}

void MemoryAllocator::deleteBlock(MemoryChunk* block){

	for( std::vector< MemoryChunk* >::iterator iter = blocks.begin(); iter != blocks.end(); ++iter )
		if( *iter == block ){
			blocks.erase( iter );
			fragmented = 1;
			return;
		}
	
	printf("MemoryAllocator::deleteBlock: Block not found.");
}

void MemoryAllocator::resizeBlock(MemoryChunk* block, unsigned int newSize){
	
	unsigned int blockToResize = 0;
	
	while ( blocks[ blockToResize++ ] != block ) 
		if( blockToResize == blocks.size() ){
			printf("MemoryAllocator::resizeBlock: Block not found.");
			return;
		}

	// make sure there is enough space for the resize
	if( newSize > blocks[ blockToResize ]->getSize() )
		reserve( newSize - blocks[ blockToResize ]->getSize() );
	
	blocks[ blockToResize ]->size = newSize;
	
	// if there are blocks after it, move them
	if( blockToResize != blocks.size()-1 )
		moveBlocks(blockToResize+1, blocks.size()-1, blocks[ blockToResize ]->getDataEnd());
	
}

void MemoryAllocator::resize(unsigned int newSize){
	
	char* oldDataBegin = dataBegin;
	char* newDataBegin = (char*)realloc(dataBegin,newSize);

	if( newDataBegin != NULL ){
		dataBegin = newDataBegin;
		size = newSize;
		
		int moveDistance = newDataBegin - oldDataBegin;
		
		if( moveDistance != 0 )
			for( std::vector< MemoryChunk* >::iterator iter = blocks.begin(); iter != blocks.end(); ++iter )
				(*iter)->dataBegin += moveDistance;
		
	}
	else
		printf("MemoryAllocator::resize: Failed to allocate memory.");

}

void MemoryAllocator::defrag(){
	
	if( !fragmented || !blocks.size() ){
		fragmented = 0;
		return;
	}
	
	char* lastDataEnd = dataBegin;
	unsigned int firstToMove = 0;
	unsigned int lastToMove = 0;
	
	unsigned int iter = 0;
	
	while( iter != blocks.size() ){
	
		if( blocks[ iter ]->getDataBegin() == lastDataEnd ){
			lastDataEnd = blocks[ iter ]->getDataEnd();
			++iter;
			continue;
		}
		
		firstToMove = iter;
		
		do{
			lastToMove = iter++;
		} while( iter != blocks.size() && blocks[ iter ]->getDataBegin() == blocks[ lastToMove ]->getDataEnd() );
		
		moveBlocks(firstToMove,lastToMove,lastDataEnd);
		
		lastDataEnd = blocks[ lastToMove ]->getDataEnd();
		
	}
	
	fragmented = 0;
}

void MemoryAllocator::moveBlocks(unsigned int firstToMove, unsigned int lastToMove, char* destination){

	unsigned int sizeToMove = blocks[ lastToMove ]->getDataEnd() - blocks[ firstToMove ]->getDataBegin();
	int distanceToMove = destination - blocks[ firstToMove ]->getDataBegin();
	
	// move the memory, they may overlap
	memmove(destination, blocks[ firstToMove ]->getDataBegin(), sizeToMove);	
		
	// fix the data pointers in the block
	for( unsigned int moveIter = firstToMove; moveIter != lastToMove+1; ++moveIter )
		blocks[ moveIter ]->moveDataBegin( distanceToMove );
	
}
