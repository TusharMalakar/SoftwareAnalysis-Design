#ifndef __SIMULATOR_H_
#define __SIMULATOR_H_

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Graph.h"


using namespace std;


class Simulator{
private:
    int fileNums; //Keeps track of numbers in file that represent node IDs
    float fileCost; //Keeps track of floats that represent the cost of the edges
    int pos; //position of vector currently
    ifstream inStream;

    Graph adjList; //Graph that holds adjacent list
    int vertexNum; //reads the vertex number from the file
    int counter; //counter for edge vector to set new edges in each next part of the vector
public:
    void OpenFile(string && fileName);
    void CreateGraph();
    void CheckAdj(int && adjFile);
    void StartDijkstra(int && startPos);
    void StartDijkstra1(int && startPos);

};
void Simulator::OpenFile( string && fileName){
    inStream.open(fileName);
    if(inStream.fail()){
        cout << "Error. This file could not open." << endl;
        exit(1);
    }
}

void Simulator::CreateGraph(){
    inStream >> fileNums;

    adjList.SetSize(fileNums); //First graphs the size of the vector array and then sets it
    while(inStream >> fileNums){

        pos = fileNums;
        adjList.SetID(pos); //The Vertex that we will be adding adjacent edges to
        counter = 0;

        while(inStream.peek() != -1){
            inStream >> fileNums;
            if(fileNums == -1) //If either fileNums or fileCost grabs -1, break and move to the next line
                break;
            inStream >> fileCost;
            if(fileCost == -1)
                break;
            adjList.AddEdge(pos,counter,fileNums,fileCost); //Sets the edge using the parameters received
            counter++;
        }
    }
    adjList.PrintAdjList();
}


void Simulator::CheckAdj(int && adjFile){
                inStream >> adjFile ;
                cout << adjFile <<"____________________"<<endl;

                                adjList.GetVertex(adjFile);
                                cout<<endl<<adjFile <<" has edge with "<<endl;




}

void Simulator::StartDijkstra(int &&startPos){
    if(startPos < 0 || startPos >= adjList.GetSize()){
        cout << "This is not a valid startPos in the Vertex" << endl;
        exit(1);
    }
    cout << "Starting position is " << startPos << endl;
    adjList.Dijkstra(adjList.GetVertex(startPos));
    char choice;
    int vertexNum;
    do{
        cout << "Enter a valid Vertex number. This will print the shortest path to that Vertex." << endl;
        cin >> vertexNum;
        /* Checks to see whether user enters a number in a valid range so that program doesn't break */
        while (vertexNum < 0 || vertexNum >= adjList.GetSize()){
            cout << "Invalid Number, try again." << endl;
            cin >> vertexNum;
        }
        /* If the Distance is still INT_MAX, that means there was no path from it to anywhere else */
        if(adjList.GetVertex(vertexNum).GetDist() == INT_MAX){
            cout << "Getting to the position written is impossible." << endl;
        }
        else{
            cout << "The total cost to " << adjList.GetVertex(vertexNum).GetSource() << " is " << adjList.GetVertex(vertexNum).GetDist() << endl;
            cout << "The Path is: " << endl;
            adjList.PrintPath(adjList.GetVertex(vertexNum));
            cout << endl;
        }
        cout << "Would you like to try another Vertex? If so, enter \'Y\' or \'y\'. Otherwise, enter anything else." << endl;
        cin >> choice;
    } while(choice == 'Y' || choice == 'y');
}
void Simulator::StartDijkstra1(int && startPos){
    if(startPos < 0 || startPos >= adjList.GetSize()){
        cout << "This is not a valid startPos in the Vertex" << endl;
        exit(1);
    }
    cout << "Starting position is " << startPos << endl;
    adjList.Dijkstra(adjList.GetVertex(startPos));
    char choice;
    int vertexNum;

        cout << "Enter a valid Vertex number. This will print the shortest path to that Vertex." << endl;
        cin >> vertexNum;


            cout << "The total cost to " << adjList.GetVertex(vertexNum).GetSource() << " is " << adjList.GetVertex(vertexNum).GetDist() << endl;
            cout << "The Path is: " << endl;
            adjList.PrintPath(adjList.GetVertex(vertexNum));
            cout << endl;

        exit(0);
}

#endif
