#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <sstream> 
#include <climits>

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

  // Run the polymerization 
  for (int step=1; step<=10; step++) {
    std::stringstream afterStep;  
    std::string twoElementIn; 
    std::string toInsert; 
    for(int i=0; i<polyTemplate.length()-1; i++) {
      twoElementIn = polyTemplate.substr(i, 2);
      toInsert = pairRules[twoElementIn]; 

      if (i==0) { // first step, insert the first char
        afterStep << twoElementIn[0]; 
      }
      afterStep << toInsert << twoElementIn[1]; 
    }

    polyTemplate = afterStep.str(); 
    // std::cout << polyTemplate << std::endl;
  }

  // Count the characters in the final result 
  std::map<char, int> charCount; 
  for (int i =0; i<polyTemplate.size(); i++) {
    if (charCount.contains(polyTemplate[i])) {
      charCount[polyTemplate[i]]++; 
    } else {
      charCount.insert(std::pair<char, int>(polyTemplate[i], 1)); 
    }
  }

  // Find the min and the max 
  int minCount = INT_MAX;
  int maxCount = 0; 

  std::map<char, int>::iterator it = charCount.begin();

  while (it != charCount.end()) {
    if (it->second > maxCount) {
      maxCount = it->second;
    }
    if (it->second < minCount) {
      minCount = it->second; 
    }
    it++;
  } 

  std::cout << "Max - min: " << maxCount - minCount << std::endl; 

}