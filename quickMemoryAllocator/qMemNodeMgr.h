#include "qMemTypes.h"
#include "qMemNode.h"
using namespace std;

#ifndef __Q_MEM_NODE_MGR__
#define __Q_MEM_NODE_MGR__

/********************************************************************
 * qMemNodeMgr manages the qMemNodes (chunks of memory) that are in
 * use. It is an abstract class that provides api to query for a
 * qMemNode. Based on user selection, qMemNodeMgr morphs into a
 * particular concrete class.
 * Currently 2 concrete classes 1) qMemNodeMgrLazy 2) qMemNodeMgrSqueeze
 * are implemented 
 *******************************************************************/
class qMemNodeMgr {
public:
	virtual ~qMemNodeMgr() {}
	/* Get a qMemNode that has enough memory */
	virtual qMemNode* getAvailableNode(int bytes) = 0;
	/* Record a newly added qMemNode */
	virtual int addNode(qMemNode* node) = 0;
};

#endif /* __Q_MEM_NODE_MGR__ */