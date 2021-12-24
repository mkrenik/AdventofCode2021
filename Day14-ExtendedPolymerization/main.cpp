#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <sstream> 
#include <climits>

#define GEN 40

bool first = true; 

void addPolyAndCount(std::string duplex, std::map<std::string, std::string> &table, std::map<char, int> &count, int generations) {
  if (generations == GEN) {
    // add to count and return 
    if (first) {    // There is a bug here... needs to be reset everytime the initial value slides
      if (count.contains(duplex[0])) {
        count[duplex[0]]++; 
      } else {
        count.insert(std::pair<char, int>(duplex[0], 1)); 
      }
      first = false; 
    }
    if (count.contains(duplex[1])) {
      count[duplex[1]]++; 
    } else {
      count.insert(std::pair<char, int>(duplex[1], 1)); 
    }
    
  } else {
    // recurse
    std::string addChar = table[duplex];
    // std::cout << "duplex: " << duplex << "   addChar: " << addChar << std::endl; 
    addPolyAndCount(duplex[0]+addChar, table, count, generations+1);
    addPolyAndCount(addChar+duplex[1], table, count, generations+1);
  }
}

int main(int argc, char *argv[]) {

  std::string polyTemplate;
  std::map<std::string, std::string> pairRules; 

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

  // // print input
  // std::cout << "Polymer Template: " << polyTemplate << std::endl; 

  // std::map<std::string, std::string>::iterator it = pairRules.begin();

  // // Iterate over the map using Iterator till end.
  // while (it != pairRules.end()) {
  //   std::cout << it->first << " -> " << it->second << std::endl; 
  //   it++;
  // }

  std::string twoElementIn; 
  std::map<char, int> finalCount; 

  for(int i=0; i<polyTemplate.length()-1; i++) {
    std::cout << "Sliding " << i << std::endl; 
    twoElementIn = polyTemplate.substr(i, 2);
    addPolyAndCount(twoElementIn, pairRules, finalCount, 0);   
  }

  int min=INT_MAX, max=0; 
  std::map<char, int>::iterator count_it = finalCount.begin();
  while (count_it != finalCount.end()) {  
    std::cout << "\t" << count_it->first << ": " << count_it->second; 
    if(count_it->second > max) {
      max = count_it->second; 
    }
    if(count_it->second < min) {
      min = count_it->second; 
    }
    count_it++; 
  }
  std::cout << std::endl; 

  std::cout << "max(" <<max<<") - min("<<min<<"): " << max-min << std::endl; 

}