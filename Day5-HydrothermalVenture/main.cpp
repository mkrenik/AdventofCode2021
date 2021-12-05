#include <iostream>
#include <vector> 
#include <array> 
#include <sstream>     
#include <fstream>

#define FILE_NAME "input"
#define GRID_SIZE 1000 

struct Line {
  int x1, x2, y1, y2; 

  Line(int x1, int x2, int y1, int y2) 
  : x1{x1}, x2{x2}, y1{y1}, y2{y2}{}; 
};


std::vector<Line> readInput() {

  std::vector<Line> inputs; 
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp;
    int number_lines = 0;  
    while (getline(f, temp)) {

      std::size_t pos = temp.find(" -> "); 
      std::string firstPoint = temp.substr(0, pos); 
      std::string secondPoint = temp.substr(pos+4, std::string::npos); 

      // std::cout << "1st: " << firstPoint << std::endl;
      // std::cout << "2nd: " << secondPoint << std::endl;

      // std::cout << firstPoint.substr(0, firstPoint.find(",")) << "\t"; 
      // std::cout << firstPoint.substr(firstPoint.find(",")+1, std::string::npos) << "\t"; 
      // std::cout << secondPoint.substr(0, secondPoint.find(",")) << "\t"; 
      // std::cout << secondPoint.substr(secondPoint.find(",")+1, std::string::npos) <<std::endl; 

      int x1 = std::stoi( firstPoint.substr(0, firstPoint.find(","))); 
      int y1 = std::stoi( firstPoint.substr(firstPoint.find(",")+1, std::string::npos)); 
      int x2 = std::stoi( secondPoint.substr(0, secondPoint.find(","))); 
      int y2 = std::stoi( secondPoint.substr(secondPoint.find(",")+1, std::string::npos)); 

      // std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;  

      // only allow horizontal / vertical
      if (x1 == x2 || y1 == y2)  {
        if (x2 < x1 || y2 < y1) {
          Line newLine(x2, x1, y2, y1); 
          inputs.push_back(newLine); 
        } else {
          Line newLine(x1, x2, y1, y2); 
          inputs.push_back(newLine); 
        }
      }
      number_lines++; 
    }
    // std::cout << "Valid: " << inputs.size() << ", total: " << number_lines << std::endl; 
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  return inputs; 
}

void plotLines(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid , std::vector<Line> lines) {
  for (auto & elem : lines) {
    // std::cout << "Line: (" << elem.x1 << "," << elem.y1 << ") (" << elem.x2 << "," << elem.y2 << ")" << std::endl; 
    // std::cout << "Points marked: "; 
    for (int i=elem.x1; i<=elem.x2; i++){
      for (int j=elem.y1; j<=elem.y2; j++) {
        grid[i][j]++; 
        // std::cout << "(" << i << "," << j << ") "; 
      }
    }
    // std::cout << std::endl; 
  }
}

int countPoints(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid) {
  int count = 0; 
  for (int i=0; i<GRID_SIZE; i++){
    for (int j=0; j<=GRID_SIZE; j++) {
      if (grid[i][j] >= 2){
        count++; 
      }
    }
  }
  return count; 
}

int main() {
  std::vector<Line> lines = readInput(); 
  std::array<std::array<short int, GRID_SIZE>, GRID_SIZE> grid = {}; 

  plotLines(grid, lines); 

  std::cout << countPoints(grid) << std::endl; 

  return 0; 
}