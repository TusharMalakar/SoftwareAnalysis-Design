/** @file TestDelete.cpp */


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
  	string delete_filename(argv[2]);

	int create_input, delete_input, total=0, tmp = 0;
 	ifstream create_file(create_filename); 
	ifstream delete_file(delete_filename);

	//Check if file names are correct.
	if (create_file.is_open() && delete_file.is_open()) 
	{

		//Read in file and insert into PQ, increment total each time.
		while (create_file >> create_input)
		{
			a_priority_queue.Insert(create_input);
			++total;
		}

		//Print first successful inserting message.
		cout << "Success inserting " << total <<  " elements into the queue."
			 << " The minimum element is " << a_priority_queue._heap.findMin() << '.' << endl;

		//Delete fist item and place into tmp.
		a_priority_queue._heap.deleteMin(tmp);
		cout << tmp << " Deletion successful!" << endl;

		//Read in delete file.
		while (delete_file >> delete_input)
		{
			cout << endl;
			//Remove item from PQ.
	  		while(a_priority_queue.Remove(delete_input))
	  			cout << delete_input << " deleted from queue." << endl;

	  		// Check if delete was successful. 
  			if (a_priority_queue.Find(delete_input)) 
				cout << "Serious problem with deletion routine... Need to debug..." << endl; 
			else 
				cout << "Deletion successful" << endl; 
		}
	}

	
	//Prompt user with file error.
	else
		cout << "Could not open files, please check file name, and try again." << endl;

	cout << "\n" << endl;
	return 0;
}