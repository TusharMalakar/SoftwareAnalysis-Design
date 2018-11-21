
/** @file LeftistNode.h */

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

// LeftistNode class for PriorityQueue
//
// CONSTRUCTION: best with no parameters
//
// ******************MAIN OPERATIONS***********************
// 
// ********************************************************

class LeftistNode
{
public:
    int         element;
    LeftistNode *left;
    LeftistNode *right;
    LeftistNode *parent;
    int          npl;

    LeftistNode( const int & e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0, LeftistNode *pt = nullptr )
      : element{ e }, left{ lt }, right{ rt }, parent{ pt }, npl{ np }  { }
    
    LeftistNode( int && e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0,  LeftistNode *pt = nullptr  )
      : element{ std::move( e ) }, left{ lt }, right{ rt }, parent{ pt }, npl{ np } { }

};


#endif