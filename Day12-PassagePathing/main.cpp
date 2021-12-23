#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector> 
#include <memory> 

#define FILE_NAME "input"

struct Cave {
  std::string name; 
  bool isSmall;
  std::vector<std::shared_ptr<Cave>> connections; 

  Cave(std::string n) {
    name = n; 
  }

  void print() {
    std::cout << "Cave: " << name << std::endl << "\tConn: "; 
    for(auto &conn : connections) {
      std::cout << conn->name << " "; 
    }
    std::cout << std::endl;
  }
};

std::shared_ptr<Cave> findCaveInList(std::vector<std::shared_ptr<Cave>> &list, std::string caveName) {
  for ( auto& cave : list ) {
    if (cave->name == caveName) {
      return cave; 
    }
  }
  return nullptr; 
}

void addCave(std::vector<std::shared_ptr<Cave>> &list, std::string firstCave, std::string secondCave) {
  // Add first cave to list, if not already there
  std::shared_ptr<Cave> firstCavePtr = findCaveInList(list, firstCave);
  if (firstCavePtr == nullptr) {
    firstCavePtr = std::make_shared<Cave>(firstCave); 
    list.push_back(firstCavePtr); 
  }

  // Add second cave to list, if not already there
  std::shared_ptr<Cave> secondCavePtr = findCaveInList(list, secondCave);
  if (secondCavePtr == nullptr) {
    secondCavePtr = std::make_shared<Cave>(secondCave); 
    list.push_back(secondCavePtr);
  }

  // Add connection to cave, if not already there 
  bool isNewConn = true; 
  for ( auto& conn : firstCavePtr->connections ) {
    if (conn->name == secondCave) {
      isNewConn = false; 
      break; 
    }
  }
  // end shouldn't have connections
  // start shouldn't be a connection 
  if (isNewConn && firstCavePtr->name != "end" && secondCave != "start") {
    firstCavePtr->connections.push_back(secondCavePtr);
  }
}

bool hasDoubleVisited(std::vector<std::shared_ptr<Cave>> route) {
  for (int i =1; i < route.size(); i++) { // discount start 
    if (std::isupper(route[i]->name[0])) {
      continue; 
    }
    for (int j =i+1; j<route.size(); j++) {
      if (std::isupper(route[j]->name[0])) {
        continue; 
      } 
      if (route[i]->name == route[j]->name) {
        return true; 
      }      
    }
  }
  return false;
}

void findPath(std::shared_ptr<Cave> start, std::vector<std::shared_ptr<Cave>> route, int &routeNumber) {
  route.push_back(start); 
  if (start->name == "end") {
    for (auto& node: route) {
       std::cout << node->name; 
      if (node->name != "end") {
      std::cout << "->"; 
      } 
    }
    std::cout << std::endl; 
    routeNumber++;
    return; 
  } 
  for (auto &conn : start->connections) {
    if (std::islower(conn->name[0])) {
      bool hasDoubled = hasDoubleVisited(route); 
      bool hasVisitedSmallCave = false; 
      // search route for existing small caves with the same name 
      for (auto &node : route) {
        if(conn == node) {
          hasVisitedSmallCave = true; 
          break;
        }
      }
      if (hasVisitedSmallCave && hasDoubled) {
        continue; // doesn't recurse with this connection 
      } 
    }

    findPath(conn, route, routeNumber);
  }
}

int main () {
  std::vector<std::shared_ptr<Cave>> caveList; 
  int routeNumber = 0; 
  std::fstream f(FILE_NAME, std::ios_base::in);
  std::string temp; 
  if (f) {
    while(getline(f, temp)) {
      int pos = temp.find('-');
      std::string first = temp.substr(0, pos);
      std::string second = temp.substr(pos+1,temp.length()); 

      // std::cout << first << "-" << second << std::endl; 

      addCave(caveList, first, second); 
      addCave(caveList, second, first); 
    }

  } else {
    std::cout << "Error: could not open file" << std::endl; 
  }

  for(auto & cave : caveList) {
    cave->print(); 
  }

  // Depth first search to enumerate path options 
  std::vector<std::shared_ptr<Cave>> route; 
  findPath(findCaveInList(caveList, "start"), route, routeNumber);
  std::cout << "Routes: " << routeNumber << std::endl; 
}

