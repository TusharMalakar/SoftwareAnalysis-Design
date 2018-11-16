/*
 *  sorting_algorithms.h
 *  Created on: November 12, 2018
 *  Author: Tushar Malakar
 */
#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <functional>


using namespace std;

class sorting_algorithms {

 public:


 /*function should return true iff the input is in ascending order.*/
 template <typename Comparable, typename Comparator>
 bool AscendOrder(vector<Comparable> & arr, Comparator last){
      bool ascend;

      for(unsigned int i=0; i < last ; i++){
          if (arr[last-1] < arr[last-2])
                ascend = false;
          else
                 ascend = true;
      }
      return ascend;
 }

 /*function should return true iff the input is in descending order.*/
 template <typename Comparable, typename Comparator>
 bool DecendOrder(vector <Comparable> & arr, Comparator last){
      bool descen;

      for(unsigned int i=0; i < last ; i++){
          if (arr[last-1] > arr[last-2])
                descen = false;
          else
                 descen = true;
      }
      return descen;
 }


 template <typename Comparable, typename Comparator>
 void insertionsort(vector <Comparable> & a, Comparator less_than){
   int key, i, j;
   for ( i = 1; i < less_than; i++){

       key = a[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while ( j >= 0 && a[j] > key){

           a[j+1] = a[j];
           j = j-1;
       }
       a[j+1] = key;
   }
 }

 template <typename Comparable, typename Comparator>
 void mergesort(vector <Comparable> & a, Comparator less_than){

      mergesort(a, 0, less_than-1);
 }

 template <typename Comparable, typename Low, typename High>
 void mergesort(vector <Comparable> &a, Low low, High high){
     if(low >= high)
                return;
     else{
                int mid = (low + high)/2;
                mergesort(a,low,mid);
                mergesort(a, mid+1, high);
                merge_(a, low, mid, mid+1, high);
     }
 }

 template <typename Comparable, typename LeftLow, typename LeftHigh, typename RightLow,typename RightHigh>
 void merge_(vector <Comparable> &a, LeftLow lLow, LeftHigh lHigh, RightLow rLow, RightHigh rHigh){

     int length = rHigh - lLow+1 ;
     int temp[length];
     int left = lLow;
     int right = rLow;
     for (int i = 0; i<length; ++i){
                if(left > lHigh)
                    temp[i] = a[right++];
                else if(right > rHigh)
                    temp[i] = a[left++];
                else if(a[left] <= a[right])
                    temp[i] = a[left++];
                else
                    temp[i] = a[right++];

     }

     for(int i=0; i<length; ++i)
                a[lLow++] = temp[i];
 }
 /* Function to print an vector */
template <typename Comparable>
void display(vector <Comparable> & arr, int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    cout<<(" ");
}

 // function build Max Heap where value
// of each child is always smaller
// than value of their parent
 template <typename Comparable, typename Comparator>
 void BuildMaxHeap(vector <Comparable> & arr, Comparator n){

    for (int i = 1; i < n; i++){

        // if child is bigger than parent
        if (arr[i] > arr[(i - 1) / 2]){

            int j = i;

            // swap child and parent until
            // parent is smaller
            while (arr[j] > arr[(j - 1) / 2]){

                swap_(arr[j], arr[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }
    }
 }

template <typename Comparable, typename Comparator>
void heapSort(vector <Comparable> & arr, Comparator n){

    BuildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; i--){

        swap_(arr[0], arr[i]); // swap value of first  with last
        int j = 0, index; // maintaining heap property

        do{

            index = (2 * j + 1);

            // if left child is smaller than
            // right child point index variable
            // to right child
            if (arr[index] < arr[index + 1] &&
                                index < (i - 1))
                index++;

            // if parent is smaller than child
            // then swapping parent with child
            // having higher value
            if (arr[j] < arr[index] && index < i)
                swap_(arr[j], arr[index]);

            j = index;

        } while (index < i);
    }
 }
 // A utility function to swap two elements
template <typename Comparable>
void swap_(Comparable* a, Comparable* b)
{
    Comparable t = *a;
    *a = *b;
    *b = t;
}
template <typename Comparable>
void swap_(Comparable & a, Comparable & b) {
  Comparable t = a;
    a = b;
    b = t;
 }

/*QuickSort  It picks an element as pivot and partitions the given
 array around the picked pivot. There are many different versions of
 quickSort that pick pivot in different ways:

               1) Always pick first element as pivot.
               2) Always pick last element as pivot (implemented below)
               3) Pick a random element as pivot.
               4) Pick median as pivot.
 then, sort the smaller elements to left and larger to right to pivot,
 using linear time.
**/

/*Partition Algorithm:
 There can be many ways to do partition, following pseudo code adopts the
 method given in CLRS book. The logic is simple, we start from the leftmost
 element and keep track of index of smaller (or equal to) elements as i.
 While traversing, if we find a smaller element, we swap current element
 with arr[i]. Otherwise we ignore current element.
 **/

/*
 The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index
*/
  template <typename Comparable>
  void quickSort(vector <Comparable> & vec, int high){
      quickSort(vec, 0, high);
  }

 template <typename Comparable>
 void quickSort(vector<Comparable> & arr, int low, int high){

    if (low < high){

        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = lastPivot(arr, low, high);

        // Separately sort elements before
        // lastPivot and after lastPivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

 template <typename Comparable>
 void firstPivot(vector<Comparable> &numList,int right){
      firstPivot(numList, 0, right);
 }


 template <typename Comparable>
 void firstPivot(vector<Comparable> &numList,int left,int right){

    int i=left,j=right;// the left side of the pivot// the right side of the pivot//for swapping
    int pivot=numList[left];// pivot is first element now
    if (left+right<10){ // if the amount of elements are less than 10 insertion sort is applied

                insertionsort(numList,right);
     }
     else{
         while(i<=j){     // it loops through the whole array

                while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                i++;
                }

                while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                   j--;


                   if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped

                      int temp=numList[i];
                      numList[i]=numList[j];
                      numList[j]=temp;
                      i++;
                      j--;
                   }
                }
                // sort the left side
                if (left<j) {

                   firstPivot(numList,left,j);

                }
                //sort the right side;
               if (i<right) {

                   firstPivot(numList,i,right);
                }
         }
   }
 }
 /* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
template <typename Comparable>
const Comparable lastPivot (vector <Comparable> &arr, int high){
      lastPivot(arr, 0, high);
}
template <typename Comparable>
const Comparable lastPivot (vector <Comparable> &arr, int low, int high){
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap_(&arr[i], &arr[j]);
        }
    }
    swap_(&arr[i + 1], &arr[high]);
    return (i + 1);
 }
 template <typename Comaparable>
 const Comaparable randomPivot(vector <Comaparable> & arr, int high){
       randomPivot(arr, 0, high);
  }

template <typename Comaparable>
 const Comaparable randomPivot(vector <Comaparable> & arr, int low, int high){

    // Generate a random number in between
    // low .. high
    srand(time(NULL));
    int random = low + rand() % (high - low);

    // Swap A[random] with A[high]
    swap(arr[random], arr[high]);

    return lastPivot(arr, low, high);
 }
template <typename Comparable >
const Comparable medianofThree(vector <Comparable> & numList, int high){
                medianofThree(numList, 0, high);
}
template <typename Comparable >
const Comparable medianofThree(vector<Comparable>&numList,int left,int right){ // puts the three number in order then takes one before the last number (n-1*) and returns as pivot
           int middle=(left+right)/2;
            if (numList[middle]<numList[left]){
  
