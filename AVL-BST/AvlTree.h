/*
 *  AvlTree.h
 *  Created on: Sep 27, 2018
 *  Author: Tushar Malakar
 */
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
//#include "SequenceMap.h"
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool remove( x, i)     --> If x is found in tree, it is removed and call returns true.
// bool contains( x )     --> Return true if x is present
// void find_and_print( x)--> Prints vector associated with x if x is present
// bool find( x )         --> Returns true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// int countNodes( )      --> Return number of AvlNodes
// int calculate_IPL()    --> Return Internal Path Length
// int calculate_Avg_Depth()-> Return Average Depth of all Nodes
// double calculate_ratio()-> Return Ratio of Avg Depth to log2n
// print_Between(k1, k2)  --> prints all elements with keys between k1 and k2
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root_{ nullptr }
      { }

    AvlTree( const AvlTree & rhs ) : root_{ nullptr }
    {
        root_ = clone( rhs.root_ );
    }

    AvlTree( AvlTree && rhs ) : root_{ rhs.root_ }
    {
        rhs.root_ = nullptr;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
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
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root_ )->element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root_ )->element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable & x) const
    {
        return contains(x, root_);
    }

    /**
      * This is specific to an object T with a string data member that can be retrieved using getRecSequence().
      * Post Condition: returns true if x is found. recursion_calls is updated to indicated the number of times
      * find() is called.
     */
    bool find(const std::string & x, int& recursion_calls) const {
        recursion_calls = 0;
        return find(x, root_, recursion_calls);
    }

    /**
      * If x is located in the tree, its associated vector is printed
      * This assumes that T has a data member that is a vector.
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
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root_ );
        cout << endl;
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

    int heightOfTree() const {
      return heightOfNode(root_);
    }
    /**
     * Returns number of nodes in tree.
     */
    int count_Nodes() const {
        return count_Nodes(root_);
    }
    /**
      *Returns the sum of the depth of each node in a tree.
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
    /**
      * Prints all elements in tree between the value str1 and str2.
      * Assumes T has a string data member.
     */
    void print_Between(std::string str1, std::string str2) {
        print_Between(str1, str2, root_);
    }

  private:
    struct AvlNode
    {
        Comparable element_;
        AvlNode   *left_;
        AvlNode   *right_;
        int       height_;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ ele }, left_{ lt }, right_{ rt }, height_{ h } { }

        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ std::move( ele ) }, left_{ lt }, right_{ rt }, height_{ h } { }
    };

    AvlNode *root_;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * This function assumes all Comparables have a Merge() function.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element_ )
            insert( x, t->left_ );
        else if( t->element_ < x )
            insert( x, t->right_ );
        else
        {
            t->element_.Merge(x);
            return;
        }
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * This function assumes all Comparables have a Merge() function.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element_ )
            insert( std::move( x ), t->left_ );
        else if( t->element_ < x )
            insert( std::move( x ), t->right_ );
         else
        {
            t->element_.Merge(x);  // Duplicate;
            return;
        }
        balance( t );
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
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
            AvlNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }

        balance( t );
    }
    /**
      * Internal method to remove x from subtree while counting number of recursion calls to do so.
     */

    bool remove(const std::string & x, AvlNode * & t, int& recursion_calls) {
        ++recursion_calls;
        if( t == nullptr )
            return false;   // Item not found; do nothing
        if( x < t->element_.getRecSequence() )
            return remove( x, t->left_, recursion_calls);
        else if( t->element_.getRecSequence() < x )
            return remove( x, t->right_, recursion_calls);
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            return remove( t->element_.getRecSequence(), t->right_ ,recursion_calls);
        } else {
            AvlNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
            return true;
        }
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;

        if( heightOfNode( t->left_ ) - heightOfNode( t->right_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->left_->left_ ) >= heightOfNode( t->left_->right_ ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( heightOfNode( t->right_ ) - heightOfNode( t->left_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->right_->right_ ) >= heightOfNode( t->right_->left_ ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
    }
        t->height_ = max( heightOfNode( t->left_ ), heightOfNode( t->right_ ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
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
    AvlNode * findMax( AvlNode *t ) const
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
    bool find( const std::string& x, AvlNode *t, int& recursion_calls) const
    {
        ++recursion_calls;
        if( t == nullptr )
            return false;
        else if( x < t->element_.getRecSequence())
            return find( x, t->left_, recursion_calls);
        else if( t->element_.getRecSequence() < x )
            return find( x, t->right_, recursion_calls);
        else
            return true;    // Match
    }
    /**
      * If x is found in the tree, its associated vector is printed.
      * Assumes type T has a Printe_Vector() function, a vector data member, and an enzyme_acronym_ data member.
     */
    void find_and_print(const std::string& x, AvlNode *t) const {
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
     * Internal method to test if an item is in a subtree is present.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
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
    bool contains( const Comparable & x, AvlNode *t ) const
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
    void makeEmpty( AvlNode * & t )
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
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left_ );
            cout << t->element_ << " ";
            printTree( t->right_ );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element_, clone( t->left_ ), clone( t->right_ ), t->height_ };
    }
        // Avl manipulations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int heightOfNode( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height_;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left_ child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left_;
        k2->left_ = k1->right_;
        k1->right_ = k2;
        k2->height_ = max( heightOfNode( k2->left_ ), heightOfNode( k2->right_ ) ) + 1;
        k1->height_ = max( heightOfNode( k1->left_ ), k2->height_ ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right_ child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right_;
        k1->right_ = k2->left_;
        k2->left_ = k1;
        k1->height_ = max( heightOfNode( k1->left_ ), heightOfNode( k1->right_ ) ) + 1;
        k2->height_ = max( heightOfNode( k2->right_ ), k1->height_ ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left_ child.
     * with its right child; then node k3 with new left_ child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left_ );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left_ child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right_ );
        rotateWithRightChild( k1 );
    }
    /**
     * Internal function to count nodes.
     */
    int count_Nodes(AvlNode *t) const {
        if( t != nullptr ) return count_Nodes(t->left_) + count_Nodes(t->right_) + 1;
        else return 0;
    }
    /**
      * Internal function to sum depth of each node in tree.
     */
    int calculate_IPL(AvlNode *t, int depth) const {
        if (t == NULL) return 0;
        else return calculate_IPL(t->left_, depth+1) + calculate_IPL(t->right_, depth+1) + depth;
    }

    void print_Between(const std::string str1, const std::string str2, const AvlNode *t) {
        if( t != nullptr ) {
          if (t->element_.getRecSequence() > str1)
              print_Between( str1, str2, t->left_ );
          if ((t->element_.getRecSequence() > str1) && (t->element_.getRecSequence()< str2))
              std::cout << t->element_<< " ";
          if (t->element_.getRecSequence()<= str2)
              print_Between( str1, str2, t->right_ );
        }
    }
    void rot(const std::string str1, const AvlNode *t) {
        if( t != nullptr ) {
          if (t->element_.getRecSequence() == str1)
                cout<<t;

    }}
};

#endif
