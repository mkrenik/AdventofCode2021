#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::stringstream

int main() 
{
  std::fstream f("input", std::ios_base::in);

  int currentDepth = 0;
  int currentHorizontal = 0; 
  std::string tempLine;
  bool firstLine = true; 

  // array index 0 corresponds to most significant binary bit 
  int numZeros[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; 
  int numOnes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};  

  if(f){
    while(getline(f, tempLine)){  // gets the whole line

      int tempInt = stoi(tempLine, nullptr, 2); 

      for (int i=0, j=11; i<12; i++, j--) {
        if (((tempInt >> j) & 1) == 0) {
          numZeros[i]++;
        }
        else {
          numOnes[i]++; 
        }
      }
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  f.close();

  int gammaRate = 0;
  int epsilonRate = 0; 
  
  for (int i=0; i<12; i++) {
    if (numOnes[i] > numZeros[i]) {
      gammaRate = (gammaRate << 1) | 1;
      epsilonRate = (epsilonRate << 1) | 0;
    } else {
      gammaRate = (gammaRate << 1) | 0;
      epsilonRate = (epsilonRate << 1) | 1;
    }
  }

  std::cout << "gammaRate: " << gammaRate << std::endl;
  std::cout << "episolongRate: " << epsilonRate << std::endl;
  std::cout << "Product: " << gammaRate * epsilonRate << std::endl;
}