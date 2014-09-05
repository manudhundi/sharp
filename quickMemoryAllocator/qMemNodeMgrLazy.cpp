#include "qMemNodeMgrLazy.h"

qMemNodeMgrLazy::qMemNodeMgrLazy()
{
}

qMemNodeMgrLazy::~qMemNodeMgrLazy()
{
	/* Delete memory allocated by all the chunks */
	for (unsigned int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
	nodes.clear();
}

qMemNode* qMemNodeMgrLazy::getAvailableNode(int bytes)
{
	vector <qMemNode*>::reverse_iterator it = nodes.rbegin();
	return *it;
}
int qMemNodeMgrLazy::addNode(qMemNode *node)
{
	nodes.push_back(node);
	return 0; /* Success */
}