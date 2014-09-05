#include <iostream>
using namespace std;

#include "qMemAllocator.h"
#include "qMemSelectNodeMgr.h"

int main ()
{
	//uint8 *p1, *p2,
	uint8 *p3, *p4, *p5, *p6, *p7, *p8;
	qMemSelectNodeMgr selectNodeMgr;
	int nodeMgrType;
	cout << "Enter node Mgr type:" << endl;
	cout << "1 for lazy mgr" << endl;
	cout << "2 for squeeze mgr" << endl;
	cin >> nodeMgrType;
	if (nodeMgrType == 2) {
		selectNodeMgr.setNodeMgr(eSQUEEZE);
	} else {
		selectNodeMgr.setNodeMgr(eLAZY);
	}
	cout << "Testing Quick Memory Allocator" << endl;
	qMemAlloc allocObj(100);
	//p1 = allocObj.getMemory(5);
	//p2 = allocObj.getMemory(10);
	p3 = allocObj.getMemory(95);
	p4 = allocObj.getMemory(95);
	p5 = allocObj.getMemory(4);
	p6 = allocObj.getMemory(20);
	p7 = allocObj.getMemory(1000);
	p8 = allocObj.getMemory(4);

	//cout << p1 << p2 << p3 << p4 << endl;
}