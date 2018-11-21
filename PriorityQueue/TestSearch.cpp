/** @file TestSearch.cpp */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

int main(int argc, char const *argv[])
{
	cout << "\n" << endl;

	//Create PriorityQueue.
	PriorityQueue<int> a_priority_queue;

	string create_filename(argv[1]);
  	string search_filename(argv[2]);

	int create_input, search_input;
 	ifstream create_file(create_filename); 
	ifstream search_file(search_filename);

	//Check if file names are correct.
	if (create_file.is_open() && search_file.is_open()) 
	{
		//Read in file and insert into PQ.
		while (create_file >> create_input)
	  		a_priority_queue.Insert(create_input);

	  	//Read in file and test PQ for contents.
		while (search_file >> search_input)
		{
	  		if(a_priority_queue.Find(search_input))
	  			cout << search_input << " Found" << endl;
	  		else
	    		cout << search_input << " Not Found" << endl;
		}
	}

	//Prompt user with file error.
	else
		cout << "Could not open files, please check file name, and try again." << endl;

	cout << "\n" << endl;
	return 0;
}