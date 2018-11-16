
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>



using namespace std;
void textquick_sort(vector<string>& stringFile, int left, int right);
void textquick_randomPiv(vector<string>& stringFile,int left, int right);
 void textquick_firstPiv(vector<string>& stringFile,int left, int right);
 void textquick_sortmedianof3(vector<string>& stringFile,int left, int right);
 void quick_sortrandomPiv(vector<int>& numList,int left,int right);
 void quick_sortfirstPiv(vector<int>& numList,int left,int right);
 void  quick_sort(vector<int>& numList,int left,int right);
 void quick_sort2(vector<int>& numList, int left, int right);
void  insertion_sort(vector<int>& listOfNum,int left,int right);
 bool smallerThan(string first, string second);
 int medianofThree(vector<int>& numList, int left, int right);
 string medianof3(vector<string>&stringFile,int left,int right);

int main(){
    int amountofArrays=1000,arraySize=100,arraySize2=1000,userInput;
    srand(unsigned(time(0))); // used to random initialize numbers
    string gettext; // to retrieve text from the romeo and juliet file and then pushed onto the vector textfile
    vector<string>  textFile;




    cout<<"Please enter the number that corresponds to find what you are looking for:"<<endl;
    cout<<"1.Pick a sorting method to sort 1000 arrays of size 100"<<endl;
    cout<<"2.Pick a sorting method to sort 1000 arrays of size 1000"<<endl;
    cout<<"3.Output a file with Romeo and Juliet alphabetized"<<endl;
    cout<<"4.Test if a string is smaller than another string"<<endl;
    cout<<"5.End Program"<<endl;
     cin>>userInput;
      if(userInput==1){
//takes 0m0.030s for using first element as pivot , takes 0m0.015s for using random pivot,takes 0m0.047s for traditional, took almost 0m0.000s for median of three   //sys time
           for(int i=0;i<amountofArrays;i++){
           int * arrays=new int[100];
           for(int j=0;j<arraySize;j++){
           arrays[j]=(rand()%100)+1;
            }
            vector<int>list(arrays,arrays+100);
            cout<<"Do you want to use first element as pivot method press 1,Random pivot press 2 ,Traditional pivot with selection sort press 3 , Median of 3 pivot press 4"<<endl;
            int userInput2;
            cin>>userInput2;
            if(userInput2==1){
                quick_sortfirstPiv(list,0,100);
            }
             if(userInput2==2){
                quick_sortrandomPiv(list,0,100);

            }
            if(userInput2==3){
              quick_sort(list,0,100);
            }

            if(userInput2==4){
                quick_sort2(list,0,100);
            }
            cout<<"After Quick Sorted:";
            for(int i=0;i<100;i++){
            cout<<list.at(i)<<" ";

             }
           cout<<endl;
           exit(1);

      }
       }


   if(userInput==2){
  //takes 0m0.015s for using first element as pivot , takes 0m0.015s for using random pivot,takes 0m0.015s for traditional, took almost 0m0.000s for median of three //SYS time
           for(int i=0;i<amountofArrays;i++){
            int * arrays=new int[1000];
            for(int j=0;j<arraySize2;j++){
            arrays[j]=(rand()%100)+1;
            }
            vector<int>list(arrays,arrays+1000);
             cout<<"Do you want to use first element as pivot method press 1,Random pivot press 2 ,Traditional pivot with selection sort press 3 , Median of 3 pivot press 4"<<endl;
            int userInput2;
            cin>>userInput2;
            if(userInput2==1){
                quick_sortfirstPiv(list,0,1000);
            }
             if(userInput2==2){
                quick_sortrandomPiv(list,0,1000);

            }
            if(userInput2==3){
              quick_sort(list,0,1000);
            }

            if(userInput2==4){
                quick_sort2(list,0,1000);
            }


            cout<<"After Quick Sorted:";
             for(int i=0;i<1000;i++){
                 cout<<list.at(i)<<" ";

      }
      cout<<endl;

           exit(1);
      }
   }




      if(userInput==3){
                //opens the romeo and juliet file ,sorts it, then outputs into another text file with it alphabetically sorted
      ifstream inFile; //takes 0.031s for first  pivot, takes 0.046 for random pivot,  takes 0.093 seconds to execute traditionally, takes 0.030 seconds for median of three //sys time
      inFile.open("RomeoandJuliet.txt");
      if(inFile.fail()){
          cerr<<"Error can't open file" <<endl;
          exit(1);
      }
      while(!inFile.eof()){
          inFile>>gettext;
          textFile.push_back(gettext);
      }
       inFile.close();
       int maxSize=textFile.size();
       cout<<"Please choose firstpiv type in 1, random piv type in 2, traditional piv type in 3, medianofThree type in 4"<<endl;
       int userinput3;
       cin>>userinput3;
       if(userinput3==1){
           textquick_firstPiv(textFile,0,maxSize-1);
        }
       if(userinput3==2){
           textquick_randomPiv(textFile,0,maxSize-1);
             }
       if(userinput3==3){
       textquick_sort(textFile,0,maxSize-1);
       }
       if(userinput3==4){
        textquick_sortmedianof3(textFile,0,maxSize-1);
                }
       ofstream myfile;
       myfile.open("RomeoandJuliet.output.txt");
        for(int i=0;i<maxSize;i++){
            myfile<<" "<<textFile[i];
        }
        myfile.close();


        exit(1);
      }
      if(userInput==4){
          string firstinput;
          string secondinput;
          cout<<"enter first output , then second output"<<endl;
          cin>>firstinput;
          cin>>secondinput;
           if(smallerThan(firstinput,secondinput)==true){
               cout << "true" << endl;

           }
            else{
               cout << "false" << endl;
            }
            exit(1);

      }

      if(userInput==5){
         exit(1);

      }

     }






    void insertionSort(vector<int>&numbers,int left, int right){     //insertion sort if less than 10 numbers
          for (int i = left+1; i <right; i++) {
           int mainNum= numbers[i];
                      int j;
          for (j = i - 1; j >= 0 && numbers[j] >mainNum; j--) {
           numbers[j + 1] = numbers[j];
       }
   numbers[j+1]=mainNum;

          }
           }
   void quick_sort(vector<int>&numList,int left,int right)
   {
          int i=left,j=right;// the left side of the pivot// the right side of the pivot//for swapping
          int pivot=numList[(left+right)/2];// the pivot for the quick sort
          if (left+right<10){ // if the amount of elements are less than 10 insertion sort is applied
                insertionSort(numList,left,right);
          }
           else{
              while(i<=j)
                    {     // it loops through the whole array
                  while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                  i++;
                  }
                  while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                  j--;
                  }
                  if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped
                     int temp=numList[i];
                     numList[i]=numList[j];
                     numList[j]=temp;
                     i++;
                     j--;
                  }
              }
              if (left<j) //base case using selection sort // sort the left side
               {
                quick_sort(numList,left,j);
               }
                if (i<right)   //sort the right side;
               {
               quick_sort(numList,i,right);
                }
   }
   }


      int medianofThree(vector<int>&numList,int left,int right){ // puts the three number in order then takes one before the last number (n-1*) and returns as pivot
           int middle=(left+right)/2;
            if (numList[middle]<numList[left]){
                   swap(numList[left],numList[middle]);
            }
           else if(numList[right]<numList[left]){
               swap(numList[right],numList[left]);
           }
           else if(numList[right]<numList[middle]){
               swap(numList[right],numList[middle]);
           }
         return numList[right-1];      //after the three numbers are sorted , it takes the element before last one to swap with pivot
      }



      void quick_sort2(vector<int>&numList,int left, int right){
           int i=left,j=right;
           int pivot= medianofThree(numList,left,right);

           while(i<=j)
                    {     // it loops through the whole array
                  while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                  i++;
                  }
                  while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                  j--;
                  }
                  if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped
                     int temp=numList[i];
                     numList[i]=numList[j];
                     numList[j]=temp;
                     i++;
                     j--;
                  }
              }
                       swap(numList[i],numList[right-1]);
              if (left<j) /// sort the left side
               {
                quick_sort(numList,left,j);
               }
                if (i<right)   //sort the right side;
               {
               quick_sort(numList,i,right);
                }



   }

      bool smallerThan(string first, string second){
           if (first.compare(second)<0){
               return true;
           }
           else{
               return false;
           }
      }


    void quick_sortfirstPiv(vector<int>& numList,int left,int right){
          int i=left,j=right;// the left side of the pivot// the right side of the pivot//for swapping
          int pivot=numList[left];// pivot is first element now
          if (left+right<10){ // if the amount of elements are less than 10 insertion sort is applied
                insertionSort(numList,left,right);
          }
           else{
              while(i<=j)
                    {     // it loops through the whole array
                  while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                  i++;
                  }
                  while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                  j--;
                  }
                  if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped
                     int temp=numList[i];
                     numList[i]=numList[j];
                     numList[j]=temp;
                     i++;
                     j--;
                  }
              }
              if (left<j) // sort the left side
               {
                quick_sortfirstPiv(numList,left,j);
               }
                if (i<right)   //sort the right side;
               {
               quick_sortfirstPiv(numList,i,right);
                }
   }
   }
   void quick_sortrandomPiv(vector<int>& numList,int left,int right){
       srand(time(NULL));
       int i=left,j=right;// the left side of the pivot// the right side of the pivot//for swapping
       int size=left+rand()%(right-left+1); // since there is a different left and right every recursive call we have to change it accordingly to the function
          int pivot=numList[size];// pivot is random element now

              while(i<=j)
                    {     // it loops through the whole array
              while (numList[i]<pivot) {  // if the element is less than pivot on the left keep incrementing
                  i++;
                  }
              while(numList[j]>pivot){ // if the element is more than pivot on the right keep decrementing
                  j--;
                  }
              if(i<=j){         //if it did not meet the above conditional loops it means that the elements are not in its place and should be swapped
                     int temp=numList[i];
                     numList[i]=numList[j];
                     numList[j]=temp;
                     i++;
                     j--;
                  }
              }
             if (left<j) //sort left side
               {
                quick_sortrandomPiv(numList,left,j);
               }
              if (i<right)   //sort the right side;
               {
               quick_sortrandomPiv(numList,i,right);
                }
   }
     void textquick_sort(vector<string>& stringFile,int left, int right){ // takes the same implentation as the quicksort and compares the string to the pivot, if it is in the right place it will continue
           // it iterates until it needs to be swapped then when it reaches pivot it recursively sorts the two sides

             int i=left,j=right;
             string temp;

             string pivot=stringFile[(left+right)/2];

                while(i<=j)
                        {
                   while(stringFile[i]<pivot)
                    {
                             i++;
                    }
                    while(stringFile[j]>pivot)
                    {
                        j--;
                    }
                    if(i<=j){
                        temp=stringFile[i];
                        stringFile[i]=stringFile[j];
                        stringFile[j]=temp;
                        i++;
                        j--;
                    }
                }
             if (left<j){
                textquick_sort(stringFile,left,j-1);
             }
            if (right>i){
                textquick_sort(stringFile,i+1,right);
            }
      }

        void textquick_sortmedianof3(vector<string>& stringFile,int left, int right){ // takes the same implentation as the quicksort and compares the string to the pivot, if it is in the right place it will continue
           // it iterates until it needs to be swapped then when it reaches pivot it recursively sorts the two sides

             int i=left,j=right;
             string temp;

             string pivot=medianof3(stringFile,left,right);

                while(i<=j)
                        {
                   while(stringFile[i]<pivot)
                    {
                             i++;
                    }
                    while(stringFile[j]>pivot)
                    {
                        j--;
                    }
                    if(i<=j){
                        temp=stringFile[i];
                        stringFile[i]=stringFile[j];
                        stringFile[j]=temp;
                        i++;
                        j--;
                    }
                }
             if (left<j){
                textquick_sortmedianof3(stringFile,left,j-1);
             }
            if (right>i){
                textquick_sortmedianof3(stringFile,i+1,right);
            }
      }


         string medianof3(vector<string>&stringFile,int left,int right){ //string version of median of three
            int middle=(left+right)/2;
            if (stringFile[middle]<stringFile[left]){
                   swap(stringFile[left],stringFile[middle]);
            }
           else if(stringFile[right]<stringFile[left]){
               swap(stringFile[right],stringFile[left]);
           }
           else if(stringFile[right]<stringFile[middle]){
               swap(stringFile[right],stringFile[middle]);
           }
         return stringFile[right-1];  //string version of median of three
      }

     void textquick_firstPiv(vector<string>& stringFile,int left, int right){ // takes the same implentation as the quicksort and compares the string to the pivot, if it is in the right place it will continue
           // it iterates until it needs to be swapped then when it reaches pivot it recursively sorts the two sides

             int i=left,j=right;
             string temp;
             string pivot=stringFile[left];

                while(i<=j)
                        {
                   while(stringFile[i]<pivot)
                    {
                             i++;
                    }
                    while(stringFile[j]>pivot)
                    {
                        j--;
                    }
                    if(i<=j){
                        temp=stringFile[i];
                        stringFile[i]=stringFile[j];
                        stringFile[j]=temp;
                        i++;
                        j--;
                    }
                }
             if (left<j){
                textquick_sort(stringFile,left,j-1);
             }
            if (right>i){
                textquick_sort(stringFile,i+1,right);
            }
      }


      void textquick_randomPiv(vector<string>& stringFile,int left, int right){
            int i=left,j=right;
            int size=left+rand()%(right-left+1); // since left and right are different every recursive call we have to make sure it adjusts accordingly
             string temp;
             string pivot=stringFile[size];

                while(i<=j)
                        {
                   while(stringFile[i]<pivot)
                    {
                             i++;
                    }
                    while(stringFile[j]>pivot)
                    {
                        j--;
                    }
                    if(i<=j){
                        temp=stringFile[i];
                        stringFile[i]=stringFile[j];
                        stringFile[j]=temp;
                        i++;
                        j--;
                    }
                }
             if (left<j){
                textquick_randomPiv(stringFile,left,j-1);
             }
            if (right>i){
                textquick_randomPiv(stringFile,i+1,right);
            }
      }

