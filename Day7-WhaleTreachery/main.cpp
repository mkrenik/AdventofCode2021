#include <iostream>
#include <vector> 
#include <sstream>     
#include <fstream>
#include <algorithm>
#include <cmath>

#define FILE_NAME "input"

std::vector<int> readInput() {
  std::vector<int> vect; 
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp;
    while (getline(f, temp, ',')) {
      vect.push_back(stoi(temp));
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  return vect; 
}


int fuelCost(int diff) {
  int sum = 0; 
  for (int i = 1; i <= diff; i++ ) {
    sum += i; 
  }
  return sum; 
}


int main() {

  std::vector<int> crabs; 
  crabs = readInput(); 

  int maxPos = 0;
  int minPos = 100000;

  for (int i = 0; i < crabs.size(); i++)
  {
    if (crabs[i] < minPos) {
      minPos = crabs[i]; 
    }

    if (crabs[i] > maxPos) {
      maxPos = crabs[i]; 
    }
  }

  std::cout << "maxPos: " << maxPos << " minPos: " << minPos << std::endl; 

  int fuelUsed; 
  long int minFuelUsed = 10000000000; 

  for (int i=minPos; i<=maxPos; i++) {
    fuelUsed = 0; 
    for (int j = 0; j < crabs.size(); j++)
    {
      fuelUsed += fuelCost(std::abs(i-crabs[j])); 
    }
    if (fuelUsed < minFuelUsed) {
      minFuelUsed = fuelUsed; 
    }
  }

  std::cout << "minFuelUsed: " << minFuelUsed << std::endl; 

}