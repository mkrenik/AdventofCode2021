#include <iostream>
#include <sstream> 
#include <fstream>
#include <string> 
#include <assert.h> 
#include <cmath> 

#define FILE_NAME "input" 


const char segmentArray[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

struct Digit {

  bool segments[7] = {}; // initializes all to zero / false

  Digit() {}

  Digit(std::string n) {
    for (int i = 0; i<n.length(); i++) {
      for (int j = 0; j < 7; j++) {
        if (n[i] == segmentArray[j])  {
          segments[j] = true; 
        }
      }
    }
  }

  int count() {
    int count = 0; 
    for (int i = 0; i<7; i++) {
      if (segments[i] == true) {
        count++; 
      }
    }
    return count; 
  }
};

std::ostream& operator<<(std::ostream& os, const Digit& dt)
{
  for(int i =0; i<7; i++) {
    os << dt.segments[i];
  }
  return os;
}

bool equalsDigit(Digit a, Digit b) {
  for (int i =0 ; i<7; i++) {
    if (a.segments[i] != b.segments[i]) {
      return false; 
    }
  }
  return true; 
}

bool includesDigit(Digit a, Digit b) {
  for (int i =0 ; i<7; i++) {
    if (b.segments[i] == true) {
      if (a.segments[i] == false) {
        return false; 
      }
    }
  }
  return true; 
}

Digit subtractDigitSegments(Digit a, Digit b) {

  Digit diff; 
  for (int i =0 ; i<7; i++) {
    if (a.segments[i] == true) {
      diff.segments[i] = a.segments[i] - b.segments[i]; // boolean subtraction is XOR 
    }
  }
  return diff; 
}

void solveUnknowns(Digit (&mappings)[10], Digit (&inputs)[10]) {
  // Step 1: fill in the easy ones (1, 4, 7, 8)
  for (int i = 0; i<10; i++) {
    if (inputs[i].count() == 2) {
      mappings[1] = inputs[i]; 
    } else if (inputs[i].count() == 3) {
      mappings[7] = inputs[i]; 
    } else if (inputs[i].count() == 4) {
      mappings[4] = inputs[i]; 
    } else if (inputs[i].count() == 7) {
      mappings[8] = inputs[i]; 
    }      
  }

  // Step 2: solve the ones with length 6
  Digit countSix[3]; 
  for (int i=0, j=0; i<10; i++) {
    if (inputs[i].count() == 6) {
      countSix[j] = inputs[i];
      j++; 
      if (j == 3) break; 
    }
  }

  // Solve for 6 (only 6count that doesn't include 1)
  for (int i =0; i < 3; i++) {
    if (!includesDigit(countSix[i], mappings[1])) {
      mappings[6] = countSix[i]; 
      break; 
    }
  }

  // Solve for 0 (only 6count that doesn't include 4-1)
  Digit sub4and1 = subtractDigitSegments(mappings[4], mappings[1]); 
  for (int i =0; i < 3; i++) {
    if (!includesDigit(countSix[i], sub4and1)) {
      mappings[0] = countSix[i]; 
      break;
    }
  }

  // Solve for 9 (not equal to zero or six)
  for (int i =0; i < 3; i++) {
    if (!equalsDigit(countSix[i], mappings[0]) && !equalsDigit(countSix[i], mappings[6])) {
      mappings[9] = countSix[i]; 
      break;
    }
  }

  // Step 3: solve the ones with length 5
  Digit countFive[3]; 
  for (int i=0, j=0; i<10; i++) {
    if (inputs[i].count() == 5) {
      countFive[j] = inputs[i];
      j++; 
      if (j == 3) break; 
    }
  }

  // Solve for 3 (only 5count that includes 1)
  for (int i =0; i < 3; i++) {
    if (includesDigit(countFive[i], mappings[1])) {
      mappings[3] = countFive[i]; 
      break; 
    }
  }

  // Solve for 5 (not 3 and is included in 9)
  for (int i=0; i<3; i++) {
    if (!equalsDigit(countFive[i], mappings[3]) && includesDigit(mappings[9], countFive[i])) {
      mappings[5] = countFive[i]; 
      break; 
    }
  }

  // Solve for 2 (not equal to three or five)
  for (int i =0; i < 3; i++) {
    if (!equalsDigit(countFive[i], mappings[3]) && !equalsDigit(countFive[i], mappings[5])) {
      mappings[2] = countFive[i]; 
      break;
    }
  }
}

int main () {
 
  int easyDigits=0; 
  int outputSum = 0; 
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp, temp2;

    while (getline(f, temp)) {
      bool preDelimiter;
      int preDelimCount; 
      Digit inputs[10] = {};
      Digit mappings[10] = {};
      int outputDigits[4] = {}; 
      int postDelimCount;  

      preDelimCount = 0; 
      postDelimCount = 0; 

      std::stringstream tempStream(temp); 
      preDelimiter = true; 
      while(getline(tempStream, temp2, ' ')) 
      {
        if (temp2 == "|") {
          std::cout << "Inputs: "; 
          for(int i =0; i<10; i++ ) {
            std::cout << "[" << i << "] " << inputs[i] << "   "; 
          }
          std::cout << std::endl; 
          solveUnknowns(mappings, inputs); 
          std::cout << "Mappings: "; 
          for(int i =0; i<10; i++ ) {
            std::cout << "[" << i << "] " << mappings[i] << "   "; 
          }
          std::cout << std::endl; 
          preDelimiter = false; 
          continue; 
        }

        if (preDelimiter) {
          inputs[preDelimCount] = Digit(temp2); 
          std::cout << preDelimCount << ": " << temp2 << std::endl; 
          preDelimCount++; 
        } else {

          // Part 1: 
          int length = temp2.length(); 
          if (length == 2 || length == 3 || length == 4 || length == 7) {
            easyDigits++;
          } 

          // Part 2: 
          Digit result(temp2); 
          for (int i = 0; i < 10; i ++) {
            if (equalsDigit(mappings[i], result)) {
              outputDigits[postDelimCount] = i; 
              std::cout << i; 
              break; 
            }
          }
          postDelimCount++; 
        }
      }
      std::cout << std::endl; 

      int output = 0; 
      for (int i=0, j=3; i<4; i++, j--) {
        output += outputDigits[i] * std::pow(10, j); 
      }
      outputSum+= output; 
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }


  std::cout << "easy digits: " << easyDigits << std::endl;
  std::cout << "output sums: " << outputSum << std::endl;

  return 0; 
}