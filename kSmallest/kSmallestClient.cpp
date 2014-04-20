#include <iostream>
#include <cstdlib>
#include <algorithm>    // std::random_shuffle
using namespace std;

#include "kSmallest.h"

#define K 20
#define NUM_ELEMENTS 1000

int cmp(int *a, int *b)
{
	if (*a == *b)
		return 0;
	if (*a > *b)
		return 1;
	return -1;
}

int main (void)
{
	int count = 0;
	int test_array[NUM_ELEMENTS];
	int dest_array[K] = {0};
	cout << "kSmallest" << endl;

	for (count = 0; count < NUM_ELEMENTS; count++)
	{
		test_array[count] = count;
	}
	std::random_shuffle(test_array, test_array + (NUM_ELEMENTS - 1));

	kSmallest<int> k;
	k.getKSmallest(dest_array, test_array, NUM_ELEMENTS, K, cmp);

	for (count = 0; count < K; count++)
		printf("%d ", dest_array[count]);

	cout << endl;
	return 0;
}