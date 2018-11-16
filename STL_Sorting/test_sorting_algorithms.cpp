/*
 *  test_sorting_algorithms.cpp
 *  Created on: November 12, 2018
 *  Author: Tushar Malakar
 */
 #include <iostream>
 #include <chrono>
#include "sorting_algorithms.h"

using namespace std;

int main( int argc, char **argv ){

    if(argc != 4) {

        cout << "\n    Usage :  " << argv[0]<< " <input_type> <input_size> <comparison_type>" <<'\n';

        cout<<"\nEnter your <input_type> , can be random or sorted :"<<endl;
        cout<<"Enter the number of element as <input_size> :"<<endl;
        cout<<"Enter the <comparison_type> as less or greater :"<<endl;

        cout<< "\n TRY :\n  ./test_sorting_algorithms random 20000 less  ";
        return 1;
    }


    sorting_algorithms sorter;
    string input_type = argv[1];
    int input_size = atoi(argv[2]);
    string comparison_type = argv[3];
    vector <int> vect (input_size);


    sorter.GenerateRandomVector(vect,input_size);

    if(sorter.AscendOrder(vect,input_size) == false ){
                cout<<"\nPart 1 :  \n";
                cout<<"Running sorting algorithms: "<<input_type<<", "<<input_size<<", "<<comparison_type<<'\n';

                cout << "HeapSort : Runtime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.heapSort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : HeapSort\n";
                }

    }
    sorter.GenerateRandomVector(vect,input_size);
    if(sorter.AscendOrder(vect,input_size) == false ){
                cout << "MergeSort : Runtime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.mergesort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : MergeSort\n";
                }

    }
    sorter.GenerateRandomVector(vect,input_size);
    if(sorter.AscendOrder(vect,input_size) == false ){
                cout << "QuickSort : Runtime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.quickSort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : QuickSort\n";
                }

    }



    sorter.GenerateRandomVector(vect,input_size);
    if(sorter.AscendOrder(vect,input_size) == false ){

                cout<<"\nPart 2 :  \n";
                cout<<"Testing QuickSort: "<<input_type<<", "<<input_size<<", "<<comparison_type<<'\n';
                cout << "Median of three \nRuntime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.medianofThree(vect,input_size);
                sorter.quickSort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : Median of Three.\n";
                }

    }
    sorter.GenerateRandomVector(vect,input_size);
    if(sorter.AscendOrder(vect,input_size) == false ){
               cout << "Random \nRuntime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.randomPivot(vect,input_size);
                sorter.quickSort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : Random Pivot.\n";
                }

    }
    sorter.GenerateRandomVector(vect,input_size);
    if(sorter.AscendOrder(vect,input_size) == false ){
                cout << "First \n Runtime: ";

                const auto begin = chrono::high_resolution_clock::now();
                sorter.firstPivot(vect,input_size);
                sorter.quickSort(vect,input_size);
                const auto end = chrono::high_resolution_clock::now();
                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                if(sorter.AscendOrder(vect,input_size) == true){
                  cout<< "Verified : First Pivot.\n ";
                }

    }
    else
         cout<< "Please Enter a right format to see the runtime.";
         cout<< "\n TRY :\n  ./test_sorting_algorithms random 20000 less \n";








}
