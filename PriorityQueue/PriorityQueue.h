/** @file PriorityQueue.h */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "QuadraticHash.h"
#include "LeftistHeap.h"
#include "LeftistNode.h"

using namespace std;

// PriorityQueue class
//
// CONSTRUCTION: with no parameters
//
// ******************MAIN OPERATIONS***********************
// bool Insert( x )                         --> Returns true if x is inserted to both _heap and _hash.
// bool Find( x, vector<LeftistNode*>& )    --> Returns true if x is found in hash.
// bool Remove( x )                         --> Returns true if instance of x was deleted.
// ********************************************************

template <typename T>
class PriorityQueue 
{
public:

    /**
     * Defualt constructor
     */
    PriorityQueue() : _lastRemovedItem{}, _hash{}, _heap{}, _vec{}  { }

    /**
     * Returns true if x is inserted to both _heap and _hash.
     */
    bool Insert(T item)
    {
        LeftistNode* P = _heap.insert(item);
        return _hash.insert(item,P);
    }

    /**
     * Helper function which returns true if x was found in hash.
     */
    bool Find(T item)
    {
        return Find(item, _vec);
    }

    /**
     * Returns true if x is found in hash, and stores vector of pointers to x in V.
     */
    bool Find(T item, vector<LeftistNode*>& V)
    {
        V = _hash.contains(item);

        if(V.empty())
            return false;

        for(auto X : V)
            if(X->element != item)
                return false;

        return true;
    }

    /**
     * Returns true if single instance of x was deleted,
     * Note there maybe more item duplicates contained within vector.
     */
    bool Remove(T item)
    {
        while(_hash.percolateUp( item )) { }

        if(_heap.findMin() == item)
        {
            _heap.deleteMin(_lastRemovedItem);
            int pos = _hash.findPos(item);
            _hash.array[pos].pointers.erase(_hash.array[pos].pointers.begin());

            if(_hash.array[pos].pointers.empty())
                _hash.array[pos].info = QuadraticHash<int>::EntryType(DELETED);

            return true;
        }
        return false;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    int _lastRemovedItem;
    QuadraticHash<int> _hash;
    LeftistHeap<int> _heap;
    vector<LeftistNode*> _vec;
};


#endif // PRIORITY_QUEUE_H