/*************************************************************************
 *  Compilation:  g++ -o 4sum 4sum.cpp
 *  Execution:    ./4sum
 * 
 *  In a given input array find integers a,b,c,d such that 
 *  a + b = c + d
 *
 *  C++ implementation using STL map
 *  Order of operation: O(n^2. lg n)
 *          STL in cpp implements map as a Balanced Binary Tree where
 *          accessing an element is of the order O(lg n). Hence the order
 *          of operation is O(n^2. lg n). If map is replaced by
 *          standard hash_map where accessing an element is of the order
 *          O(1), then the below code can run in O(n^2)
 *  Memory Usage: O(n^2) (to build the map)
 *
 *************************************************************************/
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

class intPair {
public:
	intPair(int i, int j): i(i), j(j) {}
	~intPair() {}
	int getI() {return i;}
	int getJ() {return j;}
private:
	int i;
	int j;
};

int main()
{
	int intArray[] = {4, 5, -1, 1, -2, 3};
	int arrayLen = sizeof(intArray)/sizeof(int);
	multimap<int,intPair, classcomp> sumMap;

	/* Form a map where key is the sum of pair of integers in the intArray 
		and value is the pair */
	for (int i = 0; i < arrayLen; i++)
	{
		for (int j = i+1; j < arrayLen; j++)
		{
			intPair* val = new intPair(intArray[i], intArray[j]);
			sumMap.insert(pair<int, intPair>((intArray[i] + intArray[j]), *val));
		}
	}

	/* Now run through the map to find if there are same keys */
	multimap<int, intPair, classcomp>::iterator itMap;
	for (itMap = sumMap.begin(); itMap != sumMap.end(); itMap++)
	{
		if (sumMap.count(itMap->first) == 1)
		{
			continue;
		}
		pair<multimap<int, intPair, classcomp>::iterator, multimap<int, intPair, classcomp>::iterator>keyRange;
		multimap<int, intPair, classcomp>::iterator itKeyRange;
		/* Get the range in map where the keys are equal */
		keyRange = sumMap.equal_range(itMap->first);
		for (itKeyRange = keyRange.first; itKeyRange != keyRange.second; ++itKeyRange)
		{
			/* Print to stdout */
			if (itKeyRange != keyRange.first) {
				cout << " = ";
			}
			cout << itKeyRange->second.getI() << " + " << itKeyRange->second.getJ();
		}
		cout << endl;
		itMap = itKeyRange;
	}
	return 0;
}
 