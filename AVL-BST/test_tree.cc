#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"

template <typename TreeType>
class testTree {
public:
    //construct a test-tree
    testTree(std::string database, std::string query) : db_filename(database), query_filename(query) {
        Query();
    }


    //combine all the functions
    void TestQuery()
{
    std::cout << "2: " << a_tree.count_Nodes() << " \n";
    std::cout << "3a: " << a_tree.calculate_Avg_Depth() << " \n";
    std::cout << "3b: " << a_tree.calculate_ratio() <<" \n";
    search_Sequences();
    remove_Sequences();
    std::cout << "6a: "<< a_tree.count_Nodes() << " \n";
    std::cout << "6b: " << a_tree.calculate_Avg_Depth() << " \n";
    std::cout << "6c: " << a_tree.calculate_ratio() <<" \n";
}

private:
    std::string db_filename;
    std::string query_filename;
    TreeType a_tree;
    //function to insert insert and check file
    void Query () {
    ifstream inStream(db_filename);
    if (inStream.fail()) {
        std::cerr <<"Filename not found." << std::endl;
        exit(1);}
    else {
    std::string db_line, an_enz_acro, a_reco_seq, garbage_line;
    for (int i = 0; i < 10; i ++)                               //Skip over the header and begin reading on line 11.
        getline(inStream, garbage_line);
    while (std::getline (inStream, db_line)) {                  //inStream has reached line 11 and will begin to parse data.
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
    //function to recognize slash in a string
    std::string GetEnzymeAcronym(std::string db_line, size_t first_slash) {
    std::string enzyme_acro_ = db_line.substr(0, first_slash);
    return enzyme_acro_;
}

    bool GetNextRecognitionSequence(std::string db_line, std::string& a_reco_seq, size_t& first_slash) {
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


    void search_Sequences()
{
    ifstream inStream(query_filename);
    std::string sequence;
    int success_query_count = 0, total_queries = 0, recursion_calls = 0, sum_recursion_calls = 0, avg_recursion_calls;
    while(std::getline(inStream, sequence)) {
        if (sequence.empty()) continue;
        total_queries++;
        if (a_tree.find(sequence, recursion_calls))
            success_query_count++;
        sum_recursion_calls += recursion_calls;
    }
    avg_recursion_calls = sum_recursion_calls / total_queries;
    std::cout << "4a: " << success_query_count  << std::endl;
    std::cout << "4b: " << avg_recursion_calls  << std::endl;
}

    void remove_Sequences()
{
    ifstream inStream(query_filename);
    std::string sequence;
    int every_other = 0, success_delete_count = 0, recursion_calls = 0, sum_recursion_calls = 0, total_calls = 0;
    while (std::getline(inStream, sequence)) {
        if (sequence.empty()) continue;
        if (every_other % 2 == 0) {           //If it is even, call remove().
            total_calls++;
            if (a_tree.remove(sequence, recursion_calls))             //remove sequence from a_tree
                success_delete_count++;

            sum_recursion_calls += recursion_calls;     //Even if delete wasn't successfully
        }
        every_other++;
    }

    double avg_recursion_calls = sum_recursion_calls / total_calls;
    std::cout << "5a: " << success_delete_count << std::endl;
    std::cout << "5b: " << avg_recursion_calls << std::endl;
}
};

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0]<< " <databasefilename> <queryfilename> <tree-type>" << endl;
        cout <<"Try \n './test_tree rebase210.txt input_part2a.txt BST' \n\n";
        return 0;
    }
    string db_filename(argv[1]);
    string query_filename(argv[2]);
    string param_tree(argv[3]);
    cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;

    if (param_tree == "BST") {
        std::cout << "\nType of tree is BST" << std::endl;
        testTree<BinarySearchTree<SequenceMap>> a_tree(db_filename, query_filename);
        a_tree.TestQuery();
    } else if (param_tree == "AVL") {
        std::cout << "\nType of tree is AVL" << std::endl;
        testTree<AvlTree<SequenceMap> > a_tree(db_filename, query_filename);
        a_tree.TestQuery();
    } else
        std::cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << std::endl;
    return 0;
}
