#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <cmath>
#include <algorithm> 

// bool isDuplicate(std::pair<int,int>, std::pair<int,int) {

// }

void printCoordinates(std::vector<std::pair<int, int>> coordinates) {

  std::cout << "# coords: " << coordinates.size() << std::endl; 

  for (auto &point : coordinates) {
    std::cout << point.first << "," << point.second << "\t"; 
  }
  std::cout << std::endl;

  char printArray[100][100]; 
  int maxX =0, maxY=0; 

  for (auto &coord: coordinates) {
    if (coord.first > maxX) {
      maxX = coord.first; 
    }
    if (coord.second > maxY) {
      maxY = coord.second;
    }
  }

  std::cout << "maxX: " << maxX << "   maxY: " << maxY << std::endl; 

  for (int j = 0; j <= maxY; j++) {
    for (int i = 0; i <= maxX; i++) {
      printArray[i][j] = '.'; 
    }
  }

  for (int j = 0; j <= maxY; j++) {
    for (int i = 0; i <= maxX; i++) {
      for(auto& point : coordinates) {
        if (point.first == i && point.second == j) {
          printArray[i][j] = 'X'; 
        }
      }
    }
  }

  for (int j = 0; j <= maxY; j++) {
    for (int i = 0; i <= maxX; i++) {
      std::cout << printArray[i][j]; 
    }
    std::cout << std::endl; 
  }
}

int main (int argc, char* argv[]) {
  std::string temp;
  std::vector<std::pair<int, int>> coordinates; 
  std::vector<std::pair<char, int>> folds; 

  if (argc ==2) {
    std::fstream f(argv[1], std::ios_base::in);
    if (f) {
      while(getline(f, temp)) {

        int pos = temp.find(',');
        if (pos != std::string::npos) {  
          int first = std::stoi(temp.substr(0,pos)); 
          int second = std::stoi(temp.substr(pos+1,temp.length())); 
          coordinates.push_back(std::make_pair(first, second)); 
        } else if (temp.empty()) {
          continue; 
        } else {
          int eqPos = temp.find('=');
          char foldDir = temp.at(eqPos-1); 
          int foldAt = std::stoi(temp.substr(eqPos+1, temp.length())); 
          folds.push_back(std::make_pair(foldDir, foldAt)); 
        }

      }
    } else {
      std::cout << "Error opening file" << std::endl; 
      return -1; 
    }

  } else {
    std::cout << "Error with program arguments." << std::endl; 
    return -1; 
  }

  // printCoordinates(coordinates); 

  for (auto &fold : folds) {

    for (auto &point : coordinates) {
      int foldPos = fold.second; 
      if (fold.first == 'x') {
        if (point.first < foldPos) {
        } else {
          point.first = foldPos - (point.first - foldPos); 
        }
      } else { // fold == 'y' 
        if (point.second < foldPos) {
        } else {
          point.second = foldPos - (point.second - foldPos); 
        }
      }
    }
    // sort and remove duplicates 
    std::sort(coordinates.begin(), coordinates.end());
    auto last = std::unique(coordinates.begin(), coordinates.end()); 
    coordinates.erase(last, coordinates.end()); 
    std::cout << "After fold at: " << fold.first << "=" << fold.second <<
      "   # coordinates: " << coordinates.size() << std::endl;

    // printCoordinates(coordinates); 
  }

  printCoordinates(coordinates);
} 