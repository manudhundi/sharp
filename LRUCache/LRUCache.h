#include <list>
#include <map>
using namespace std;

/* This class holds the value to be stored in the LRU cache */
class value {
public:
    value(void* val) {this->val = val;}
    ~value() {}
    void* get(void) {return (this->val);}
private:
    /* Remote obj ptr where value is stored */
    void* val;
};

/* Node is stored in the list needed to maintain LRU Cache 
   This class can be accessed only by class LRUCache */
class Node {
private:
    /* Private ctor */
    Node(int key, value& val): key(key), val(val) {}
    int key;
    value &val;
    friend class LRUCache;
};

/* Map (hashmap) in LRUCache class */
typedef map<int, list<Node*>::iterator> lruMap;

/* Class that implements LRU cache */
class LRUCache {
public:
    LRUCache(int size);
    ~LRUCache();
    /* Add an element with key and val to cache */
    void addElement(int key, value& val);
    /* Retrieve an element with a particular key */
    value* getElement(int key);
    /* Print all elements in the cache */
    void printCache(void);
private:
    /* Max size of cache */
    int maxSize;
    /* Curr cache size */
    int currSize;
    /* List of elements in cache in temporal (causal) order */
    list<Node*> LRUList;
    /* Maps keys to position in list for quick (almost O(1)) access */
    lruMap LRUMap;
};
