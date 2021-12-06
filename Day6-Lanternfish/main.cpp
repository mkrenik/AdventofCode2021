#include <iostream>
#include <vector> 
#include <sstream>     
#include <fstream>

#define FILE_NAME "input"

struct Fish {
  int days; 
  Fish() : days{8} {}; 
  Fish(int x) : days{x} {};
};


std::vector<Fish> readInput() {

  std::vector<Fish> inputs; 
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp;
    while (getline(f, temp, ',')) {
      inputs.push_back(Fish(stoi(temp)));
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  return inputs; 
}

int main () {
  std::vector<Fish> school; 
  school = readInput(); 

  for (int i =1 ; i<=80; i++) {
    std::vector<Fish> newFish; 
    for (auto &fish : school) {
      fish.days--; 
      if (fish.days < 0) {
        fish.days = 6; 
        newFish.push_back(Fish()); 
      }
    }
    for (auto &fish : newFish) {
      school.push_back(fish); 
    }
    newFish.clear(); 
    std::cout << "Day #" << i << ": " << school.size() << " fish" << std::endl; 
  }
}