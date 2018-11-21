/** @file LeftistHeap.h */

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include "QuadraticHash.h"
#include "LeftistNode.h"
#include <iostream>

using namespace std;

// LeftistHeap class for PriorityQueue
//
// CONSTRUCTION: with no parameters
//
// ******************MAIN OPERATIONS***********************
// LeftistNode* insert( x )     --> Returns lefistNode* of item just instered.
// bool deleteMin( minItem )    --> Return true if root was deleted and placed into minItem.
// Comparable findMin( )        --> Return smallest item.
// bool isEmpty( )              --> Return true if empty; else false.
// void makeEmpty( )            --> Remove all items.
// void merge( rhs )            --> Absorb rhs into this heap.
// void inOrder()               --> Inorder prints out the heap's content.
// ********************************************************

template <typename Comparable>
class LeftistHeap
{
  public:

    /**
     * Default Constructor.
     */
    LeftistHeap( ) : root{ nullptr }
      { }

    /**
     * Copy Constructor.
     */
    LeftistHeap( const LeftistHeap & rhs ) : root{ nullptr }
      { root = clone( rhs.root ); }
    
    /**
     * Move Constructor.
     */
    LeftistHeap( LeftistHeap && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor.
     */
    ~LeftistHeap( )
      { makeEmpty( ); }
    
    
    /**
     * Copy assignment operator.
     */
    LeftistHeap & operator=( const LeftistHeap & rhs )
    {
        LeftistHeap copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment operator.
     */
    LeftistHeap & operator=( LeftistHeap && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Returns true if empty, false otherwise.
     */
    bool isEmpty( ) const
      { return root == nullptr; }
    
    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item.
     */
    const Comparable & findMin( ) const
    {
        return root->element;
    }

    /**
     * Inserts x; duplicates allowed.
     * Returns a LeftistNode* to object inseted.
     */
    LeftistNode * insert( const Comparable & x )
    {
        LeftistNode * p = new LeftistNode{ x };
        root = merge( p, root ); 
        return p;
    }

    /**
     * Inserts x; duplicates allowed.
     * Returns a LeftistNode* to object inseted.
     */
    LeftistNode * insert( Comparable && x )
    {
        LeftistNode * p = new LeftistNode{ std::move( x ) };
        root = merge( p , root ); 
        return p;
    }

    /**
     * Return true if removed the minimum item.
     */
    bool deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            return false;
        else
        {
            minItem = findMin();
            LeftistNode *oldRoot = root;
            root = merge( root->left, root->right );
            if(root)
                root->parent = nullptr;
            delete oldRoot;
            return true;
        }
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        reclaimMemory( root );
        root = nullptr;
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     */
    void merge( LeftistHeap & rhs )
    {
        if( this == &rhs )
            return;

        root = merge( root, rhs.root );
        rhs.root = nullptr;
    }


    /**
     * Helper function which inorder prints out the heap's content.
     */
    void inOrder() 
    {
        inOrder( root );
    }

    /**
     * Inorder prints out the heap's content.
     */
    void inOrder( LeftistNode* ptr ) 
    {
        if ( ptr ) 
        {
            inOrder(ptr->left);
            cout << "[ " << ptr->element << '-' << ptr->npl << " ]";
            inOrder(ptr->right);
        }
    }

    LeftistNode* root;

    /**
     * Internal method to merge two roots.
     * Deals with deviant cases and calls recursive merge1.
     */
    LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 )
    {
        if( h1 == nullptr )
            return h2;
        if( h2 == nullptr )
            return h1;
        if( h1->element < h2->element )
            return merge1( h1, h2 );
        else
            return merge1( h2, h1 );
    }

    /**
     * Internal method to merge two roots.
     * Assumes trees are not empty, and h1's root contains smallest item.
     */
    LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 )
    {
        if( h1->left == nullptr )
        {   // Single node
            h1->left = h2;
            h1->left->parent = h1;
        }       
        else
        {
            h1->right = merge( h1->right, h2 );
            h1->right->parent = h1;
            if( h1->left->npl < h1->right->npl )
                swapChildren( h1 );
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    /**
     * Swaps t's two children.
     */
    void swapChildren( LeftistNode *t )
    {
        LeftistNode *tmp = t->left;
        t->left = t->right;
        t->right = tmp;
    }

    /**
     * Internal method to make the tree empty.
     */
    void reclaimMemory( LeftistNode *t )
    {
        if( t != nullptr )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    LeftistNode * clone( LeftistNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new LeftistNode{ t->element, clone( t->left ), clone( t->right ), t->npl };
    }

};


#endif