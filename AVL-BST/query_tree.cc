/*
 *  FileName: QueryTree.cpp
 *  Created on: Sep 27, 2018
 *  Author: Tushar Malakar
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
using namespace std;

namespace{

                string GetEnzymeAcronym(const string& db_line, size_t first_slash)
                {
                    string enzyme_acro_ = db_line.substr(0, first_slash);
                    return enzyme_acro_;
                }

                //---------------------------
                bool GetNextRecognitionSequence(string db_line, string& a_reco_seq, size_t& first_slash)
                {
                int length;
                size_t next_slash = db_line.find("/", first_slash+1);
                if (next_slash == first_slash + 1) //see if there are two '/' in a row
                   return false; //there are no more recognition sequences (all db_lines end in "//")
                else {
                   length = next_slash-first_slash-1;
                   a_reco_seq = db_line.substr(first_slash+1, length);
                   first_slash = next_slash;
                   return true;
                     }
                }

                //---------------------------
                template <typename TreeType>
                void QueryTree (string db_filename, TreeType &a_tree)
                {
                ifstream inStream(db_filename);
                if (inStream.fail()) {
                    cerr <<"Filename not found." << endl;
                    exit(1);
                }
                else {
                  string db_line, an_enz_acro, a_reco_seq, garbage_line;
                  for (int i = 0; i < 10; i ++)                               //Skip over the header and begin reading on line 11.
                     getline(inStream, garbage_line);
                   while (getline (inStream, db_line)) {                  //inStream has reached line 11 and will begin to parse data.
                   if (db_line.empty()) continue;
                   size_t first_slash = db_line.find("/");
                   an_enz_acro = GetEnzymeAcronym(db_line, first_slash);
                   while (GetNextRecognitionSequence(db_line, a_reco_seq, first_slash)) {
                     SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
                     a_tree.insert(new_sequence_map);
                    }
                   }
                  }
                 }
                }
int main(int argc, char **argv) {
    if (argc != 4) {

        cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
        return 0;
    }

    string db_filename(argv[1]);
    string str1(argv[2]);
    string str2(argv[3]);
    cout << "Input file is " << db_filename << " ";
    cout << "String 1 is " << str1 << "   and string 2 is " << str2 << endl;

    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
    a_tree.rot(str1);
    return 0;
}


