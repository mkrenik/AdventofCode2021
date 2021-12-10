#include <iostream>     // std::cout, std::endl
#include <fstream>      // std::fstream
#include <string>       // std::string

int main() 
{
    std::fstream f("input", std::ios_base::in);
    int increaseCount = 0; 
    int lastlastDepth = 0; 
    int lastDepth = 0;
    int currentDepth = 0;
    int lastDepthSum = 0;
    int depthSum = 0; 
    std::string tempLine;
    // int printLines = 0; 

    if(f){
        while(getline(f, tempLine)){
            lastlastDepth = lastDepth; 
            lastDepth = currentDepth;
            currentDepth = std::stoi(tempLine);

            if (lastlastDepth != 0) { // wait until at least 3 values are loaded (assumes depths can't be 0)
              lastDepthSum = depthSum; 
              depthSum = lastlastDepth + lastDepth + currentDepth;
            }

            // if (printLines < 10) {
            //   std::cout << "iter#" << printLines << ": " << lastDepthSum << " " << depthSum << std::endl;
            // }   

            if (lastDepthSum == 0) // skip the first 3 iterations of loop, when we only have one depth sum 
            {
              continue; 
            }

            if (depthSum > lastDepthSum) 
            {
              increaseCount++; 
            }

            // printLines++;
        }
    } else{
        std::cout << "Error: couldn't open file" << std::endl;
    }

    f.close();

    std::cout << "Number of increases: " << increaseCount << std::endl;
}