#include <map>
#include "qMemTypes.h"
#include "qMemNode.h"
#include "qMemNodeMgr.h"
using namespace std;

#ifndef __Q_MEM_NODE_MGR_SQUEEZE__
#define __Q_MEM_NODE_MGR_SQUEEZE__

/********************************************************************.
 * qMemNodeMgrSqueeze is a concrete class for the abstract class qMemNodeMgr
 * qMemNodeMgrSqueeze stores a map (STL map, that is, an RB tree)
 * of all qMemNodes and selects the one with the memory size that
 * can just satisfy the demand for memory. If not, it throws
 * out of memory
 *******************************************************************/
class qMemNodeMgrSqueeze: public qMemNodeMgr {
public:
	qMemNodeMgrSqueeze();
	~qMemNodeMgrSqueeze();
	qMemNode* getAvailableNode(int bytes);
	int addNode(qMemNode* node);
private:
	multimap <int, qMemNode*> nodesMap;
};

#endif /* __Q_MEM_NODE_MGR_SQUEEZE__ */