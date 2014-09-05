#include "qMemNodeMgrSqueeze.h"

qMemNodeMgrSqueeze::qMemNodeMgrSqueeze()
{
}

qMemNodeMgrSqueeze::~qMemNodeMgrSqueeze()
{
	multimap<int, qMemNode*>::iterator it;
	/* Delete memory allocated by all the chunks */
	for (it = nodesMap.begin(); it != nodesMap.end(); it++) {
		delete it->second;
	}
	nodesMap.clear();
}

qMemNode* qMemNodeMgrSqueeze::getAvailableNode (int bytes)
{
	qMemNode *pNode = NULL;
	if (nodesMap.count(bytes)) { /* There is a memNode with exact num of bytes */
		pNode = nodesMap.find(bytes)->second;
		/* Key in the map has changed, so delete and add back the updated one */
		nodesMap.erase(nodesMap.find(bytes));
		/* Still need this to free all memory */
		nodesMap.insert(pair<int, qMemNode*>(0, pNode));
		return pNode;
	} else {
		if (nodesMap.upper_bound(bytes) == nodesMap.end()) {
			/* No mem node in the map has enough memory */
			return NULL;
		} else {
			/* Memnode to return */
			pNode = nodesMap.upper_bound(bytes)->second;
			int remNodeMem = (nodesMap.upper_bound(bytes)->first) - bytes;
			/* Key in the map has changed, so delete and add back the updated one */
			nodesMap.erase(nodesMap.upper_bound(bytes)->first);
			nodesMap.insert(pair<int, qMemNode*>(remNodeMem, pNode));
			return pNode;
		}
	}
}

int qMemNodeMgrSqueeze::addNode (qMemNode *node)
{
	int nodeSize = node->getAvailableMemory();
	/* ASSERT nodesMap.count(nodeSize) */
	nodesMap.insert(pair<int, qMemNode*>(nodeSize, node));
	return 0; /* Success */
}