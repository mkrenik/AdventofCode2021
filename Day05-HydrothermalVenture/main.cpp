#include <iostream>
#include <vector> 
#include <array> 
#include <sstream>     
#include <fstream>
#include <cmath> 

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

      Line newLine(x1, x2, y1, y2); 
      inputs.push_back(newLine); 

      number_lines++; 
    }
    std::cout << "Total Lines: " << number_lines << std::endl; 
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  return inputs; 
}

void plotOrtho(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid, int x1, int y1, int x2, int y2) {
  for (int i=x1; i<=x2; i++){
    for (int j=y1; j<=y2; j++) {
      grid[i][j]++; 
    }
  }
}

void plotLines(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid , std::vector<Line> lines) {
  int num_ortho_lines = 0;
  for (auto & elem : lines) {
    // only allow horizontal / vertical
    if (elem.x1 == elem.x2 || elem.y1 == elem.y2)  {
      if (elem.x2 < elem.x1 || elem.y2 < elem.y1) {
        plotOrtho(grid, elem.x2, elem.y2, elem.x1, elem.y1); // reverse the points 
      } else {
        plotOrtho(grid, elem.x1, elem.y1, elem.x2, elem.y2);  
      }
      num_ortho_lines++; 
    } 
  }

  std::cout << "Ortho Lines: " << num_ortho_lines << std::endl; 
}

struct Direction {
  int x, y; 

  Direction(int xdir, int ydir) {
    if (xdir > 0) x = 1;
    else x = -1; 
    if (ydir > 0) y = 1;
    else y = -1; 
  }; 
}; 

void plotDiag(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid, int x1, int y1, int x2, int y2) {

  Direction dir(x2-x1, y2-y1); 

  std::cout << "Line: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ") Dir: " << dir.x << " " <<dir.y << std::endl; 
  std::cout << "Points marked: "; 
  // z is a step counter
  for (int i=x1, j=y1, z=0; z<=std::abs(x2-x1); i+=dir.x, j+=dir.y, z++){
    grid[i][j]++; 
    std::cout << "(" << i << "," << j << ") "; 
  }
  std::cout << std::endl; 
}

void plotLinesDiag(std::array<std::array<short int, GRID_SIZE>, GRID_SIZE>& grid , std::vector<Line> lines) {
  int num_diag_lines = 0;
  for (auto & elem : lines) {
    // only allow horizontal / vertical
    if (elem.x1 != elem.x2 && elem.y1 != elem.y2)  {
      plotDiag(grid, elem.x1, elem.y1, elem.x2, elem.y2); 
      num_diag_lines++; 
    } 
  }
  std::cout << "Diag Lines: " << num_diag_lines << std::endl; 

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
  std::cout << "Part 1: " << countPoints(grid) << std::endl; 

  plotLinesDiag(grid, lines); 
  std::cout << "Part 2: " << countPoints(grid) << std::endl; 

  return 0; 
}