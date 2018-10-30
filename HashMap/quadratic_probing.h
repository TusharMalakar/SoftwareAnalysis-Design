/*
 *  quadratic_probing.h
 *  Created on: October 27, 2018
 *  Author: Tushar Malakar
 */


#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "is_prime.h"
using namespace std;

prime getPrime;

// QuadraticProbing Hash table class
template<typename HashKey, typename HashValue>
class HashMap
{
  public:
    enum EntryType { ACTIVE, EMPTY, DELETED };
  private:

     struct HashEntry{

            HashKey element;
            HashValue map_;
            EntryType info;

       HashEntry( const HashKey & v = HashKey{ },const HashValue & m = HashValue{ },
                EntryType i = EMPTY ): element{v}, map_{m}, info{i} { }


       HashEntry( HashKey && v, HashValue && m,EntryType i = EMPTY )
                                 : element{ std::move( v ) }, map_{ std::move( m ) }, info{ i } { }
                   };


 vector<HashEntry> mapArray;
 int currentSize;


 bool isActive( int currentPos ) const{
    return mapArray[ currentPos ].info == ACTIVE;
                }

 int findPos( const HashKey & key ) const{
                int offset = 1;
                int currentPos = myhash( key );

                while( mapArray[ currentPos ].info != EMPTY && mapArray[ currentPos ].element != key ){
                currentPos += offset;  // Compute ith probe
                                offset += 2;
                if( currentPos >= mapArray.size( ) )
                                currentPos -= mapArray.size( );
                if( mapArray[ currentPos ].element == key )
                                break;
                                }
                 return currentPos;
                }


 //Rehashes the current map to double the size for Quadratic Probing efficiency.
 void rehash(){
      vector<HashEntry> oldArray = mapArray;
      // Create new double-sized, empty table
      mapArray.clear();
      mapArray.resize( getPrime.nextPrime( 2 * oldArray.size( ) ) );
      // Copy table over
      currentSize = 0;
     for( auto & entry : oldArray )
       if( entry.info == ACTIVE )
                insert( std::move( entry.element ), std::move( entry.map_ ) );
               }

 //Retrieves the hash value of a key (Algorithm from textbook)
 size_t myhash( const HashKey & key) const{
     static hash<HashKey> hf;
      return hf( key ) % mapArray.size();
 }


public:
  explicit HashMap( int size ) : mapArray( getPrime.nextPrime( size ) ){ makeEmpty(); }

//Deletes entire map using Lazy Deletion.

//If Active and if part of the map, returns true.
 bool contains( const HashKey & key ) const{
   return isActive( findPos( key ) );
 }
                void makeEmpty( ){
                currentSize = 0;
                for( auto & entry : mapArray )
                                entry.info = EMPTY;
}

 //Copies the key and object, placing it into the map.
 bool insert( const HashKey & key, const HashValue & obj ){
  // Find key hash value
  int currentPos = findPos( key );

   if( isActive( currentPos ) )
          return false;

           // Insert Items
           mapArray[ currentPos ].element = key;
           mapArray[ currentPos ].map_ = obj;
           mapArray[ currentPos ].info = ACTIVE;

          if( ++currentSize > mapArray.size( ) / 2 )
                rehash( );

       return true;
 }

 //Moves a key and object, placing it into the map and then destroying the rvalue.
 bool insert( const HashKey && key, const HashValue && obj ){
 // Find key hash value
  int currentPos = findPos( key );
  if( isActive( currentPos ) )
        return false;

    // Move Items in mapArray
    mapArray[ currentPos ].element = std::move( key );
    mapArray[ currentPos ].map_ = std::move( obj );
    mapArray[ currentPos ].info = ACTIVE;

    if( ++currentSize > mapArray.size( ) / 2 )
                rehash( );

       return true;
}

//Removes one object from map using lazy deletion
 bool remove( const HashKey & key ){
     int currentPos = findPos( key );
     if( !isActive( currentPos ) )
                return false;

        mapArray[ currentPos ].info = DELETED;
                return true;
 }


//Finds a key if active and if part of the map, and returns the hashvalue.
//otherwise returns a hashvalue of nothing.
 HashValue find( const HashKey & key ) const{

     int currentPos = findPos ( key );
     if( isActive( currentPos ) )
         return mapArray[ currentPos ].map_;
     else {
         HashValue empty;
         return empty;
        }
 }

//Overloaded Bracket Operator, acting much in the same way as a Map's Bracket Operator. Retrieves the
//HashValue of a Key, Otherwise, it inserts the key into a spot and returns the empty map.
 HashValue & operator[]( const HashKey & key ){

       int currentPos = findPos( key );
        if( !isActive( currentPos ) ) {

                 if(mapArray[ currentPos ].info == DELETED)
                    mapArray[ currentPos ].info == ACTIVE;

                  else{
                  // Insert key as active
                     mapArray[ currentPos ].element = key;
                     mapArray[ currentPos ].info = ACTIVE;
                     if( ++currentSize > mapArray.size( ) / 2 )
                                rehash( );
                     }
                }

                return mapArray[ currentPos ].map_;
 }




//Overloaded Bracket Operator, acting much in the same way as a Map's Bracket Operator. Retrieves the HashValue of a Key,
//Otherwise, it moves the key into a spot and returns the empty map.
HashValue & operator[]( const HashKey && key ){

   int currentPos = findPos( key );

    if( !isActive( currentPos ) ) {
      if(  mapArray[ currentPos ].info == DELETED )
                 mapArray[ currentPos ].info == ACTIVE;

       else{
       // Insert key as active
      mapArray[ currentPos ].element = key;
      mapArray[ currentPos ].info = ACTIVE;
      if( ++currentSize > mapArray.size( ) / 2 )

                rehash( );
                }
     }

      return mapArray[ currentPos ].map_;
}



    typedef typename std::vector<HashEntry>::iterator iterator;
    typedef typename std::vector<HashEntry>::const_iterator const_iterator;
    iterator begin(){ return mapArray.begin(); }
    const_iterator begin() const { return mapArray.begin(); }
    iterator end() { return mapArray.end(); }
    const_iterator end() const { return mapArray.end(); }
};
#endif
