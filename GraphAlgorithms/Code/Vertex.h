/*
 *  Vertex.h
 *  Created on: December 10, 2018
 *  Author: Tushar Malakar
 */
#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <vector>
using namespace std;

struct Edge{
        int destintion;
        float weight;
        bool known;

        //default Edge
        Edge(){
            destintion = weight = 0;
            known = false;
        }
    };

class Vertex{

  private:
    //vector Edges
    vector<Edge> edges;

    int Source;
    float dist;
    bool known;
    int path;

  public:

    // Vertex Constructor
    Vertex() {
        edges.resize( 0 );
        Source = dist = known = 0;
        path = -1;
    }

    //Setter
    void SetSource(const int & x){
                     Source = x;
    }
    void SetEdge(const int & pos, const float & otherID){
                    edges[pos].destintion = otherID;
    }
    void SetEdgeCost(const int & pos, const float & newCost){
                    edges[pos].weight = newCost;
    }
    void SetDist(float newDist){
                    dist = newDist;
    }
    void SetKnown(bool isKnown){
                    known = isKnown;
    }
      void SetPath(Vertex v) {
                      path = v.GetSource();
      }


    //Getter
    int GetPath() {
                    return path;
    }
    bool GetKnown(){
                    return known;
    }
    int GetSource(){
                    return Source;
    }
    size_t GetEdgeCount(){
                    return edges.size();
    }

    int GetEdgeTo(const int & pos){
                    return edges[pos].destintion;
    }
    bool hasEdge ( bool  pos){
                return edges[pos].known;
    }
     const float GetEdgeCost( const int & pos){
                     return edges[pos].weight;
     }
     int GetTo(int pos){
                     return edges[pos].destintion;
     }

    const float GetDist() const {
                    return dist;
    }

    //other useful functions
    void ResizeEdgeVector(){
                    edges.resize( edges.size() + 1 );
    }

};

#endif
