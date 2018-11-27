/*
 *  FileName: Graph.h
 *  Created on: November 27, 2018
 *  Author: Tushar Malakar
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>

class Graph{

/**
* PSEUDOCODE sketch of the Vertex structure.
* In real C++, path would be of type Vertex *,
* and many of the code fragments that we describe
* require either a dereference * or use the
* -> operator instead of the . operator.
* Needless to say, this obscure the basic algorithmic ideas
*/
 struct Vertex {

      List<Vertex> adjacent_; // Adjacency list
      bool known_;
      DistType distance_; // DistType is probably int
      Vertex previous_in_path_; // Other data and member
      // functions as needed
 }

public:

  //Pseudocode to perform topological sort
  void topologicalSort( ){

     Queue<Vertex> q;
     int counter = 0;
     q.makeEmpty( );
     for each Vertex v
         if( v.indegree == 0 )
             q.enqueue( v );
             while( !q.isEmpty( ) ){

                 Vertex v = q.dequeue( );
                 v.topNum = ++counter; // Assign next number

                 for each Vertex w adjacent to v
                     if( --w.indegree == 0 )
                        q.enqueue( w );
            }
            if( counter != NUM_VERTICES )
            throw CycleFoundException{ };
 }


 //shortest path
  void UnweightedShortestPath(Vertex s) {

             for (each Vertex v) {
                v.distance_ = kInfinity;
                v.known_ = false;
             }
             s.distance_ = 0
             for (int curr_distance = 0; curr_distance < num_vertices_;
                                                    ++curr_distance_) {
                 for (each Vertex v) {
                     if (!v.known_ && v.distance_ == curr_distance) {
                         v.known_ = true;
                         for (each Vertex w adjacent to v) {
                                if (w.distance_ == kInfinity) {

                                     w.distance_ = curr_distance + 1;
                                     w.path_ = v;
                                }
                         } // end for each Vertex w…
                     } // end if (!v.known…
                } // end for each Vertex v
             }
                //O( |V|2 )
  }

  void UnweightedShortestPath(Vertex s) {

      Queue<Vertex> q;

      for each Vertex v {
          v.distance_ = kInfinity;
      }

      s.distance_ = 0;
      q.enqueue(s);

      while (!q.isEmpty()) {

          Vertex v = q.dequeue();
          for each Vertex w adjacent to v {

             if (w.distance_ == kInfinity) {

                w.distance_ = v.distance_ + 1;
                w.path_ = v;
                q.enqueue(w);
             }
          } // end for
     } // end while
 }

 void DijkstraShortestPath(Vertex s ) {
          for each Vertex v {

                v.distance_ = kInfinity;
                v.known_ = false;
          }
          s.distance_ = 0;
          while (true) {
           Vertex v = smallest unknown distance vertex; // How?
           if (v == NOT_A_VERTEX) break;
           v.known_ = true;

           for each Vertex w adjacent to v {

            if (!w.known_) {

              if (v.distance_ + c(v,w) < w.distance_) {

                w.distance_ = v.distance_ + c(v,w); // Decrease w.distance_
                w.previous_in_path_ = v;

              }
            }
           } // end of for each Vertex w…
         } // end of while (true)
 }

 void WeightedNegative(Vertex s) {

                Queue<Vertex> q;

                for each Vertex v

                    v.distance_ = kInfinity;
                    s.distance_ = 0;
                    q.enqueue(s);

                    while (!q.isEmpty()) {

                         Vertex v = q.dequeue();
                         for each Vertex w adjacent to v

                            if (v.distance_ + cvw < w.distance_ ) {

                                 w.distance_ = v.distance_ + cvw;
                                 w.previous_ = v;
                                 if (w is not already in q){

                                   q.enqueue(w);

                                 }
                             }
                     }
 }

 void kruskal() {

     int accepted_edges = 0;
     DisjointSet ds(num_vertices_);
     PriorityQueue<Edge> pq;

     pq.BuildQueue(GetAllEdges());
     Edge e;
     Vertex u, v;

     while (accepted_edges < num_vertices_ - 1) {
       pq.deleteMin(e); // Edge e = (u, v)
       SetType uset = ds.find(u);
       SetType vset = ds.find(v);

       if (uset != vset) {

           accepted_edges++;
           ds.unionSets(uset, vset);
       }
     }
 }

 // Depth First Search
 //A recursive implementation
 void dfs(Vertex v) {

     v.visited = true;
     for each Vertex w adjacent to v
         if (!w.visited){
            dfs(w);
         }
 }

 //Depth First Search
 //A recursive implementation
 void dfs(Vertex v) {

   v.visited = true;
   for each Vertex w adjacent to v

      if (!w.visited)
         dfs(w);
 }

 // Assign low; also check for articulation points
 void AssignLow( Vertex v ) {

     v.low = v.num; // Rule 1
     for each Vertex w adjacent to v {

        if (w.num > v.num) { // Forward edge

            AssignLow(w);
            if (w.low >= v.num)

              cout << v << “is an articulation point” << endl;
              v.low = min(v.low, w.low); // Rule 3
        }
        else if (v.parent != w) { // Back edge

             v.low = min(v.low, w.num) // Rule 2
        }
     } // End for each Vertex w
 }
 void printPath( Vertex v ){

      if( v.path != NOT_A_VERTEX ){

          printPath( v.path );
          cout << " to ";
      }
      cout << v;
 }


 // Runs the shortest path calculation from the adjacency map, returning a vector
 // that contains the sequence of word changes to get from first to second.
 unordered_map<string,string>
 findChain( const unordered_map<string,vector<string>> & adjacentWords,
 const string & first, const string & second ) {

  unordered_map<string,string> previousWord;
  queue<string> q;

  q.push( first );
  while( !q.empty( ) ) {

      string current = q.front( ); q.pop( );
      auto itr = adjacentWords.find( current );

      const vector<string> & adj = itr->second;
      for( string & str : adj )

         if( previousWord[ str ] == "" ) {

            previousWord[ str ] = current;
            q.push( str );
         }
      }
      previousWord[ first ] = "";

      return previousWord;
 }


 // After the shortest path calculation has run, computes the vector that
 // contains the sequence of words changes to get from first to second.
 vector<string> getChainFromPreviousMap(

    const unordered_map<string,string> & previous, const string & second ){
    vector<string> result;
    auto & prev = const_cast<unordered_map<string,string> &>( previous );

    for( string current = second; current != ""; current = prev[ current ] )
    result.push_back( current );

    reverse( begin( result ), end( result ) );
    return result;
 }
};

#endif
