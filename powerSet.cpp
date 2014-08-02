/*****************************************************************************
 * PowerSet class prints the power set of a given array 
 * Ex: If the input array is [2 3 4] then the power set is
 *     [], [2], [3], [4], [2, 3], [2, 4], [3, 4], [2, 3, 4]
 * Given an array of length N, there are 2^N elements in a power set
 * (because every element has 2 choices, either it is present or not)
 *
*****************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class PowerSet {
public:
	void printPowerSet(vector<int> &a, int length)
	{
		int bitMask = 0;
		int numPowerSet = 1 << length;
		for (int i = 0; i < numPowerSet; i++) {
			cout << "[";
			bitMask = i;
			for (int j = 0; j < length; j++) {
				if (!(bitMask >> j))
					break; /* Stop here we don't have to go till length */
				if ((bitMask >> j) & 0x1) {
					cout << a[j] << ",";
				}
			}
			cout << "]" << endl;
		}
	}
};

#define LEN 3
int main()
{
	vector <int> a;
	for (int i = 0; i < LEN; i++) {
		a.push_back(i+3);
	}
	
	PowerSet p;
	p.printPowerSet(a, LEN);
	return 0;
}
