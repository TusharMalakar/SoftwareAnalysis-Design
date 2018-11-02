/*
 *  sorting_algorithms.h
 *  Created on: November 1, 2018
 *  Author: Tushar Malakar
 */
#include <iostream>
#include <algorithm>

using namespace std;

class sorting_algorithms {

  template <typename Iterator, typename Comparator>
  void insertionSort( const Iterator & begin, const Iterator & end, Comparator lessThan ) {

	if (begin == end)
	  return;

        Iterator J;
	for (Iterator p = begin + 1; p !=end; ++p ){
      		auto tmp = std::move (*p );
		for (j = p; j != begin && lessThan (tmp, *( j-1 ) ); --1)
			*j = std::move (tmp);
	}


  }

  template <typename Comparable>
  void shellSort ( vector <Comparable> & a){

       for (int gap = a.size() / 2; gap >0; gam /=2)

   	for ( int i =gap; i<a.size(); ++i){

		Comparable tmp = std::move(a[i]);
		int j=i;

  		for (; j>= gap && tmp< a[j -gap]; j-= gap)

			a[j] = std::move ( a[j-gap] );
		a[j] = std::move( tmp );
	}
  }


 //Standard heapsort.
 template <typename Comparable>
 void heapsort( vector<Comparable> & a ){

 	for( int i = a.size( ) / 2 - 1; i >= 0; --i ) /* buildHeap */
 		percDown( a, i, a.size( ) );
 	for( int j = a.size( ) - 1; j > 0; --j ){

 		std::swap( a[ 0 ], a[ j ] ); /* deleteMax */
 		percDown( a, 0, j );
 	}
 }

 //Returns the index of the left child.
 inline int leftChild( int i ){

 	return 2 * i + 1;
 }


/**
 * Internal method for heapsort that is used in deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
*/
 template <typename Comparable>
 void percDown( vector<Comparable> & a, int i, int n ){

	int child;
 	Comparable tmp;

 	for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child ){

 		child = leftChild( i );
 		if( child != n - 1 && a[ child ] < a[ child +1])
 			++child;
 		if( tmp < a[ child ] )
 			a[ i ] = std::move( a[ child ] );
 		else
 			break;
 	}

 	a[ i ] = std::move( tmp );
 }


/**
* Mergesort algorithm (driver).
*/
 template <typename Comparable>
 void mergeSort( vector<Comparable> & a ){

	 vector<Comparable> tmpArray( a.size( ) );
 	 mergeSort( a, tmpArray, 0, a.size( ) - 1 );
 }


 /**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
 template <typename Comparable>
 void mergeSort( vector<Comparable> & a,
		vector<Comparable> & tmpArray, int left, int right ){

 	if( left < right ){

	 int center = ( left + right ) / 2;
	 mergeSort( a, tmpArray, left, center );
	 mergeSort( a, tmpArray, center + 1, right );
 	merge( a, tmpArray, left, center + 1, right );
 	}
 }

/**
 * Internal method that merges two sorted halves of a subarray.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* leftPos is the left-most index of the subarray.
* rightPos is the index of the start of the second half.
* rightEnd is the right-most index of the subarray.
*/
 template <typename Comparable>
 void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
				int leftPos, int rightPos, int rightEnd ){

	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

 	// Main loop
 	while( leftPos <= leftEnd && rightPos <= rightEnd )
 		if( a[ leftPos ] <= a[ rightPos ] )
	   		tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
		else
 	   		tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

	while( leftPos <= leftEnd ) // Copy rest of first half
 		tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

 	while( rightPos <= rightEnd ) // Copy rest of right half
 		tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

	// Copy tmpArray back
	for( int i = 0; i < numElements; ++i, --rightEnd )
 		a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
 }


template <typename Comparable>
void SORT( vector<Comparable> & items ){

	if( items.size( ) > 1 ){

		vector<Comparable> smaller;
		vector<Comparable> same;
 		vector<Comparable> larger;

 		auto chosenItem = items[ items.size( ) / 2 ];

		for( auto & i : items ){

			if( i < chosenItem )
 				smaller.push_back( std::move( i ) );
 			else if( chosenItem < i )
 				larger.push_back( std::move( i ) );
 			else
 				same.push_back( std::move( i ) );
 		}

 		SORT( smaller ); // Recursive call!
 		SORT( larger ); // Recursive call!

 		std::move( begin( smaller ), end( smaller ), begin( items ) );
 		std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
 		std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );
 	}
 }


/**
 * Quicksort algorithm (driver).
 */
 template <typename Comparable>
 void quicksort( vector<Comparable> & a ) {

	quicksort( a, 0, a.size( ) - 1 );
 }

/**
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right ){

	int center = ( left + right ) / 2;

 	if( a[ center ] < a[ left ] )
 		std::swap( a[ left ], a[ center ] );
 	if( a[ right ] < a[ left ] )
 		std::swap( a[ left ], a[ right ] );
 	if( a[ right ] < a[ center ] )
 		std::swap( a[ center ], a[ right ] );

 		// Place pivot at position right - 1
 	std::swap( a[ center ], a[ right - 1 ] );
 	return a[ right - 1 ];
}


/**
2 * Internal quicksort method that makes recursive calls.
3 * Uses median-of-three partitioning and a cutoff of 10.
4 * a is an array of Comparable items.
5 * left is the left-most index of the subarray.
6 * right is the right-most index of the subarray.
7 */
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right ){

	if( left + 10 <= right ){

		 const Comparable & pivot = median3( a, left, right );

 		// Begin partitioning
 		int i = left, j = right - 1;
 		for( ; ; ){

 			while( a[ ++i ] < pivot ) { }
 			while( pivot < a[ --j ] ) { }
 			if( i < j )
 				std::swap( a[ i ], a[ j ] );
 			else
 				break;
 		}

 		std::swap( a[ i ], a[ right - 1 ] ); // Restore pivot

 		quicksort( a, left, i - 1 ); // Sort small elements
 		quicksort( a, i + 1, right ); // Sort large elements
 	}
 	else // Do an insertion sort on the subarray
 	insertionSort( a, left, right );
 	}


};


