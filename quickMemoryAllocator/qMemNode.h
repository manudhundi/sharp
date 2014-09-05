#include "qMemTypes.h"

/********************************************************************
 * qMemNode is a chunk of memory allocated by qMemAlloc. Until all
 * the memory in this chunk is used, qMemNode can be called to get
 * memory. It returns NULL if asked for memory size more than it can
 * accomodate.
 *******************************************************************/
#ifndef __Q_MEM_NODE__
#define __Q_MEM_NODE__
class qMemNode {
public:
	qMemNode (int size);
	~qMemNode();
	uint8* getMemoryFromNode (int size);
	int getAvailableMemory(void);
private:
	uint8* startPtr;
	uint8* currPtr;
	int remSize;
};
#endif /* __Q_MEM_NODE__ */