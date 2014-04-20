#include <iostream>
#include <cstdlib>
#include <algorithm>    // std::random_shuffle
using namespace std;

#include "kSmallest.h"

/* http://www.cplusplus.com/forum/general/14162/ */
template class kSmallest<int>;
template class kSmallest<double>;
template class kSmallest<float>;

template <class T>
kSmallest<T>::kSmallest()
{
	/* ctor */
}

template <class T>
kSmallest<T>::~kSmallest()
{
	/* dtor */
}

/**************************************************************************
 * getKSmallest: API to client.  
 * Input: 
 *       dest : destination array to copy k smallest objects
 *       src  : src array of objects; srcLen: src array length
 *       compareFunc : function to compare 2 objects of type T
 * Return:
 *       0 on success; negative on failure
/**************************************************************************/
template <class T>
int kSmallest<T>::getKSmallest(T *dest, T *src, unsigned int srcLen,
							unsigned int k, int (*compareFunc) (T *a, T *b))
{
	T *pSrc = src;
	unsigned int uiRemLen = srcLen;
	unsigned int uiKRem = k;
	unsigned int uiRetIdx = 0;

    /* Validate Input */
	if ((!dest) || (!src) || (!compareFunc))
	{
		return -1;
	}

	if (!k)
		return 0; /* we are done */

	/* Randomize the input to make we do not hit worst case runtime like
	  in Q sort. Note random_shuffle should be of O(n) */
	std::random_shuffle(pSrc, pSrc + (srcLen - 1));

	/* Partition the src array till you get k largest */
	while (1) 
	{
		uiRetIdx = partition(pSrc, uiRemLen, compareFunc);
		if ((uiKRem == uiRetIdx) || (uiKRem == uiRetIdx + 1)) {
			/* we have found k smallest elements */
			memcpy(dest, src, k * sizeof(T));
			break;
		}
		if (uiRetIdx > uiKRem) { /* Search left only */
			/* Cut short the search only upto the return index */
			uiRemLen = uiRetIdx;
			continue;
		}
		else { /* Search right only */
			/* Search for elements only after return index */
			uiKRem -= (uiRetIdx + 1);
			pSrc = pSrc + (uiRetIdx + 1);
			uiRemLen -=  (uiRetIdx + 1);
			continue;
		}
	}
	return 0;
}

/**************************************************************************
 * getKSmallest: Uses quick sort kind of partitioning to get k smallest
 * Input: 
 *       src  : src array of objects; size: src array length
 *       compareFunc : function to compare 2 objects of type T
 * Return:
 *       index of the partition pivot
 * Note: Assumes size passed is >= 0
 *       The src array is randomly shuffled
/**************************************************************************/
template <class T>
unsigned int kSmallest<T>::partition(T *src, unsigned int size,
								  int (*compareFunc) (T *a, T *b))
{
	unsigned int i = 1, j = (size - 1);
	/* Choose first element as pivot.
	   Since src is randomly shuffled, choosing first element is as good as
	   picking a random pivot */
	T pivot = src[0];

	/* Standard partition logic */
	while (1) {
		while (compareFunc(&src[i], &pivot) <= 0) {
			i++;
			if (i >= size - 1) {
				break;
			}
		}
		while (compareFunc(&src[j], &pivot) > 0) {
			j--;
			if (j == 0) {
				break;
			}
		}

		if (i >= j) {/* Indices crossed */
			break;
		}
		swap(src + i, src + j);
	}

	swap(src, src + j);
	return j;
}

/**************************************************************************
 * swap: Swap 2 objects of type T
/**************************************************************************/
template <class T>
void kSmallest<T>::swap(T *a, T *b)
{
	if ((!a) || (!b))
		return;

	T temp = *a;
	memcpy(a, b, sizeof(T));
	memcpy(b, &temp, sizeof(T));
	return;
}
