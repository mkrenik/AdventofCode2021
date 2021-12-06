#include <iostream>
#include <deque> 
#include <sstream>     
#include <fstream>

#define FILE_NAME "input"

struct FishBuckets {
  long int zero = 0;
  long int one = 0; 
  long int two = 0; 
  long int three = 0; 
  long int four = 0; 
  long int five = 0;
  long int six = 0; 
  long int seven = 0; 
  long int eight = 0; 

  void addInput(int x) {
    if (x == 0) zero++; 
    else if (x==1) one++;
    else if (x==2) two++; 
    else if (x==3) three++; 
    else if (x==4) four++; 
    else if (x==5) five++; 
    else if (x==6) six++; 
    else if (x==7) seven++; 
    else if (x==8) eight++; 
    else {
      std::cout << "ERROR" << std::endl; 
    }
  }

  long long int count() {
    return zero + one + two + three + four + five + six + seven + eight; 
  }
};

FishBuckets ageByDay(FishBuckets input) {
  FishBuckets output; 

  output.zero = input.one; 
  output.one = input.two; 
  output.two = input.three; 
  output.three = input.four;
  output.four = input.five;
  output.five = input.six;
  output.six = input.zero + input.seven; 
  output.seven = input.eight; 
  output.eight = input.zero; 

  return output; 
}


FishBuckets readInput() {

  FishBuckets school;
  std::fstream f(FILE_NAME, std::ios_base::in);

  if (f) {
    std::string temp;
    while (getline(f, temp, ',')) {
      school.addInput(stoi(temp));
    }
  } else {
    std::cout << "Error: couldn't open file" << std::endl;
  }

  return school; 
}

int main () {
  FishBuckets school; 
  school = readInput(); 

  for (int i =1 ; i<=256; i++) {
    FishBuckets newSchool = ageByDay(school); 
    school = newSchool; 
    std::cout << "Day #" << i << ": " << school.count() << " fish" << std::endl; 
  }
}