#include "qMemSelectNodeMgr.h"
#include "qMemNodeMgrLazy.h"
#include "qMemNodeMgrSqueeze.h"

NodeMgrEnum qMemSelectNodeMgr::eNodeMgr = eLAZY;

qMemNodeMgr* qMemSelectNodeMgr::getNodeMgr (void)
{
	if (eNodeMgr == eSQUEEZE) {
		qMemNodeMgrSqueeze *pNodeMgr = new qMemNodeMgrSqueeze();
		return ((qMemNodeMgrSqueeze*)pNodeMgr);
	}
	else { /* Default case */
		qMemNodeMgrLazy *pNodeMgr = new qMemNodeMgrLazy();
		return ((qMemNodeMgr*)pNodeMgr);
	}
}

void qMemSelectNodeMgr::setNodeMgr(NodeMgrEnum eNodeNgr)
{
	this->eNodeMgr = eNodeNgr;
}