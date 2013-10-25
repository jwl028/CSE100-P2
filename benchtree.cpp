#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string.h>
#include <ios>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
  string dataStruc;
  string order;
  int maxSize;
  int numRuns;
  int maxN;
  int N;
  if (argc == 5) {
    //std::istream num1(argv[3]);
    //std::istream num2(argv[4]);
    //Selected data structure
    if(strcmp(argv[1],"bst")==0 || strcmp(argv[1],"rst")==0 || strcmp(argv[1],"set")==0) {
      dataStruc = argv[1];
    }
    else {
      cout << "Please enter either 'bst', 'rst', or 'set' for the first argument" << endl;
      return (0);
    } 
    //Sorted or shuffled 
    if(strcmp(argv[2],"sorted")==0 || strcmp(argv[2],"shuffled")==0 ) {
      order = argv[2];
    }    
    else {
      cout << "Please enter either 'sorted' or 'shuffled' for the second argument" << endl;
      return (0);
    } 
    //Maximum tree size 
    maxSize = atoi(argv[3]);
    maxN = log(maxSize + 1) / log(2);
    //# times calculations are run 
    for(unsigned int a = 0; a < strlen(argv[4]); a++) {
      if(isdigit(argv[4][a]) == 0) {
        cout << "Please enter an integer from 1 to infinite for the fourth argument" << endl;
        return(0);
      }
    }
    numRuns = atoi(argv[4]);
    if (numRuns == 0) {
      cout << "Please enter an integer greater than or equal to 1 for the fourth argument" << endl;
      return(0);
    }
  }
  else {
    cout << "Please enter 4 arguments" << endl;
    return(0);
  }

  //Description of benchmark
  cout << "# Benchmarking average number of comparisons for successful find" << endl;
  cout << "# Data structure: " << dataStruc << endl;
  cout << "# Data: " << order << endl;
  cout << "# N is powers of 2, minus 1, from 1 to " << maxSize << endl;
  cout << "# Averaging over " << numRuns << "for each N" << endl;
  cout << "#" << endl;
  cout << "# N\tavgcomps\tstdev" << endl;

  //N in 2^n + 1 steps
  for (int i=0; i<maxN; i++) {
    //Calculate N
    N = pow(2,(i+1))-1;
    //Reset values for each N
    double avgcomps = 0.0;
    double sumsqcomp = 0.0;
    double stdev = 0.0;
    
    //Insert and find on RST data structure.
    //Originally implemented one loop and if/else statements for each data structure declaration.
    //However, tree.insert() and tree.find() would not compile because of scope.  Therefore, multiple
    //loops were created for each if statement. 
    if(dataStruc.compare("rst")==0) {
      for (int j=0; j<numRuns; j++) {
        RST<countint> tree = RST<countint>();
        vector<countint> v;
        countint::clearcount();
        v.clear();
        for(int k=0; k<N; ++k) {
          v.push_back(k);
        }
        if(order == "shuffled") {
          random_shuffle(v.begin(),v.end());
        }  
        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.insert(*vit);
        }
        countint::clearcount();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.find(*vit);
        }
        avgcomps += countint::getcount()/(double)N;
        sumsqcomp += pow((countint::getcount()/(double)N),2.0);   
      }
      avgcomps = avgcomps/(double)numRuns;
      sumsqcomp = sumsqcomp/(double)numRuns;   
      stdev = sqrt(abs(pow(avgcomps,2.0)-sumsqcomp));
      cout << N << "\t" << avgcomps << "\t" << stdev << endl;
    }

    //Insert and find on BST data structure.
    else if(dataStruc.compare("bst")==0) {
      for (int j=0; j<numRuns; j++) {
        BST<countint> tree = BST<countint>();
        vector<countint> v;
        countint::clearcount();
        v.clear();
        for(int k=0; k<N; ++k) {
          v.push_back(k);
        }
        if(order == "shuffled") {
          random_shuffle(v.begin(),v.end());
        }  
        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.insert(*vit);
        }
        countint::clearcount();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.find(*vit);
        }  
        avgcomps += countint::getcount()/(double)N;
        sumsqcomp += pow((countint::getcount()/(double)N),2.0);   

      }
      avgcomps = avgcomps/(double)numRuns;
      sumsqcomp = sumsqcomp/(double)numRuns;   
      stdev = sqrt(abs(pow(avgcomps,2.0)-sumsqcomp));
      cout << N << "\t" << avgcomps << "\t" << stdev << endl;
    }
  
    //Insert and find on set data structure.
    else if(dataStruc.compare("set")==0) {
      for (int j=0; j<numRuns; j++) {
        set<countint> tree;
        vector<countint> v;
        countint::clearcount();
        v.clear();
        for(int k=0; k<N; ++k) {
          v.push_back(k);
        }
        if(order == "shuffled") {
          random_shuffle(v.begin(),v.end());
        }  
        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.insert(*vit);
        }
        countint::clearcount();
        for(vit = v.begin(); vit != ven; ++vit) {
          tree.find(*vit);
        }  
        avgcomps += countint::getcount()/(double)N;
        sumsqcomp += pow((countint::getcount()/(double)N),2.0);   
      }
      avgcomps = avgcomps/(double)numRuns;
      sumsqcomp = sumsqcomp/(double)numRuns;   
      stdev = sqrt(abs(pow(avgcomps,2.0)-sumsqcomp));
      cout << N << "\t" << avgcomps << "\t" << stdev << endl;
    }
  } 
}
