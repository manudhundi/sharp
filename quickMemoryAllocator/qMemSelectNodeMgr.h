#include "qMemNodeMgr.h"

#ifndef __Q_MEM_SELECT_NODE_MGR__
#define __Q_MEM_SELECT_NODE_MGR__

/* Class to select node mgr type */
enum NodeMgrEnum {
	eLAZY,
	eSQUEEZE
};

class qMemSelectNodeMgr {
public:
	qMemNodeMgr* getNodeMgr (void);
	void setNodeMgr (NodeMgrEnum eNodeNgr);
private:
	static NodeMgrEnum eNodeMgr;
};

#endif /* __Q_MEM_SELECT_NODE_MGR__ */