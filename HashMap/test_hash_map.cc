#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "quadratic_probing.h"

using namespace std;


template <typename HashTableType>
void TestComputeAdjacentWords(HashTableType &hash_table, const vector<string> &words) {
  // This is for computing timing.
  const auto begin = chrono::high_resolution_clock::now();

  hash_table.MakeEmpty();
  //..Insert your own code using algorithm described in Figure 4.73

  const auto end = chrono::high_resolution_clock::now();

  cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;
}

vector<string> ReadWordsFromFile(const string &words_filename) {
  vector<string> the_words;
  // Implement this...
  return the_words;
}

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " words_file_name hash_type (quadratic or double)" << endl;
    cout<<"   Try : \n   'test_hash_map words.txt quadratic'\n";
    return 0;
  }

  const string words_filename(argv[1]);
  const vector<string> the_words = ReadWordsFromFile(words_filename);

  const string param_flag(argv[2]);

  if (param_flag == "quadratic") {
    HashQuadraticProbing<string> quadratic_probing_table;
    TestComputeAdjacentWords(quadratic_probing_table, the_words);
  } else if (param_flag == "double") {
    // HashTableDouble<string> double_probing_table;
    // TestComputeAdjacentWords(double_probing_table, the_words);
  } else {
    cout << "Uknown hash type " << param_flag << " (User should provide quadratic, or double)" << endl;
  }
  return 0;
}
