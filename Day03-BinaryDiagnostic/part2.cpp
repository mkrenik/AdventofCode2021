#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <vector>       // std::vector
#include <bitset>       // std::bitset
#include <algorithm>    // std::sort

int main() 
{
  std::fstream f("input", std::ios_base::in);
  std::string tempLine;

  // array index 0 corresponds to most significant binary bit 
  // int numZeros[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; 
  // int numOnes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};  

  std::vector<int> input; 

  if(f){
    while(getline(f, tempLine)){  // gets the whole line

      int tempInt = stoi(tempLine, nullptr, 2); 
      input.push_back(tempInt); 

      // for (int i=0, j=11; i<12; i++, j--) {
      //   if (((tempInt >> j) & 1) == 0) {
      //     numZeros[i]++;
      //   }
      //   else {
      //     numOnes[i]++; 
      //   }
      // }
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  f.close();

  sort(input.begin(), input.end()); 

  // // find the "ideal" values for oxyGen and co2Scrub
  // int idealOxygen = 0;
  // int idealc02Scrub = 0; 
  
  // // depending on # ones/zeros, put correct bit into gamma/epsilon
  // for (int i=0; i<12; i++) {
  //   std::cout << numOnes[i] << "     " << numZeros[i] << std::endl; 
  //   if (numOnes[i] >= numZeros[i]) {
  //     idealOxygen = (idealOxygen << 1) | 1;
  //     idealc02Scrub = (idealc02Scrub << 1) | 0;
  //   } else {
  //     idealOxygen = (idealOxygen << 1) | 0;
  //     idealc02Scrub = (idealc02Scrub << 1) | 1;
  //   }
  // }

  // std::bitset<12> iOx(idealOxygen); 
  // std::bitset<12> ico2(idealc02Scrub); 

  // std::cout << "Ideal oxygen: " << iOx << std::endl; 
  // std::cout << "Ideal co2 scrub: " << ico2 << std::endl; 


  // start with full list copies 
  std::vector<int> oxygenGenRating = input; 
  std::vector<int> c02ScrubRating = input; 

  // performance optimization 
  // instead of removing items from the vector, which causes vector re-sizing
  // just push them onto the back of a new vector and start with that new vector 
  // each time we iterate with the next bit 
  std::vector<int> newOx;
  std::vector<int> newC02;

  int finalOx; 
  int finalc02;

  for (int i = 11; i>=0; i--) {  
    std::cout << "shifts: " << i << std::endl; 

    // find most common value still in vector
    int numZeros = 0;
    int numOnes = 0; 
    for (auto & elem: oxygenGenRating) {
      if (((elem >> i) & 1) == 0) numZeros++; 
      else numOnes++; 
    }

    for (auto & elem : oxygenGenRating) {
      if (((elem >> i) & 1) == ((numOnes >= numZeros) ? 1 : 0)) {
        newOx.push_back(elem); 
        std::cout << elem << "\t"; 
      }
    }
    std::cout << std::endl; 

    if (newOx.size() == 1) {
      finalOx = newOx.back();
      break; 
    }
    oxygenGenRating = newOx; 
    newOx.clear(); 
  }
  std::bitset<12> actual_iOx(finalOx); 
  std::cout << "oxygenGenRating: " << actual_iOx << std::endl;


  for (int i = 11; i>=0; i--) { 
    std::cout << "shift: " << i << std::endl; 

    // find most common value still in vector
    int numZeros = 0;
    int numOnes = 0; 
    for (auto & elem: c02ScrubRating) {
      if (((elem >> i) & 1) == 0) numZeros++; 
      else numOnes++; 
    }

    for (auto & elem : c02ScrubRating) {
      if (((elem >> i) & 1) == ((numOnes >= numZeros) ? 0 : 1)) {
        newC02.push_back(elem); 
        std::cout << elem << "\t"; 
      }
    }
    std::cout << std::endl; 

    if (newC02.size() == 1) {
      finalc02 = newC02.back();
      break; 
    }
    c02ScrubRating = newC02; 
    newC02.clear(); 
  }
  std::bitset<12> actual_c02(finalc02); 
  std::cout << "c02ScrubRating: " << actual_c02 << std::endl;

  std::cout << "Product: " << finalOx * finalc02 << std::endl;
}