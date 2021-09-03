/*
Mahdi Saeedi
CSCI 451
HW 1
*/
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <regex>
using namespace std;
using std::ifstream;

int main ()
{
  string wget = "wget http://undcemcs01.und.edu/~ronald.marsh/PROJECTS/PROJECTS.HTML -q";
  const char *command = wget.c_str();
  cout << "extracting html file..." << endl;
  //cout << command;
  system(command);

  ifstream indata;
  string projName;

  //const regex pattern("[^a-zA-Z0-9]+");
  //const regex pattern("[<>=-]+");


  indata.open("PROJECTS.HTML");
  //FILE *file = fopen("PROJECTS.HTML", "r");
  if(!indata) { // file couldn't be opened
   cerr << "Error: file could not be opened" << endl;
   exit(1);
  }

  int counter = 0;
  string project_name = "";

  std::vector<std::string> names {};

  indata >> projName;
   while ( !indata.eof() ) { // keep reading until end-of-file

      //cout << projName << endl;

      // if ((projName.find('<') == std::string::npos) && (projName.find('>') == std::string::npos) && (projName.find('=') == std::string::npos))
      // {
      //   cout << projName << endl;
      // }

      if (counter == 2)
      {
      //  cout << "in counter 2  " << counter << endl;
        counter = counter + 1;
        continue;
      }

      if (std::regex_match (projName, std::regex("(<font)")))
      {
        //cout << "in first loop" << counter << endl;
        counter = counter + 1;
      }

      if (std::regex_match (projName, std::regex("(color=\"#FFCC00\")")))
      {
        //cout << "in second loop" << counter << endl;
        counter = counter + 1;
      }

      // if (std::regex_match (projName, std::regex("(SIZE=+1>)")))
      // {
      //   cout << "in third loop" << counter << endl;
      //   counter = counter + 1;
      //   cout << "in third loop" << counter << endl;
      // }



      if (std::regex_match (projName, std::regex("(</font>)")))
      {
        cout << "pushing item  " << project_name << endl;
      //  cout << "in last loop" << counter << endl;
        counter = 0;
        names.push_back(project_name);
        project_name = "";
      }

      if (counter == 3)
      {
        project_name = project_name + " " + projName;
      }

      //if its <font

      indata >> projName; // sets EOF flag if no value found

   }

   size_t n = sizeof(names)/sizeof(names[0]);
   for (size_t i = 0; i < n; i++) {
       cout << names[i] << ' ';
   }


   indata.close();
   cout << "End-of-file reached.." << endl;
   return 0;

}
