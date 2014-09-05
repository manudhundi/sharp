#include <cstdlib>
#include "qMemNode.h"
using namespace std;

/********************************************************************
 * qMemNode is a chunk of memory allocated by qMemAlloc. Until all
 * the memory in this chunk is used, qMemNode can be called to get
 * memory. It returns NULL if asked for memory size more than it can
 * accomodate.
 *******************************************************************/
qMemNode::qMemNode (int size)
{
	/* Get memory from heap */
	startPtr = new uint8[size];
	currPtr = startPtr;
	remSize = size;
}

qMemNode::~qMemNode ()
{
	/* Delete the memory */
	delete [] startPtr;
}

uint8* qMemNode::getMemoryFromNode (int size)
{
	/* Check if the memory available in the chunk is enough */
	if (size > remSize) {
		return NULL;
	}
	/* Decrement available size in the chunk */
	remSize -= size;
	currPtr += size;
	return (currPtr - size);
}

int qMemNode::getAvailableMemory(void)
{
	return remSize;
}