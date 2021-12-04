#include "bingo.hpp"

BingoCard::BingoCard(std::array<std::array<int, GRID_SIZE>, GRID_SIZE> input) : grid{input} 
{
  // initialize marked grid to be all 0s
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      marked_grid[i][j] = 0; 
    }
  }
}

void BingoCard::markNumber(int number) {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] == number) {
        marked_grid[i][j] = 1; 
        lastMarked = number; 
      }
    }
  }
}

bool BingoCard::checkForWin() {

  // check for horizontal victories
  for (int i = 0; i < GRID_SIZE; i++) {
    int rowSum = 0; 
    for (int j = 0; j < GRID_SIZE; j++) {
      rowSum += marked_grid[i][j]; 
    }
    if (rowSum == GRID_SIZE) {
      std::cout << "horizontal victory!" << std::endl; 
      return true; 
    }
  }

  // check for vertical victories 
  for (int j = 0; j < GRID_SIZE; j++) {
    int colSum = 0; 
    for (int i =0; i < GRID_SIZE; i++) {
      colSum += marked_grid[i][j]; 
    }
    if (colSum == GRID_SIZE) {
      std::cout << "vertical victory!" << std::endl; 
      return true; 
    }
  } 

  return false; 
}


int BingoCard::calculateScore() {
  // find sum of unmarked numbers
  int unmarkedSum = 0; 
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (marked_grid[i][j] == 0) {
        unmarkedSum += grid[i][j]; 
      }
    }
  }

  return unmarkedSum * lastMarked; 
}


void BingoCard::print() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      std::cout << grid[i][j] << "\t";
    }
    std::cout << std::endl; 
  }
}