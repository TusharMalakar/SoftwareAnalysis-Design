/*
 *  test_sorting_algorithms.cpp
 *  Created on: November 1, 2018
 *  Author: Tushar Malakar
 */
 #include <iostream>
#include "sorting_algorithms.h"

using namespace std;

int main( int argc, char **argv ) {

    if (argc != 3) {

      cout << "\n   Usage: " << argv[0] << " <filename>" << "<HashTable Size>" << endl;
      cout << "  Try :\n     ./test_hash_map words.txt 10000 " << endl ;
       return 1;
    }

    int size = atoi(argv[2]); //sets the size that the user enters
    string choice; //choice to print out the HashMap

    sorting_algorithms Sort;

    //Sort.OpenFile(argv[1]); //opens file that the user en



}
