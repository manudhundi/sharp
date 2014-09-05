#include <cstdlib>
#include "qMemNode.h"
#include "qMemAllocator.h"
#include "qMemNodeMgr.h"
#include "qMemSelectNodeMgr.h"
using namespace std;

/* The application using this can pass size which is used to
   get memory in chunks (of 'size') from the heap. This is also
   the max size that can be allocated */
qMemAlloc::qMemAlloc (int size) : chunkSize(size)
{
	/* First node */
	qMemNode *node = new qMemNode(chunkSize);
	qMemSelectNodeMgr selectNodeMgr;
	/* Get node mgr */
	nodeMgr = selectNodeMgr.getNodeMgr();
	/* Add the first node to the node mgr */
	nodeMgr->addNode(node);
}

/* dtor */
qMemAlloc::~qMemAlloc ()
{
	delete nodeMgr;
}

/* Called to get memory (malloc) */
uint8* qMemAlloc::getMemory (int bytes)
{
	/* Check for invalid input */
	if (bytes > chunkSize) { 
		return NULL;
	}

	/* Get a qMemNode from nodeMgr */
	qMemNode *currChunk = nodeMgr->getAvailableNode(bytes);
	/* Check if we need a new chunk */
	if ((!currChunk) || 
		(bytes > currChunk->getAvailableMemory())) { /* We need a new chunk */
		qMemNode *node = new qMemNode(chunkSize);
		/* Add the first node to the node mgr */
		nodeMgr->addNode(node);
		/* Need this for book keeping at nodeMgr */
		currChunk = nodeMgr->getAvailableNode(bytes); 
	}

	/* has to posses enough memory this time */
	/* ASSERT (bytes < currChunk->getAvailableMemory()) */
	return (currChunk->getMemoryFromNode(bytes));
}