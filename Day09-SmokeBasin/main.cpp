#include <iostream>
#include <fstream>
#include <vector> 

#define FILE_NAME "input" 

int main() {
  std::vector<std::vector<int>> heightMap; 
  std::vector<int> riskOfLowPoints; 
  std::fstream f(FILE_NAME, std::ios_base::in);
  std::string temp; 

  // read in height map 
  while (getline(f, temp)) {
    std::vector<int> emptyVec; 
    heightMap.push_back(emptyVec); 
    for (int i =0; i< temp.length(); i++) {
      heightMap.back().push_back((temp[i]) - '0'); 
    }
  }

  int riskLevelSum = 0; 
  // print out height map 
  for (int i = 0; i < heightMap.size(); i++) {
    for (int j = 0; j < heightMap.at(i).size(); j++) {
      int mapValue = heightMap.at(i).at(j); 

      if (i - 1 >= 0) {
        if(heightMap.at(i-1).at(j) <= mapValue) {
          continue; 
        }
      }

      if (i + 1 < heightMap.size()) {
        if(heightMap.at(i+1).at(j) <= mapValue) {
          continue; 
        }
      }      

      if (j - 1 >= 0) {
        if(heightMap.at(i).at(j-1) <= mapValue) {
          continue; 
        }
      }

      if (j + 1 < heightMap.at(i).size()) {
        if(heightMap.at(i).at(j+1) <= mapValue) {
          continue; 
        }
      }

      riskLevelSum += mapValue + 1; 
    }
  }
  std::cout << "Risk Level Sum: " << riskLevelSum << std::endl; 
}
