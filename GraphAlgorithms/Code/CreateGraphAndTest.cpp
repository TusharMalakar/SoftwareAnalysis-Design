/*
 *  FileName: CreatedGraphAndTest.cpp
 *  Created on: November 27, 2018
 *  Author: Tushar Malakar
 */
#include "simulator.h"
int main(int argc, const char * argv[]){
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <filename>" << " <starting vertex #>" << std::endl;
        return 1;
    }
    Simulator simultor;
    simultor.OpenFile(argv[1]);
    simultor.CreateGraph();
    simultor.CheckAdj(atoi(argv[2]));
    return 0;
}
