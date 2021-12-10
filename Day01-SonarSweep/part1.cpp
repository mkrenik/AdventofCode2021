#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string

int main() 
{
    std::fstream f("input", std::ios_base::in);
    int increaseCount = 0; 
    int lastDepth = 0;
    int currentDepth = 0;
    std::string tempLine;
    bool firstLine = true; 
    // int printLines = 0; 

    if(f){
        while(getline(f, tempLine)){
            lastDepth = currentDepth;
            currentDepth = std::stoi(tempLine);
            if (!firstLine && currentDepth > lastDepth) 
            {
              increaseCount++; 
            }
            // if (printLines < 10) {
            //   std::cout << firstLine << " " << lastDepth << " " << currentDepth << " " << increaseCount << std::endl;
            // }   
            if (firstLine) {
              firstLine = false; 
            }          
            // printLines++;
        }
    } else{
        std::cout << "Error: couldn't open file" << std::endl;
    }

    f.close();

    std::cout << "Number of increases: " << increaseCount << std::endl;
}