#include <vector> 
#include <array> 
#include <iostream> 

#define GRID_SIZE 5

class BingoCard {
  public:
  BingoCard(std::array<std::array<int, GRID_SIZE>, GRID_SIZE>);
  void markNumber(int); 
  bool checkForWin(); 
  int calculateScore(); 
  void print(); 

  private:
  std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid; 
  std::array<std::array<int, GRID_SIZE>, GRID_SIZE> marked_grid; 
  int lastMarked; 
};