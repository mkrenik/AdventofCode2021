#include <iostream>
#include <sstream> 
#include <fstream>
#include <string> 
#include <assert.h> 

#define FILE_NAME "input" 

int main () {
 
  int easyDigits=0; 
 
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp, temp2;
    bool preDelimiter;

    while (getline(f, temp)) {
      std::stringstream tempStream(temp); 
      preDelimiter = true; 
      while(getline(tempStream, temp2, ' ')) 
      {
        if (temp2 == "|") {
          preDelimiter = false; 
          continue; 
        }

        if (preDelimiter) {

        } else {
          int length = temp2.length(); 
          if (length == 2 || length == 3 || length == 4 || length == 7) {
            easyDigits++;
          } 
        }
      }
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  std::cout << "easy digits: " << easyDigits << std::endl;

  return 0; 
}