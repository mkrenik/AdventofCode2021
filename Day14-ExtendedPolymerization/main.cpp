#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <sstream> 
#include <climits>


struct Result5Gen {
  std::string resultStr;

  std::map<char, int> resultCounts;  
};

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



  // Run the polymerization on each dictionary entry to accelerate 5 steps
  std::map<std::string, std::string>::iterator it = pairRules.begin();

  std::map<std::string, Result5Gen> accelerator; 

  std::string input; 
  while (it != pairRules.end()) {
    input = it->first;
    // std::cout << "after 0 steps, is: " << input << std::endl; 
    for (int step=1; step<=7; step++) {
      std::stringstream afterStep;  
      std::string twoElementIn; 
      std::string toInsert; 
      for(int i=0; i<input.length()-1; i++) {
        twoElementIn = input.substr(i, 2);
        // std::cout << "twoElem: " << twoElementIn << std::endl; 
        toInsert = pairRules[twoElementIn]; 
        // std::cout << "toIns: " << toInsert << std::endl; 

        if (i==0) { // first step, insert the first char
          afterStep << twoElementIn[0]; 
        }
        afterStep << toInsert << twoElementIn[1]; 
      }

      input = afterStep.str(); 
      // std::cout << "after " << step << " steps, is: " << input << std::endl; 
    }

    std::map<char, int> charCount; 
    for (int i =0; i<input.size(); i++) {
      if (charCount.contains(input[i])) {
        charCount[input[i]]++; 
      } else {
        charCount.insert(std::pair<char, int>(input[i], 1)); 
      }
    }

    Result5Gen entry; 
    entry.resultCounts = charCount; 
    entry.resultStr = input; 
    accelerator.insert(std::pair<std::string, Result5Gen>(it->first, entry)); 
    it++;
  } 

  // print results of accelerator 
  std::map<std::string, Result5Gen>::iterator acc_it = accelerator.begin();
  while (acc_it != accelerator.end()) {
    std::cout << acc_it->first << ": " << std::endl; 
    std::cout << "\t" << acc_it->second.resultStr << std::endl; 

    std::map<char, int>::iterator count_it = acc_it->second.resultCounts.begin();
    while (count_it != acc_it->second.resultCounts.end()) {  
      std::cout << "\t" << count_it->first << ": " << count_it->second; 
      count_it++; 
    }
    std::cout << std::endl; 
    acc_it++; 
  } 


  // Use the accelerator  
  // std::map<char, int> finalCount; 

  // for (int step=1; step<=4; step++) {
  //   std::stringstream afterStep;  
  //   std::string twoElementIn; 
  //   std::string toReplace; 
  //   for(int i=0; i<polyTemplate.length()-1; i++) {
  //     twoElementIn = polyTemplate.substr(i, 2);
  //     // std::cout << "twoElem: " << twoElementIn << std::endl; 
  //     toReplace = accelerator[twoElementIn].resultStr; 
  //     // std::cout << "toIns: " << toInsert << std::endl; 

  //     if (i==0) { // first step, insert the first char
  //       afterStep << twoElementIn[0]; 
  //     }
  //     afterStep << toReplace; 
  //   }

  //   polyTemplate = afterStep.str(); 
  //   std::cout << "after " << step << " steps, is: " << polyTemplate.length() << std::endl; 
  // }  

  // Count the characters in the final result 


  // // Find the min and the max 
  // int minCount = INT_MAX;
  // int maxCount = 0; 

  // std::map<char, int>::iterator it = charCount.begin();

  // while (it != charCount.end()) {
  //   if (it->second > maxCount) {
  //     maxCount = it->second;
  //   }
  //   if (it->second < minCount) {
  //     minCount = it->second; 
  //   }
  //   it++;
  // } 

  // std::cout << "Max - min: " << maxCount - minCount << std::endl; 

}