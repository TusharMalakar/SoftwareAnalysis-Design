#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;
/**
a vector to store all possible passwords of decimal-
numbers length 4 to 7
*/
 vector<string> Char_password;

// The main recursive method to print all possible strings of length "length"
void permutation_of_Char(const char str[], string prefix, const int n, const int length){

    if (length == 1){
            for (int j = 0; j < n; j++){

                    string password = prefix + str[j];
                    cout << endl << prefix + str[j] <<endl;
                    Char_password.push_back(password);
            }
    }//Base case: length = 1, print the string "length" times + the remaining letter
    else{
       // One by one add all characters from "str" and recursively call for "length" equals to "length"-1
        for (int i = 0; i < n; i++){

            // Next character of input added
            permutation_of_Char(str, prefix + str[i], n, length - 1);
            // "length" is decreased, because we have added a new character
        }

    }

}

void print_vector(vector<string> str_vector){
    for (auto i = str_vector.begin(); i != str_vector.end(); ++i)
        cout << *i << " ";
}



int main(){

    char num[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    //number password length 4
    permutation_of_Char(num, "", sizeof num, 4);
    print_vector(Char_password);

    /*
    //number password length 5
    permutation_of_Char(num, "", sizeof num, 5);

    //number password length 6
    permutation_of_Char(num, "", sizeof num, 6);

    //number password length 7
    permutation_of_Char(num, "", sizeof num, 7);

    */



    /*
    auto start = high_resolution_clock::now();

    char str[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    //Note: this function works on all cases and not just the case above
    //permutation of length 4
    permutation_of_Char(str, "", sizeof str, 4);

    // After function call
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

     // To get the value of duration use the count()
    // member function on the duration object
    cout << duration.count() << endl;
    */


    /**  TRY Other permutation length ****

        //permutation of length 5
        permutation_of_Alphabets(str, "", sizeof str, 5);

        //permutation of length 6
        permutation_of_Alphabets(str, "", sizeof str, 6);

        //permutation of length 7
        permutation_of_Alphabets(str, "", sizeof str, 7);

    **/

    return 0;
}
