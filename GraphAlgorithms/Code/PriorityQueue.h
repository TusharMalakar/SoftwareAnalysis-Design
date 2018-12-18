/*
 *  PriorityQueue.h
 *  Created on: December 10, 2018
 *  Author: Tushar Malakar
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <iostream>
#include <stdexcept>

#include "dsexceptions.h"
#include "Vertex.h"

using namespace std;

//definition of PairNode
//it has previous, left and next pointers
struct PairNode
    {
        Vertex   element;
        PairNode    *leftChild;
        PairNode    *nextSibling;
        PairNode    *prev;

        PairNode( const Vertex & theElement ) : element{ theElement },
        leftChild{ nullptr }, nextSibling{ nullptr }, prev{ nullptr } { }

        PairNode( Vertex && theElement ) : element( std::move( theElement ) ),
        leftChild{ nullptr }, nextSibling{ nullptr }, prev{ nullptr } { }
/*
         * Internal method to make the tree empty.
     * WARNING: This is prone to running out of stack space.
     */
    void ReclaimMemory( PairNode *t )
    {
        if( t != nullptr )
        {
            ReclaimMemory( t->leftChild );
            ReclaimMemory( t->nextSibling );
            delete t;
        }
    }

    /**
     * Internal method that is the basic operation to maintain order.
     * Links first and second together to satisfy heap order.
     * first is root of tree 1, which may not be nullptr.
     *    first->nextSibling MUST be nullptr on entry.
     * second is root of tree 2, which may be nullptr.
     * first becomes the result of the tree merge.
     */
    void CompareAndLink( PairNode * & first, PairNode *second )
    {
        if( second == nullptr )
            return;

        if( second->element.GetDist() < first->element.GetDist() )
        {
            // Attach first as leftmost child of second
            second->prev = first->prev;
            first->prev = second;
            first->nextSibling = second->leftChild;
            if( first->nextSibling != nullptr )
                first->nextSibling->prev = first;
            second->leftChild = first;
            first = second;
        }
        else
        {
            // Attach second as leftmost child of first
            second->prev = first;
            first->nextSibling = second->nextSibling;
            if( first->nextSibling != nullptr )
                first->nextSibling->prev = first;
            second->nextSibling = first->leftChild;
            if( second->nextSibling != nullptr )
                second->nextSibling->prev = second;
            first->leftChild = second;
        }
    }

    /**
     * Internal method that implements two-pass merging.
     * firstSibling the root of the conglomerate and is assumed not nullptr.
     */
    PairNode * CombineSiblings( PairNode *firstSibling )
    {
        if( firstSibling->nextSibling == nullptr )
            return firstSibling;

        // Allocate the array
        static vector<PairNode *> treeArray( 5 );

        // Store the subtrees in an array
        int numSiblings = 0;
        for( ; firstSibling != nullptr; ++numSiblings )
        {
            if( numSiblings == (signed int)treeArray.size( ) )
                treeArray.resize( numSiblings * 2 );
            treeArray[ numSiblings ] = firstSibling;
            firstSibling->prev->nextSibling = nullptr;  // break links
            firstSibling = firstSibling->nextSibling;
        }
        if( numSiblings == (signed int)treeArray.size( ) )
            treeArray.resize( numSiblings + 1 );
        treeArray[ numSiblings ] = nullptr;

        // Combine subtrees two at a time, going left to right
        int i = 0;
        for( ; i + 1 < numSiblings; i += 2 )
            CompareAndLink( treeArray[ i ], treeArray[ i + 1 ] );

        int j = i - 2;

        // j has the result of last CompareAndLink.
        // If an odd number of trees, get the last one.
        if( j == numSiblings - 3 )
            CompareAndLink( treeArray[ j ], treeArray[ j + 2 ] );

        // Now go right to left, merging last tree with
        // next to last. The result becomes the new last.
        for( ; j >= 2; j -= 2 )
            CompareAndLink( treeArray[ j - 2 ], treeArray[ j ] );
        return treeArray[ 0 ];
    }

    /**
     * Internal method to Clone subtree.
     * WARNING: This is prone to running out of stack space.
     */
    PairNode * Clone( PairNode *t )
    {
        if( t == nullptr )
            return nullptr;
        else
        {
            PairNode *p = new PairNode{ t->element };
            if( ( p->leftChild = Clone( t->leftChild ) ) != nullptr )
                p->leftChild->prev = p;
            if( ( p->nextSibling = Clone( t->nextSibling ) ) != nullptr )
                p->nextSibling->prev = p;
            return p;
        }
    }


 };




