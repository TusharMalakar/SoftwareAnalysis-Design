/** @file QuadraticHash.h */

#ifndef QUADRATIC_HASH_H
#define QUADRATIC_HASH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>

#include "LeftistHeap.h"
#include "LeftistNode.h"

using namespace std;

int nextPrime( int n );
bool isPrime( int n );

// Quadratic Hash table class for PriorityQueue 
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************MAIN OPERATIONS***********************
// bool insert( x,  LeftistNode* )      --> Return true if inserted x && pushed pointer of x to vector.
// bool remove( x )                     --> returns true if removed x.
// vector<LefistNode*> contains( int )  --> Returns vector of node pointers to item.
// void makeEmpty( )                    --> Logically removes all items.
// bool percolateUp( x )                --> Returns true if successfully swaped x with x->parent in _heap and _hash.
// ********************************************************

template <typename HashedObj>
class QuadraticHash
{
  public:

    /**
     * Defualt constructor.
     */
    explicit QuadraticHash( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    /**
     * Returns vector of node pointers to item.
     */
    vector<LeftistNode*> contains( const HashedObj & x ) const
    {
        int Pos = findPos( x );
        return array[ Pos ].pointers;
    }

    /**
     * Logically clears entire array and all entry vectors.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
        {
            entry.info = EMPTY;
            entry.pointers.clear();
        }  
    }

    /**
     * Returns true is item was inserted into the hashtable.
     * If item is duplicate, pointer to item is pushed onto entry's vector.
     */
    bool insert( const HashedObj & x, LeftistNode* P )
    {

        int currentPos = findPos( x );
        if( isActive( currentPos ) && array[ currentPos ].element != x )
            return false;
        else if ( isActive( currentPos ) && array[ currentPos ].element == x )
            array[ currentPos ].pointers.push_back(P);
        else
        {
            array[ currentPos ].element = x;
            array[ currentPos ].info = ACTIVE;
            array[ currentPos ].pointers.clear();
            array[ currentPos ].pointers.push_back(P);
        }

        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    /**
     * Returns true is item was moved into the hashtable.
     * If item is duplicate, pointer to item is pushed onto entry's vector.
     */
    bool insert( HashedObj && x, LeftistNode* P )
    {

        int currentPos = findPos( x );
        if( isActive( currentPos ) && array[ currentPos ].element != x )
            return false;
        else if ( isActive( currentPos ) && array[ currentPos ].element == x )
            array[ currentPos ].pointers.push_back(P);
        else
        {
            array[ currentPos ].element = std::move(x);
            array[ currentPos ].info = ACTIVE;
            array[ currentPos ].pointers.clear();
            array[ currentPos ].pointers.push_back(P);
        }

        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    /**
     * Returns true is item has been logically deleted.
     */
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    /**
     * Struct to hold items in Hash array.
     */
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        vector<LeftistNode*> pointers;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY, vector<LeftistNode*> p = vector<LeftistNode*>{}  )
          : element{ e }, info{ i }, pointers { p } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY, vector<LeftistNode*> p = vector<LeftistNode*>{} )
          : element{ std::move( e ) }, info{ i }, pointers{ p } { }
    };

    vector<HashEntry> array;
    int currentSize;
    int mutable collisions;

    /**
     * Returns if hash entry is logically active.
     */
    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    /**
     * Returns int of the current position of element in hash's array.
     */
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe.
            offset += 2;
            while( currentPos >= array.size() )
                currentPos -= array.size();
            collisions++;
        }

        return currentPos;
    }

    /**
     * Redistributes the hash table into new double-sized table.
     */
    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table.
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over.
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                for( auto & pointer : entry.pointers)
                    insert( std::move( entry.element ), pointer );
    }

    /**
     * Returns size_t of unqiue hash generated for object x.
     */
    size_t myhash( const HashedObj & x ) const
    {
        static hash<int> hf;
        return hf( x ) % array.size( );
    }

    /**
    * Returns true if successfully swaped x with x->parent in _heap and _hash.
    * Doesn't actually swap hash elements but instead swaps thier pointers.
    */
    bool percolateUp( int item )
    {

        int I = 0;
        int Cpos = findPos(item);
        if ( array[Cpos].info == EMPTY || array[Cpos].info == DELETED || array[Cpos].pointers.at(0)->element != item )
            return false;    

        if(array[Cpos].pointers[0]->parent)
        {
            for (int i = 0; i < array[findPos(array[Cpos].pointers.at(0)->parent->element)].pointers.size(); ++i)
                if(array[Cpos].pointers.at(0)->parent == array[findPos(array[Cpos].pointers.at(0)->parent->element)].pointers.at(i))
                    I = i;
            int Ppos = findPos(array[Cpos].pointers.at(0)->parent->element);
            array[Cpos].pointers.at(0)->element = array[Ppos].pointers[I]->element;
            array[Ppos].pointers[I]->element = item;
            LeftistNode* tmp = array[Cpos].pointers.at(0);
            array[Cpos].pointers.at(0) = array[Ppos].pointers[I];
            array[Ppos].pointers[I] = tmp;
            return true;
        }
        else
            return false; 
    }
};

/**
 * Global function which determines if n is prime.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Global function which calculates next prime equals to or greater n.
 */
int nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 ) {};

    return n;
}

#endif // QUADRATIC_HASH_H
