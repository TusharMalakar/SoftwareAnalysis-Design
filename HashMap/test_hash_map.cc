/*
 *  test_hash_map.cc
 *  Created on: October 27, 2018
 *  Author: Tushar Malakar
 */



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include "quadratic_probing.h"
using namespace std;


class Test_Hash_Map{

  private:
     ifstream inStream;
     string word;
     vector<string> Array;


 public:
  void OpenFile(string && filename){

                inStream.open((filename));
                if(inStream.fail()){

                cout << "Error, file not found." << endl;
                exit(1);

                }
 }

 void insertWord(){

     while(inStream >> word)
     Array.push_back(word);

 }


 HashMap<string,vector<string>> adjacentWordTime(const int size){


    const auto begin = chrono::high_resolution_clock::now();

   HashMap<string,vector<string>> adjacentWords = computeAdjacentWords(size);
   const auto end = chrono::high_resolution_clock::now();

                cout << "Time to build map: " << endl;

                cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
                cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;

   return adjacentWords;
}


HashMap<string,vector<string>> computeAdjacentWords(const int size){

        HashMap<string,vector<string>> adjacentWords(size);

        HashMap<int, vector<string>> wordsByLength(100000);

       // Group the words by their length
       for( auto & thisWord : Array )
         wordsByLength[thisWord.length( )].push_back( thisWord );

       // Work on each group separately
       for( auto entry = wordsByLength.begin(); entry != wordsByLength.end(); ++entry ) {

          const vector<string> & groupsWords = entry->map_;

         // Start putting adjacent words into vectors
         for( int i = 0; i < groupsWords.size( ); ++i )

           for( int j = i + 1; j < groupsWords.size( ); ++j )

                 if( CharOff( groupsWords[i], groupsWords[j])) {


                  adjacentWords[groupsWords[i]].push_back( groupsWords[j]);
                  adjacentWords[groupsWords[j]].push_back( groupsWords[i]);
                                }
       }
         return adjacentWords;
}



 void findAdjacentTime(const HashMap<string, vector<string>> & adjacentWords){

         string currentWord;

         cout << "\nEnter a word to find similar word." << endl;
         cin >> currentWord;

         const auto begin = chrono::high_resolution_clock::now();

         findAdjacentWords(currentWord,adjacentWords);
         const auto end = chrono::high_resolution_clock::now();

 }

 void findAdjacentWords(string currentWord, const HashMap<string, vector<string>> & adjacentWords){

       if( adjacentWords.contains( currentWord ) ) {

      // Gets a vector of the user inputted key
      auto adjacentVector = adjacentWords.find( currentWord );

                cout << "Input word: " << currentWord << endl;


      for(auto & itr : adjacentVector)

                cout << itr << endl ;
       }

      else
              cout << "Could not find word." << endl;

}



 bool CharOff(const string & word1, const string & word2){

      if( word1.length( ) != word2.length( ) )
                return false;

      int diffs = 0;

      for( int i = 0; i < word1.length( ); ++i )

                if( word1[ i ] != word2[ i ] )
                   if( ++diffs > 1 )
                    return false;

     return diffs == 1;

 }



 void display(HashMap<string,vector<string>> adjacentWords){

      //Uses iterators to print out every word placed into the HashMap
      for( auto itr = adjacentWords.begin(); itr != adjacentWords.end(); ++itr ) {

                if( itr->map_.size() != 0 ){
                  cout << itr->element << " ";

                  for( auto & itr2 : itr->map_ )
                    cout << itr2 << " ";
                }

                if( itr->map_.size() != 0 )
                   cout << "\n";
      }
 }

};

int main( int argc, char **argv ) {

    if (argc != 3) {

      cout << "\n   Usage: " << argv[0] << " <filename>" << "<HashTable Size>" << endl;
      cout << "  Try :\n     ./test_hash_map words.txt 10000 " << endl ;
       return 1;
    }

    int size = atoi(argv[2]); //sets the size that the user enters
    string choice; //choice to print out the HashMap

    Test_Hash_Map Hash;
    Hash.OpenFile(argv[1]); //opens file that the user enters

    Hash.insertWord();
    HashMap<string, vector<string>> adjacentWords = Hash.adjacentWordTime(size);

    Hash.findAdjacentTime(adjacentWords);

    Hash.findAdjacentTime(adjacentWords);

    char letter;
    cout<< "Enter 'T' to see the entire tabel: \n (or) Anything else to exit.";
                cin >> letter;
                switch(letter)
                {

                case 'T' : //code
                                Hash.display(adjacentWords);
                                break;

                default : //code
                                cout<<"\n             **Thanks for using my HashTable**";
                                exit(0);
                }


}
