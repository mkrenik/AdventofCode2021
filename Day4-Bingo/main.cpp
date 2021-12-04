#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <array> 

#include "bingo.hpp"

int main() 
{
  std::fstream f("input", std::ios_base::in);

  std::vector<int> intArray; 
  std::vector<BingoCard> bingoCards; 


  if(f){
    // Read in the called numbers
    std::vector<std::string> strArray;
    std::string tmp;
    getline(f, tmp); 
    std::stringstream tempStream(tmp); 

    while(getline(tempStream, tmp, ',')) 
    {
      strArray.push_back(tmp);
    }

    // convert to int 
    for (auto &elem : strArray) {
      intArray.push_back(std::stoi(elem)); 
    }

    // debug: print int array
    for (auto &elem : intArray) {
      std::cout << elem << "\t";  
    }
    std::cout << std::endl; 

    // Read in the bingo boards 
    // TODO: this is very messy 

    std::string tempLine; 
    while(getline(f, tempLine)){  
      if (!tempLine.empty()) {
        std::cout << "Error: expected an empty line" << std::endl;
      }

      std::array<std::array<int, GRID_SIZE>, GRID_SIZE> bingoInput; 
      for(int i =0; i < GRID_SIZE; i++){
        int counter = 0; 
        std::string tmp2; 
        getline(f, tmp2); 
        std::stringstream tempStream2(tmp2); 
        while(getline(tempStream2 >> std::ws, tempLine, ' ')) {
          if (counter < GRID_SIZE) {
            bingoInput[i][counter] = std::stoi(tempLine); 
            counter++;
          } else {
            std::cout << "Error: unexpected number of values in input" << std::endl;
          }
        }
      }

      BingoCard newBingoCard(bingoInput); 
      // debug: print bingo cards
      // newBingoCard.print();
      bingoCards.push_back(newBingoCard); 
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  f.close();

  for (auto &drawn : intArray) {
    for (auto &card : bingoCards) {
      card.markNumber(drawn); 
      if (card.checkForWin()) {
        std::cout << "Winning card score: " << card.calculateScore() << std::endl; 
        return 0; 
      }
    }
  }

}
