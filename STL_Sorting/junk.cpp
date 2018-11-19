/*
 *  test_sorting_algorithms.cpp
 *  Created on: November 1, 2018
 *  Author: Tushar Malakar
 */
 #include <iostream>
#include "sorting_algorithms.h"

using namespace std;

int main()
{


    sorting_algorithms Sort;
    std::cout << std::boolalpha;
    vector<int> foo = {0,1};
    std::cout << Sort.AscendOrder(foo,2)  << '\n';
    vector<int> boo = {7,4};
    std::cout << Sort.DecendOrder(boo,2) << '\n';

    vector <int> arrr = {10, 7, 8, 9, 1, 5};
    //int n = sizeof(arr)/sizeof(arr[0]);
    int nn = arrr.size();
    Sort.quickSort(arrr, 0, nn-1);
    cout<<"Sorted array: ";
    Sort.display(arrr, nn);


    vector<int>  arr = {12, 11,40,29,939,333};
    int n = arr.size();
    Sort.insertionsort(arr, n);
    std::cout<<("\nInsertion Sorted array: ");
    Sort.display(arr,n);


    vector<int> arr__ = {12, 1, 13, 5, 6, 7};
    //int arr_size = arr__.size();
    Sort.mergesort(arr__,arr__.size());
    std::cout<<("\nMerge Sorted array is : ");
    Sort.display(arr__, arr__.size());


    vector <int> arr2 = {12, 11, 13, 5, 6};
    int n2 = arr2.size();
    Sort.heapSort(arr2,n2);
     std::cout<<("\nHeap Sorted array: ");
    Sort.display(arr2, n2);


     //------------------
    vector <int> arra = {10, 7, 8, 9, 1, 5};
    int i = arra.size();
    Sort.quickSort(arra,0,i-1);
    std::cout<<("\nQuick Sorted array: ");
    Sort.display(arra, i);

}
