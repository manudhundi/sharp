/*************************************************************************
 *  Compilation:  g++ -o taxicab taxicab.cpp
 *  Execution:    ./taxicab N (for example ./taxicab 100)
 * 
 *  Find all nontrivial integer solutions to a^3 + b^3 = c^3 + d^3 where
 *  a, b, c, and d are between 0 and N. By nontrivial, we mean
 *  a <= b, c <= d, and (a, b) != (c, d).
 *
 *  C++ implementation of http://algs4.cs.princeton.edu/24pq/Taxicab.java.html
 *
 *  % ./taxicab 11
 *
 *  % ./taxicab 12
 *  TAXI CAB NUMBERS
 *  1729 = 1^3 + 12^3
 *  1729 = 9^3 + 10^3
 *
 *   % ./taxicab 20
 *  TAXI CAB NUMBERS
 *  1729 = 1^3 + 12^3
 *  1729 = 9^3 + 10^3
 *  
 *  4104 = 9^3 + 15^3
 *  4104 = 2^3 + 16^3
 *
 *************************************************************************/
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

class taxi_cab {
private:
	long int sum;
	int i;
	int j;
public:
	/* ctor */
	taxi_cab(int i, int j);
	/* dtor */
	~taxi_cab();
	/* assignment operator */
	taxi_cab& operator=(const taxi_cab &rhs);
	int get_sum() { return sum;}
	int get_i() { return i;}
	int get_j() { return j;}
	/* for the functor to access private variables */
	friend class taxi_cab_cmp;
};

/* ctor */
taxi_cab::taxi_cab(int i, int j): i(i), j(j)
{
	sum = (i*i*i) + (j*j*j);
}

/* dtor */
taxi_cab::~taxi_cab()
{
}

/* assignment operator */
taxi_cab& taxi_cab::operator=(const taxi_cab &rhs)
{
	if(this == &rhs)
		return *this;
	
	sum = rhs.sum;
	i = rhs.i;
	j = rhs.j;
	return *this;
}

/* functor class: passed to STL queue */
class taxi_cab_cmp
{
public:
	bool operator()(taxi_cab a, taxi_cab b)
	{
		return a.sum > b.sum;
	}
};

int main (int argc, char* argv[])
{
	int n = 20; /* Default: Print atleast one taxi cab number */

	/* Get the input from cmd line */
	if (argc >= 2)
		n = atoi(argv[1]);

	cout << "TAXI CAB NUMBERS" << endl;

	/* Use a min Priority Queue */
	priority_queue<taxi_cab, vector<taxi_cab>, taxi_cab_cmp> pq;

	/* Initialize the pq with i^3 + i^3 */
	for (int i = 1; i < n; i++)
	{
		pq.push(taxi_cab(i,i));
	}

	/* Check for sums in ascending order */
	int found = 1;
	taxi_cab prev(0, 0); /* sentinel */

	while (!pq.empty())
	{
		/* Get (pop) the min pq element */
		taxi_cab curr = pq.top();
		pq.pop();

		/* If same as prev sum */
		if (prev.get_sum() == curr.get_sum()) {
			found++;
			/* To avoid repitition of the print of the already found */
            if (found == 2) {
				cout << prev.get_sum() << " = " << prev.get_i() << "^3 + " <<  prev.get_j() << "^3" << endl;
			}
			cout << curr.get_sum() << " = " << curr.get_i() << "^3 + " <<  curr.get_j() << "^3" << endl;
		} else {
				if (found > 1) cout << endl;
                found = 1;
		}
		prev = curr;

		if (curr.get_j() < n)
		{
			pq.push(taxi_cab(curr.get_i(), curr.get_j() + 1));
		}
	}
}