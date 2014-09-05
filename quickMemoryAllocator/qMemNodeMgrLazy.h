#include <vector>
#include "qMemTypes.h"
#include "qMemNode.h"
#include "qMemNodeMgr.h"
using namespace std;

#ifndef __Q_MEM_NODE_MGR_LAZY__
#define __Q_MEM_NODE_MGR_LAZY__

/********************************************************************.
 * qMemNodeMgrLazy is a concrete class for the abstract class qMemNodeMgr
 * It just gives memory from the current qMemNode if available
 * or else says out of memory. More like default, simple class.
 *******************************************************************/
class qMemNodeMgrLazy: public qMemNodeMgr {
public:
	qMemNodeMgrLazy();
	~qMemNodeMgrLazy();
	qMemNode* getAvailableNode(int bytes);
	int addNode(qMemNode* node);
private:
	/* Store a vector of nodes in use. 
	   Need to store all nodes because we need to free memory
	   at the end of application */
	vector <qMemNode*> nodes;
};

#endif /* __Q_MEM_NODE_MGR_LAZY__ */