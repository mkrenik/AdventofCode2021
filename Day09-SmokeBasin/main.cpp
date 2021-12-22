#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm> 

#define FILE_NAME "input" 
#define ROWS 100
#define COLUMNS 100

struct Basin {
  int lowPointX;
  int lowPointY; 
  std::vector<std::pair<int, int>> points; 

  Basin(int x, int y) {
    lowPointX = x; 
    lowPointY = y;
  }

  void addPoints(int x, int y, const std::vector<std::vector<int>> &map) {
    if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS && map.at(x).at(y) != 9) {
      // check for duplicates
      for (auto& point : points) {
        if (point.first == x && point.second == y) {
          return; 
        }
      }
      points.push_back(std::make_pair(x,y)); 
      addPoints(x+1, y, map); 
      addPoints(x-1, y, map); 
      addPoints(x, y+1, map); 
      addPoints(x, y-1, map); 
    }
  }
};

bool sortByPointsSize(Basin &A, Basin &B) {
    return (A.points.size() > B.points.size());
}

int main() {
  std::vector<Basin> basins; 
  std::vector<std::vector<int>> heightMap; 
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
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      int mapValue = heightMap.at(i).at(j); 

      // check up, if within map bounds
      if (i - 1 >= 0) {
        if(heightMap.at(i-1).at(j) <= mapValue) {
          continue; 
        }
      }

      // check down, if within map bounds
      if (i + 1 < ROWS) {
        if(heightMap.at(i+1).at(j) <= mapValue) {
          continue; 
        }
      }      

      // check left, if within map bounds
      if (j - 1 >= 0) {
        if(heightMap.at(i).at(j-1) <= mapValue) {
          continue; 
        }
      }

      // check right, if within map bounds
      if (j + 1 < COLUMNS) {
        if(heightMap.at(i).at(j+1) <= mapValue) {
          continue; 
        }
      }

      basins.push_back(Basin(i, j));
      basins.back().addPoints(i, j, heightMap);  
      riskLevelSum += mapValue + 1; 
    }
  }

  // Order Basins by size
  std::sort(basins.begin(), basins.end(), sortByPointsSize); 
  for (auto &basin : basins) {
    std::cout << basin.points.size() << std::endl; 
  }
  // Part 1
  std::cout << "Risk Level Sum: " << riskLevelSum << std::endl; 

  // Part 2 
  std::cout << "Product of basin sizes: " << basins.at(0).points.size() * basins.at(1).points.size() * basins.at(2).points.size() << std::endl; 

}
