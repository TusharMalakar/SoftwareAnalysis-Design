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


 string removeSpaces(string word) {
    string newWord;
    for (int char_ = 0; char_ < word.length(); char_++) {
        if (word[char_] != ' ') {
            newWord += word[char_];
        }
    }

    return newWord;
}

 // order matter in string, e.g. "01" != "10"
 //numbers of permutation = n! / (n-r)! , where n= set size and r= permutation length
// The main recursive method to print all possible strings of length "length"
void permutation_of_Char(const char str[], string prefix, const int n, const int length){

    //Base case: length = 1, print the string "length" times + the remaining letter
    if (length == 1){
            //if password length is 1 and set = {0-9},
            //then there is only 10 possible passwords
            for (int j = 0; j < n; j++){
                    //converting char to string concatenating with string
                    // pass word = "" + j'th char of str
                    string password = prefix + str[j];
                    //cout << endl << prefix + str[j] <<endl;
                    password = removeSpaces(password);
                    Char_password.push_back(password);
            }
    }
    else{
       // One by one add all characters from "str" and recursively call for "length" equals to "length"-1
        for (int i = 0; i < n; i++){

            // Next character of input added
            // "length" is decreased, because we have added a new character
            permutation_of_Char(str, prefix + str[i], n, length - 1);
            // if const char str[] = {'0', '1'} && n == 2; e.g. str [] length = 2 && prefix == "";

                // after 1st iteration =  permutation_of_Char( {'0', '1'} , "0" , 2 , 1);
                // after 2nd iteration =  permutation_of_Char( {'0', '1'} , "01" , 2 , 0);
        }

    }

}

void print_vector(vector<string> str_vector){
    for (auto i = str_vector.begin(); i != str_vector.end(); ++i)
        cout << *i << " ";
}

vector<string> concate_with_Char_password(vector <string> new_vector){
    Char_password.insert(Char_password.end(), new_vector.begin(), new_vector.end());
    return Char_password;
}

int find_one(vector <string> my_vector, string str){
    vector<string>::iterator it;
    it = find(my_vector.begin(), my_vector.end(), str);
    if (it != my_vector.end())
    {
        //cout << "Element " << str <<" found at position : " ;
        //cout << it - my_vector.begin() + 1 << "\n" ;
        int position = it - my_vector.begin() + 1 ;
        return position;
    }
    else
        //cout << "Element not found.\n\n";
        return -1;
}

int main(){

    //base case:
    char num[] = {'A', 'B', 'C'};
    permutation_of_Char(num, " ", sizeof num, 1);
    cout << "Base case : ";
    print_vector(Char_password);

    //inductive case:
    permutation_of_Char(num, " ", sizeof num, 2);
    cout << endl << "Inductive case : ";
    print_vector(Char_password);
    cout << find_one(Char_password, "BB");



    /**
    char num[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    //number password length 4
    permutation_of_Char(num, "", sizeof num, 4);
    print_vector(Char_password);


    //number password length 5
    permutation_of_Char(num, "", sizeof num, 5);
    print_vector(Char_password);
    **/

     /**
    //number password length 6
    permutation_of_Char(num, "", sizeof num, 6);

    //number password length 7
    permutation_of_Char(num, "", sizeof num, 7);

    **/



    /**
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
    **/


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

