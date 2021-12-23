#include <iostream>
#include <fstream> 

#define FILE_NAME "input"

struct Octopus {
  int value;
  bool hasFlashed; 

  Octopus() { 
    value = 0; 
    hasFlashed = false; 
  }
  Octopus(int x) {
    value = x; 
    hasFlashed = false; 
  }
};

int totalFlashes = 0; 
Octopus grid[10][10]; 

void checkForFlash(int x, int y); // prototype

void flash(int x, int y) {
  grid[x][y].hasFlashed = true; 

  if (x>0) {
    grid[x-1][y].value++;
    checkForFlash(x-1, y); 
  }
  if (x>0 && y>0) {
    grid[x-1][y-1].value++; 
    checkForFlash(x-1, y-1); 
  }
  if (x>0 && y<9) {
    grid[x-1][y+1].value++; 
    checkForFlash(x-1, y+1); 
  }
  if (x<9) {
    grid[x+1][y].value++;
    checkForFlash(x+1, y); 
  }
  if (x<9 && y>0) {
    grid[x+1][y-1].value++; 
    checkForFlash(x+1, y-1); 
  }
  if (x<9 && y<9) {
    grid[x+1][y+1].value++; 
    checkForFlash(x+1, y+1); 
  }  
  if (y<9) {
    grid[x][y+1].value++; 
    checkForFlash(x, y+1);     
  }
  if (y>0) {
    grid[x][y-1].value++; 
    checkForFlash(x, y-1);     
  }
}

void checkForFlash(int x, int y) {
  if (grid[x][y].value > 9 && grid[x][y].hasFlashed == false) {
    flash(x,y); 
  }
}

int main() {
  std::fstream f(FILE_NAME, std::ios_base::in);
  std::string temp; 
  int lineCount = 0; 
  if (f) {
    while(getline(f, temp)) {
      for (int i =0; i<temp.length(); i++) {
        grid[lineCount][i] = Octopus(temp[i] - '0'); 
      }
      lineCount++; 
    }

  } else {
    std::cout << "unable to open file." << std::endl; 
    return -1; 
  }

  // print octopus grid 
  std::cout << "Initial:" << std::endl; 
  for (int i =0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      std::cout << grid[i][j].value; 
    }
    std::cout << std::endl; 
  }

  int lastTotalFlashes; 
  for (int steps=1; steps <=1000; steps++) {
    lastTotalFlashes = totalFlashes; 
    std::cout << "Step " << steps << std::endl; 
    // Add 1 energy to all octopus values 
    for (int i =0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        grid[i][j].value += 1; 
      }
    }    

    // resolve all flashes 
    for (int i =0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        checkForFlash(i, j); 
      }
    }

    // count flashes and reset values
    for (int i =0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (grid[i][j].hasFlashed == true) {
          grid[i][j].hasFlashed = false;
          grid[i][j].value = 0;
          totalFlashes++;
        } 
      }
    }
    if (totalFlashes-lastTotalFlashes == 100) {
      std::cout << "all flashes in step: " << steps << std::endl; 
      break; 
    }

    // print result after step 
    // for (int i =0; i < 10; i++) {
    //   for (int j = 0; j < 10; j++) {
    //     std::cout << grid[i][j].value; 
    //   }
    //   std::cout << std::endl; 
    // }    
  }

  std::cout << "number of flashes: " << totalFlashes << std::endl;
}