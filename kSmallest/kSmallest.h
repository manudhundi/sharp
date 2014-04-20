template <class T>
class kSmallest
{
public:
	/* ctor */
	kSmallest();
	/* dtor */
	~kSmallest();
	/*********************************************************************
	 * getKSmallest: API to client.  
	 * Input: 
	 *       dest : destination array to copy k smallest objects
	 *       src  : src array of objects; srcLen: src array length
	 *       compareFunc : function to compare 2 objects of type T
	 * Return:
	 *       0 on success; negative on failure
	/*********************************************************************/
	int getKSmallest(T *dest, T *src, unsigned int srcLen,
					 unsigned int k, int (*compareFunc) (T *a, T *b));
private:
	/* Uses quick sort kind of partitioning to get k smallest */
	unsigned int partition(T *src, unsigned int size,
						   int (*compareFunc) (T *a, T *b));
	/* Swap 2 objects of type T */
	void swap(T *a, T *b);
};