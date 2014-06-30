/*************************************************************************
 *  Compilation:  g++ -o lruCache LRUCache.cpp
 *  Execution:    ./lruCache
 * 
 *  Implement a LRU cache with O(1) addition, O(1) updation and O(1) deletion
 *
 *  C++ implementation using STL
 *
 *  Note: I am using std::map in C++. Strictly speaking the operations
 *        are O(lg N) because implemention of std:map uses balanced BST. 
 *
 *************************************************************************/
#include <iostream>
#include <list>
#include <map>
#include "LRUCache.h"
using namespace std;

LRUCache::LRUCache(int size) : maxSize(size), currSize(0)
{
}

LRUCache::~LRUCache()
{
    cout << "LRUCache dtor" << endl;
    list<Node*>::iterator it;
    /* Delete all nodes in the list */
    for (it = LRUList.begin(); it != LRUList.end(); ++it) {
        /* Free node */
        delete *it;
    }
    /* Clear the list and map */
    LRUList.clear();
    LRUMap.clear();
}

/* Add an element with key and val to cache */
void LRUCache::addElement(int key, value& val)
{
    lruMap::iterator it;
    /* Check if element is already present */
    if (LRUMap.count(key)) { /* Already present */
        /* Remove the element from the current position in the list */
        it = LRUMap.find(key);
        delete *(it->second);
        LRUList.erase(it->second);
        LRUMap.erase(it);
        this->currSize--; /* Later add it to head of list */
    } else {
        /* If we have hit the maxsize of cache then delete the last element */
        if (currSize == maxSize) {
            LRUMap.erase(LRUList.back()->key);
            delete (LRUList.back());
            LRUList.pop_back();
            this->currSize--;
        }
    }
    Node* node = new Node(key, val);
    /* Add to list head */
    LRUList.push_front(node);
    /* Add the element to the map */
    LRUMap.insert(pair<int, list<Node*>::iterator> (key, LRUList.begin()));
    this->currSize++;
}

value* LRUCache::getElement(int key)
{

    if (LRUMap.count(key)) {
        map<int, list<Node*>::iterator>::iterator it = LRUMap.find(key);
        return (&(*(it->second))->val);
    }
    /* Element not found */
    return NULL;
}

void LRUCache::printCache(void)
{
    cout << "Elements in LRU cache are" << endl;
    list<Node*>::iterator it;
    for (it = LRUList.begin(); it != LRUList.end(); ++it) {
        cout << (*it)->key << endl;
    }
}

/* Sample client test program */
int main()
{
    cout << "LRU cache using cpp STL" << endl;
    LRUCache lru(3);
    
    char val1[] = "val1";
    char val2[] = "val2";
    char val3[] = "val3";
    char val4[] = "val4";
    char val5[] = "val5";
    value e1(val1);
    value e2(val2);
    value e3(val3);
    value e4(val4);
    value e5(val5);
    
    lru.addElement(1, e1);
    lru.addElement(2, e2);
    lru.addElement(3, e3);
    lru.addElement(4, e4);
    lru.addElement(5, e5);
    lru.addElement(3, e3);
    lru.addElement(2, e2);
    lru.addElement(3, e3);
    lru.addElement(3, e3);
    lru.addElement(3, e3);

    lru.printCache();
    
    return 0;
}
