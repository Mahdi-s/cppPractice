#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <omp.h>
using namespace std;
using std::ifstream;
#define NUM_THREADS 2


typedef struct thread_arguments {
  string * word_array;
  string word_to_search;
  int count;
} thargs_t;



void  *getWordCount(void *thrgs)
  //string * word_array, string word_to_search, int count
{
  int word_count = 0;
  string * word_array = ((thargs_t*)thrgs)->word_array;
  string word_to_search = ((thargs_t*)thrgs)->word_to_search;
  int count  = ((thargs_t*)thrgs)->count;

  for (int n=0; n< count; n++){
    if (word_array[n] == word_to_search)
      word_count  = word_count + 1;
  }

  cout << "The number of occurances of" <<
    word_to_search << " is " << word_count << endl;


}

int main()
{

  string wget = "wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt -q";
  const char *command = wget.c_str();
  cout << "extracting html file..." << endl;
  system(command);
  ifstream indata;
  string projName;
  indata.open("hw3-data.txt");

  if(!indata) { // file couldn't be opened
   cerr << "Error: file could not be opened" << endl;
   exit(1);
  }

  int counter = 0;
  indata >> projName;

  while (!indata.eof())
  {
    counter = counter + 1;
    //cout << projName << endl;
    indata >> projName; // sets EOF flag if no value found
  }

  cout << "Word count from downloaded page: "<< counter << endl;

  indata.close();

  string * word_array;
  word_array = new (nothrow) string [counter];
  if (word_array == nullptr) {
    cout << "Error assigning memory for the array..." << endl;
  }

  ifstream indata2;
  string projName2;

  indata2.open("hw3-data.txt");
  if(!indata2) { // file couldn't be opened
   cerr << "Error: file could not be opened" << endl;
   exit(1);
  }

  indata2 >> projName2;
  int i = 0;

  while (!indata2.eof())
  {
    word_array[i] = projName2;
    i =  i + 1;
    //cout << projName << endl;
    indata2 >> projName2; // sets EOF flag if no value found
  }

  for (int n=0; n< counter; n++){
    cerr << word_array[n] << endl;
  }

  indata2.close();

  pthread_t threads[NUM_THREADS];
  int rc;




  thargs_t args[2];

 for(int t=0;t<NUM_THREADS;t++) {
   if (t == 1){
     args-> word_array = word_array;
     args-> word_to_search = "easy";
     args-> word_to_search = counter;
   }
   if (t == 2){
     args-> word_array = word_array;
     args-> word_to_search = "polar";
     args-> word_to_search = counter;
   }

    rc = pthread_create(&threads[t], NULL, getWordCount, &args[t]);
    //easy
    //polar
    if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
  }
  pthread_exit(NULL);












  cout << "End-of-file reached.." << endl;
  unlink("hw3-data.txt");
  return 0;


}
