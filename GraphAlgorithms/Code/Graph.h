/*
 *  Graph.h
 *  Created on: December 10, 2018
 *  Author: Tushar Malakar
 */
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <limits.h>
#include <queue>

#include "Vertex.h"
#include "PriorityQueue.h"


class Graph{


private:
    vector<Vertex> vertices;
    PriorityQueue minHeap;
    int size;
public:
    void SetSize(int newSize);
    int GetSize() { return size; }
    void SetID(const int & pos);
    void AddEdge(const int & vertexPos, const int & edgePos, const int & nextID, const float & newCost);
    void PrintAdjList();
    Vertex GetVertex(const int & i); //Retrieves Start Vertex for Dijkstra Algorithm
    void Dijkstra(Vertex start); //Dijkstra Algorithm
    void PrintPath(Vertex pos);
    void TopologicalSort(vector <int> adjList[]);
};

void Graph::SetSize(int newSize){
    vertices.resize( newSize ); //resizes and then stores the size
    size = newSize;
}
void Graph::SetID(const int & pos){
    vertices[pos].SetSource(pos); //sets the pos as ID since they are one and the same
}
void Graph::AddEdge(const int & vertexPos, const int & edgePos, const int & nextID, const float & newCost){
    if((signed int)vertices[vertexPos].GetEdgeCount() <= edgePos){
        vertices[vertexPos].ResizeEdgeVector(); //Increases size of Edge Vector each time
    }
    vertices[vertexPos].SetEdge(edgePos, nextID); //Sets Edge ID into the to variable
    vertices[vertexPos].SetEdgeCost(edgePos, newCost); //Sets cost
}


void Graph::PrintAdjList(){
    for(int i = 0; i < (signed int)vertices.size(); i++){
        cout << "Vertex " << i << " contents: " << endl;
        for(int j = 0; j < (signed int)vertices[i].GetEdgeCount(); j++){
            cout << "Edge " << j ;
            if(!vertices[i].hasEdge(j)){
                cout<< " is vertex " << vertices[i].GetEdgeTo(j) << endl;
                cout << "Cost of Traversal to Vertex " << vertices[i].GetEdgeTo(j) << " is " << vertices[i].GetEdgeCost(j) << endl;
            }
            else
                cout<<" has no edges."<<endl;
        }
    }
}


Vertex Graph::GetVertex(const int & i){
    return vertices[i]; //To retrieve the starting Vertex
}


void Graph::Dijkstra(Vertex start){
    /* Initially set every vertex in the graph to "Infinity" and unknown */
    for(int i = 0; i < (signed int)vertices.size(); i++){
        vertices[i].SetDist(INT_MAX);
        vertices[i].SetKnown(false);
    }
    /* Start distance is 0, and makes sure to represent it as such into the graph as well */
    start.SetDist(0);
    vertices[start.GetSource()].SetDist(0);
    minHeap.Insert(start); //Initially, Start is the only vertex in the Queue
    for( ; ; ){
        Vertex v;
        bool success = false;
        /*Essentially goes through the entire minHeap, and checks if any vertex is not yet known, which means it has not yet been optimized in distance. If not, success is false and that means we are finished. */
        while(!minHeap.IsEmpty() && !success){
            v = minHeap.FindMin();
            minHeap.DeleteMin();
            if(!v.GetKnown())
                success = true;
        }
        if (!success)
            break; //finished
        v.SetKnown(true); //Sets it to being known
        /*Checks every edge for each vector. If that edge's dist is more than the cost to get from the vertex v to it, then it is optimized so that it is connected on that path, since that is the minimum path from the starting point to there. This is done multiple times, and the new version is placed in the minHeap to represent that, and will be ignored if it is already known.*/
        for(int i = 0; i < (signed int)v.GetEdgeCount(); i++){
            if((v.GetDist() + v.GetEdgeCost(i)) < vertices[v.GetTo(i)].GetDist()){
                vertices[v.GetTo(i)].SetDist(v.GetDist() + v.GetEdgeCost(i));
                minHeap.Insert(vertices[v.GetTo(i)]);
                vertices[v.GetTo(i)].SetPath(v);
            }
        }
    }
}


void Graph::PrintPath(Vertex pos){
    if(pos.GetPath() != -1){
        PrintPath(vertices[pos.GetPath()]); //Does it recursively, calling the vector based on the path int
        cout << " to ";//<<vertices[pos.GetPath()];
    }
    cout << pos.GetSource();
}


#endif
