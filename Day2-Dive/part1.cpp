#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <exception> 
int main() 
{
  std::fstream f("input", std::ios_base::in);

  int currentDepth = 0;
  int currentHorizontal = 0; 
  std::string tempLine;
  bool firstLine = true; 
  // int printLines = 0; 

  if(f){
    while(getline(f, tempLine)){  // gets the whole line
      std::stringstream tempStream(tempLine); 

      std::string tempInstr; 
      int tempDistance = 0;  
      std::string tempItem; 

      while (getline(tempStream, tempItem, ' ')) { 

        try { // don't love this... 
          tempDistance = std::stoi(tempItem);
        } catch (std::exception e) {
          tempInstr = tempItem; 
        }

      }

      std::cout << "tempInstr: " << tempInstr  << std::endl;
      std::cout << "tempDistance: " << tempDistance  << std::endl;

      if (tempInstr == "forward") {
        currentHorizontal += tempDistance; 
      } else if (tempInstr == "up") {
        currentDepth -= tempDistance; 
      } else if (tempInstr == "down") {
        currentDepth += tempDistance; 
      } else {
        std::cout << "Error: unable to parse instruction" << std::endl;
      }
    }
  } else{
    std::cout << "Error: couldn't open file" << std::endl;
  }

  f.close();

  std::cout << "Current Depth: " << currentDepth << std::endl;
  std::cout << "Current Horizontal: " << currentHorizontal << std::endl;
  std::cout << "Product: " << currentDepth * currentHorizontal << std::endl;
}