/*************************************************************************
 *  Compilation:  g++ -o randomContractionAlgo randomContractionAlgo.cpp
 *  Execution:    ./randomContractionAlgo
 * 
 *  Find a min cut in a graph
 *
 *  C++ implementation of random Contraction Algo by karger
 *  to solve the minimun cut problem in a graph
 *
 *  Adjacency list of the graph given in a file "kargerMinCut.txt"
 *
 *  This is also the solution to the assigment 3 of Algorithms course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>

using namespace std;

#define INPUT_FILE "kargerMinCut.txt"
#define MAX_ITERATIONS 50
#define INF_SENTIINEL 2^31

/* Read input (adjacency list) from a file */
int readInput(vector<vector<int> > &adjList)
{
	ifstream inpFile(INPUT_FILE);
	string line;
	int i;
	char *cstr = NULL;
	char delims[] = "	";

	if (!inpFile.is_open()) {
		cout << "Input could not be read" << endl;
		return -1;
	}
	/* Read the file line by line */
	while (getline(inpFile, line)) {
		vector<int> *intVec = new vector<int>[1];
		/* Tokenize the line */
		cstr = new char[line.length() + 1];
		strncpy(cstr, line.c_str(), line.length());
		char *tok = strtok(cstr, delims);
		while (tok) {
			i = atoi(tok);
			intVec->push_back(i);
			tok = strtok(NULL, delims);
		}
		/* Due to input formatting there is a zero appended in the end,
		   hence pop it out */
		intVec->pop_back();
		/* Free cstr */
		delete []cstr;
		/* Push the vector into vector of vectors */
		adjList.push_back(*intVec);
	}
	return 0;
}

/* Function to merge a node with another */ 
int mergeNode(vector<vector<int> > &adjList,
              unsigned int posu,
              unsigned int posuv)
{
	int u,v, atPosV, posv = -1;

	u = adjList.at(posu).front();
	v = adjList.at(posu).at(posuv);

	/* find position of v */
	for (unsigned int i = 0; i < adjList.size(); i++)
	{
		if (adjList.at(i).front() == v) {
			posv = i;
			break;
		}
	}
	/* If valid position of v is not found (due to erroneous input) */
	if (posv == -1) {
		cout << v << " " << posuv << " " << posu << endl;
		return -1;
	}
	/* We cannot have same u and v. Hence go to next or previous element for v */
	if (posu == posv) {
		if (posu == adjList.size() - 1) {
			posv = posu - 1;
			v = adjList.at(posv).front();
		} else {
			posv = posu + 1;
			v = adjList.at(posv).front();
		}
	}

	/* Merge v into u */
	/* 1) Add v into u and delete self loop edges */
	for (unsigned int i = 1; i < adjList.at(posu).size(); i++)
	{
	  /* Deleting self loops */
		if (adjList.at(posu).at(i) == v) {
			adjList.at(posu).at(i) = adjList.at(posu).back();
			adjList.at(posu).pop_back();
			/* Since the last element can cause a self loop we must check again */
			i--;
		}
	}
	for (unsigned int i = 1; i < adjList.at(posv).size(); i++)
	{
	  /* Adding edges of v to u */
		atPosV = adjList.at(posv).at(i);
		if (atPosV == u) { /* Avoiding any self loops */
			continue;
		}
		adjList.at(posu).push_back(atPosV);
	}

	/* 2. Delete node v */
	adjList.at(posv) = adjList.back();
	adjList.pop_back();

	/* 3. Replace all v in the adjacancy list by u */
	for (unsigned int i = 0; i < adjList.size(); i++)
	{
		for (unsigned int j = 1; j < adjList.at(i).size(); j++)
		{
			if (adjList.at(i).at(j) == v) {
				adjList.at(i).at(j) = u;
			}
		}
	}
	return 0;
}

/* karger algorithm to find min cut.
   Note: The algo changes the adjList passed */
int karger(vector<vector<int> > &adjList)
{
	unsigned int posu, posuv;
  
	srand (time(NULL));

	while (2 < adjList.size()) { /* while there are more than 2 vertices */
		/* Pick an edge at random */
		/* First find first vertex position */
		posu = rand() %  (adjList.size());
		/* Pick another vertex position from the vector at uth position in the
		   adjList (pick an edge from u) */
		posuv = (rand() % (adjList.at(posu).size() - 1)) + 1;
		
		/* Merge the nodes picked randomly */
		mergeNode(adjList, posu, posuv);
	}

  /* If the algorithm has run correctly then the below check should be true */
	if (adjList.front().size() == adjList.back().size()) {
		return (adjList.front().size() - 1);
	}
	return -1;
}

int main(void)
{
	int minCuts = 0;
	unsigned int minMinCuts = INF_SENTIINEL;

	cout << "contraction algo" << endl;

	/* Vector to store the adjacency list */
	vector<vector<int> > adjList;
	vector<vector<int> > adjList1;

	/* Fill the adjList from input file */
	if (readInput(adjList)) {
		exit(1);
	}
	/* Make copy of the list since we must run it for more than one iteration */
	adjList1 = adjList;

	cout << adjList.size() << endl;

	/* Run the karger algorithm */
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		minCuts = karger(adjList1);
		if (minCuts <= 0) {
		  cout << "karger algo falied" << endl;
		  exit(1);
		}
		cout << "Iteration " << i << ": MinCuts " << minCuts << endl;
		/* Store the minimum from all iterations */
		if (minCuts < minMinCuts) {
		  minMinCuts = minCuts;
		}
		sleep(1);
		adjList1 = adjList;
	}

	cout << "Min Cuts from karger algo is " << minMinCuts << endl;
}
