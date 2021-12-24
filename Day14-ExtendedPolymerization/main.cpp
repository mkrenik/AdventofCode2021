#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <sstream> 
#include <climits>

#define GEN 40
 
int main(int argc, char *argv[]) {

  std::string polyTemplate;
  std::map<std::string, std::string> pairRules; 

  // Read input file 
  if (argc == 2) {
    std::fstream f(argv[1], std::ios_base::in); 
    if (f) {
      std::string temp, key, value; 
      int pos; 
      getline(f, polyTemplate); 
      while(getline(f, temp)) {
        if (temp.empty()) {
        } else {
          pos = temp.find('-');
          key = temp.substr(0,pos-1); 
          value = temp.substr(pos+3, temp.length()); 
          pairRules.insert(std::pair<std::string, std::string>(key, value)); 
        }
      }
    } else {
      std::cout << "Unable to open file." << std::endl;
      return -1; 
    }
  } else {
    std::cout << "Wrong program inputs." << std::endl; 
    return -1; 
  }

  // print input
  // std::cout << "Polymer Template: " << polyTemplate << std::endl; 

  // std::map<std::string, std::string>::iterator it = pairRules.begin();

  // // Iterate over the map using Iterator till end.
  // while (it != pairRules.end()) {
  //   std::cout << it->first << " -> " << it->second << std::endl; 
  //   it++;
  // }


  // Put initial values into data structure 
  std::string twoElementIn; 
  std::map<std::string, long int> duplexCount; 

  std::map<std::string, std::string>::iterator init_it = pairRules.begin();
  while (init_it != pairRules.end()) {
    duplexCount.insert(std::pair<std::string, long int>(init_it->first, 0)); 
    init_it++;
  }

  for(int i=0; i<polyTemplate.length()-1; i++) {
    twoElementIn = polyTemplate.substr(i, 2);
    duplexCount[twoElementIn]++; 
  }

  // Advance the polymer steps 
  for (int i =0; i < GEN; i++) {
    std::cout << "Gen: " << i << std::endl; 

    // State of dictionary
    // std::map<std::string, int>::iterator print_it = duplexCount.begin();
    // while (print_it != duplexCount.end()) {
    //   std::cout << print_it->first << " -> " << print_it->second << std::endl; 
    //   print_it++;
    // }

    // This can be improved-- copying a empty dictionary over to avoid corrupting values mid-step 
    std::map<std::string, long int> emptyDict;
    std::map<std::string, std::string>::iterator init_it = pairRules.begin();
    while (init_it != pairRules.end()) {
      emptyDict.insert(std::pair<std::string, long int>(init_it->first, 0)); 
      init_it++;
    }

    // Add polymers 
    std::map<std::string, long int>::iterator duplexCount_it = duplexCount.begin();
    while (duplexCount_it != duplexCount.end()) {

      std::string addChar = pairRules[duplexCount_it->first]; 
      // std::cout << "pair(" << duplexCount_it->first << ") count(" << duplexCount_it->second << ") char (" << addChar << ")" << std::endl;

      // two pairs are increased
      emptyDict[duplexCount_it->first[0]+addChar] += duplexCount_it->second; 
      emptyDict[addChar+duplexCount_it->first[1]] += duplexCount_it->second; 

      duplexCount_it++;
    }  

    duplexCount = emptyDict;  // again, probably not the most efficient...  
  } 

  long int countsRight[26] = {}; 
  long int countsLeft[26] = {}; 
  long int counts[26] = {}; 
  long int max = 0, min = LONG_MAX; 
  
  // we don't know which duplex is on the ends of the sequence
  // so we count all of the lefts of the duplex which miscounts by 1 on the right
  // and we count all the of the rights of the duplex which miscounts by 1 on the left 
  // take the max of both of them for both letters, and we have the final answer! 
  std::map<std::string, long int>::iterator letterCount_it = duplexCount.begin();
  while (letterCount_it != duplexCount.end()) {
    countsLeft[letterCount_it->first[0]-'A'] += letterCount_it->second; 
    countsRight[letterCount_it->first[1]-'A'] += letterCount_it->second; 
    letterCount_it++; 
  }

  for(int i =0; i< 26; i++) {
    counts[i] = std::max(countsRight[i], countsLeft[i]);
  }


  for (int i =0; i<26; i++) {
    if(counts[i] > max) {
      max = counts[i]; 
    }
    if(counts[i] < min && counts[i] != 0) {
      min = counts[i]; 
    }
  }

  std::cout << "max(" <<max<<") - min("<<min<<"): " << max-min << std::endl; 

}