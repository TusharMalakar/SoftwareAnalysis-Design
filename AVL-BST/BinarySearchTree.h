/*
 * File:   BinarySearchTree.h
 * Author: Tushar Malakar
 * Created on Sep 27, 2018
 */
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
//#include "SequenceMap.h"
#include <cmath>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// void remove( x, i)     --> If x is found in tree, it is removed and call returns true.
// bool contains( x )     --> Return true if x is present
// void find_and_print( x)--> Prints vector associated with x if x is present
// bool find( x )         --> Returns true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// int countNodes( )      --> Return number of BinaryNodes
// int calculate_IPL()    --> Return Internal Path Length
// int calculate_Avg_Depth()-> Return Average Depth of all Nodes
// double calculate_ratio()-> Return Ratio of Avg Depth to log2n
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree( ) : root_{ nullptr } {}

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root_{ nullptr }
    {
        root_ = clone( rhs.root_ );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root_{ rhs.root_ }
    {
        rhs.root_ = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root_, rhs.root_ );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        //if( isEmpty() )
        //throw UnderflowException{ };
        return findMin( root_ )->element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        //if( isEmpty( ) )
        //throw UnderflowException{ };
        return findMax( root_ )->element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable & x) const
    {
        return contains(x, root_ );
    }

    /**
      * Pre-Condition: Object T has a string data member that can be retrieved using getRecSequence().
      * Post Condition: returns true if x is found. recursion_calls is updated to indicated the number of times
      * find() is called.
     */
    bool find(const std::string & x, int& recursion_calls) const {
        recursion_calls = 0;
        return find(x, root_, recursion_calls);
    }

    /**
      * If x is found in the tree, object is printed. Assumes Object T has a printevector() utility.
     */
    void find_and_print(const std::string& x) const {
         find_and_print(x, root_);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root_ == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root_, out );
        out << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root_ );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root_ );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root_ );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root_ );
    }

    /**
      * Remove x from the tree.
      * Post-Condition: If x is not found, returns false. recursion_calls is updated to indicate total number of
      * recursion calls it took to run remove().
     */
    bool remove(const std::string & x, int& recursion_calls) {
        recursion_calls = 0;
        return remove(x, root_, recursion_calls);
    }

    /**
     * Returns number of nodes in tree.
     */
    int count_Nodes() const {
        return count_Nodes(root_);
    }
    /**
      *Returns the sum of the depth of each node in a tree
     */
    int calculate_IPL() const {
        return calculate_IPL(root_, 0);
    }
    /**
      * Return the average depth of the tree.
     */
    int calculate_Avg_Depth() const {
        int IPL = calculate_IPL(root_, 0);
        int nodes = count_Nodes(root_);
        return IPL/nodes;
    }
    /**
      * Returns the ratio of the average depth to log2n where n is the number of nodes
     */
    double calculate_ratio() const {
        int nodes = count_Nodes(root_);
        int avg_depth = calculate_Avg_Depth();
        return avg_depth / log2(nodes);
    }

private:
    struct BinaryNode
    {
        Comparable element_;
        BinaryNode *left_;
        BinaryNode *right_;

        BinaryNode( const Comparable & the_element, BinaryNode *lt, BinaryNode *rt )
        : element_{ the_element }, left_{ lt }, right_{ rt } { }

        BinaryNode( Comparable && the_element, BinaryNode *lt, BinaryNode *rt )
        : element_{ std::move( the_element ) }, left_{ lt }, right_{ rt } { }
    };

    BinaryNode *root_;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that root_s the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element_ )
            insert( x, t->left_ );
        else if( t->element_ < x )
            insert( x, t->right_ );
        else
            t->element_.Merge(x);  // Duplicate; Assumes Comparable is a Sequence Map.
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * This function assumes all Comparables have a Merge() function.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element_ )
            insert( std::move( x ), t->left_ );
        else if( t->element_ < x )
            insert( std::move( x ), t->right_ );
        else
            t->element_.Merge(x);  // Duplicate
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element_ )
            remove( x, t->left_ );
        else if( t->element_ < x )
            remove( x, t->right_ );
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            remove( t->element_, t->right_ );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
    }
    /**
      * Internal method to remove x from subtree while counting number of recursion calls to do so.
     */

    bool remove(const std::string & x, BinaryNode * & t, int& recursion_calls) {
        ++recursion_calls;
        if( t == nullptr )
            return false;   // Item not found
        if( x < t->element_.getRecSequence() )
            return remove( x, t->left_, recursion_calls);
        else if( t->element_.getRecSequence() < x )
            return remove( x, t->right_, recursion_calls);
        else if( t->left_ != nullptr && t->right_ != nullptr ) {
            t->element_ = findMin( t->right_ )->element_;
            return remove( t->element_.getRecSequence(), t->right_, recursion_calls );
        } else {
            BinaryNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
            return true;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left_ == nullptr )
            return t;
        return findMin( t->left_ );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right_ != nullptr )
                t = t->right_;
        return t;
    }

    /**
      * Internal Method to test if an item in a subtree is present.
      * This is specific to an object T with a string data member that can be retrieved using getRecSequence().
      * t is the node that roots the tree.
      * Find() keeps track of how many recursion calls are made.
     */
    bool find( const std::string& x, BinaryNode *t, int& recursion_calls) const {
        ++recursion_calls;
        if( t == nullptr )
            return false;
        else if( x < t->element_.getRecSequence())
            return find( x, t->left_, recursion_calls );
        else if( t->element_.getRecSequence() < x )
            return find( x, t->right_, recursion_calls);
        else
            return true;    // Match
    }
    /**
      * If x is found in the tree, it's associated vector is printed.
      * Assumes type T has a Printe_Vector() function, a vector data member, and an enzyme_acronym_ data member.
     */
    void find_and_print(const std::string& x, BinaryNode *t) const {
        if( t == nullptr )
            std::cout << "Not found in this tree." << std::endl;
        else if( x < t->element_.getRecSequence())
            return find_and_print( x, t->left_ );
        else if( t->element_.getRecSequence() < x )
            return find_and_print( x, t->right_ );
        else
            t->element_.Print_Vector();
    }
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const {
        if( t == nullptr )
            return false;
        else if( x < t->element_ )
            return contains( x, t->left_ );
        else if( t->element_ < x )
            return contains( x, t->right_ );
        else
            return true;    // Match
    }
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, BinaryNode *t ) const
     {
     while( t != nullptr )
     if( x < t->element_ )
     t = t->left_;
     else if( t->element_ < x )
     t = t->right_;
     else
     return true;    // Match

     return false;   // No match
     }
     *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left_ );
            makeEmpty( t->right_ );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left_, out );
            out << t->element_ << " ";
            printTree( t->right_, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element_, clone( t->left_ ), clone( t->right_ ) };
    }
    /**
        Internal function to count nodes.
     */
    int count_Nodes(BinaryNode *t) const {
        if( t != nullptr ) {
            return count_Nodes(t->left_) + count_Nodes(t->right_) + 1;
        } else
            return 0;
    }
    /**
      * Internal function to sum depth of each node in tree.
     */
    int calculate_IPL(BinaryNode *t, int depth) const  {
        if (t == NULL)
            return 0;
        else
            return calculate_IPL(t->left_, depth+1) + calculate_IPL(t->right_, depth+1) + depth;
    }
};

#endif