class PriorityQueue{

 public:

    PairNode *root;

    PriorityQueue( )
    {
        root = nullptr;
    }

    ~PriorityQueue( )
    {
        MakeEmpty( );
    }


    PriorityQueue( const PriorityQueue & rhs ) : root{ nullptr }
    {
        root = root->Clone( rhs.root );
    }

    PriorityQueue( PriorityQueue && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }


    /**
     * Deep copy.
     */
    PriorityQueue & operator=( const PriorityQueue & rhs )
    {
        PriorityQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
    PriorityQueue & operator=( PriorityQueue && rhs )
    {
        std::swap( root, rhs.root );

        return *this;
    }


    bool IsEmpty( ) const
    {
        return root == nullptr;
    }

    const Vertex & FindMin( ) const
    {
        if( IsEmpty( ) )
            throw UnderflowException{ };
        return root->element;
    }

    typedef PairNode * Position;

    /**
     * Insert item x into the priority queue, maintaining heap order.
     * Return the Position  (a pointer to the node) containing the new item.
     */
    Position Insert( const Vertex & x )
    {
        PairNode *newNode = new PairNode{ x };

        if( root == nullptr )
            root = newNode;
        else
            root->CompareAndLink( root, newNode );
        return newNode;
    }

    /**
     * Insert item x into the priority queue, maintaining heap order.
     * Return the Position  (a pointer to the node) containing the new item.
     */
    Position Insert( Vertex && x )
    {
        PairNode *newNode = new PairNode{ std::move( x ) };

        if( root == nullptr )
            root = newNode;
        else
            root->CompareAndLink( root, newNode );
        return newNode;
    }

    /**
     * Remove the smallest item from the priority queue
     * or throw UnderflowException if empty.
     */
    void DeleteMin( )
    {
        if( IsEmpty( ) )
            throw UnderflowException{ };

        PairNode *oldRoot = root;

        if( root->leftChild == nullptr )
            root = nullptr;
        else
            root = root->CombineSiblings( root->leftChild );

        delete oldRoot;
    }

    /**
     * Remove the smallest item from the priority queue.
     * Pass back the smallest item via minItem, or throw UnderflowException if empty.
     */
    void DeleteMin( Vertex & minItem )
    {
        minItem = FindMin( );
        DeleteMin( );
    }

    void MakeEmpty( )
    {
        root->ReclaimMemory( root );
        root = nullptr;
    }

    /**
     * Change the value of the item stored in the pairing heap.
     * Throw invalid_argument if newVal is larger than
     *    currently stored value.
     * p is a Position returned by Insert.
     * newVal is the new value, which must be smaller
     *    than the currently stored value.
     */
    void DecreaseKey( Position p, Vertex & newVal )
    {
        if( p->element.GetDist() < newVal.GetDist() )
            throw invalid_argument( "newVal too large" );

        p->element = newVal; //Might be wrong but probably not
        if( p != root )
        {
            if( p->nextSibling != nullptr )
                p->nextSibling->prev = p->prev;
            if( p->prev->leftChild == p )
                p->prev->leftChild = p->nextSibling;
            else
                p->prev->nextSibling = p->nextSibling;

            p->nextSibling = nullptr;
            root->CompareAndLink( root, p );
        }
    }
    void DecreaseKey( Position p, Vertex && newVal )
    {
        if( p->element.GetDist() < newVal.GetDist() )
            throw invalid_argument( "newVal too large" );

        p->element = std::move( newVal );
        if( p != root )
        {
            if( p->nextSibling != nullptr )
                p->nextSibling->prev = p->prev;
            if( p->prev->leftChild == p )
                p->prev->leftChild = p->nextSibling;
            else
                p->prev->nextSibling = p->nextSibling;

            p->nextSibling = nullptr;
            root->CompareAndLink( root, p );
        }
    }

};

#endif
