#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm> 
#include <iomanip>

#define GRID_SIZE 100
#define MULTIPLIER 5  // part 2

// TODO: can add heuristic (maximum possible minimal cost) to reduce total computation time 
// #define HEURISTIC (9*GRID_SIZE*MULTIPLIER*GRID_SIZE*MULTIPLIER) 

// function prototypes
bool isValid(std::pair<int, int> node, bool (&vis)[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]); 
std::vector<std::pair<int, int>> getValidNeighbors(std::pair<int, int> node, bool (&vis)[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]); 
int getExpandedNodeCost(int x, int y, int (&nc)[GRID_SIZE][GRID_SIZE]);
int calculateHeuristic(GRID_SIZE); 
int main(int argc, char *argv[]) {

  int nodeCost[GRID_SIZE][GRID_SIZE]{};  // null-init 
  int pathCost[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]{};  // null-init
  bool visited[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]{};  // null-init

  if (argc == 2) {
    std::string line; 
    std::fstream f(argv[1], std::ios_base::in);
    if (f) {
      int row = 0; 
      while(getline(f, line)) {
        for (int column =0; column<line.length(); column++) {
          nodeCost[row][column] = line.at(column) - '0';
        }
        row++; 
      }

    } else {
      std::cout << "Error opening file" << std::endl;
      return -1; 
    }
  } else {
    std::cout << "Error with input arguments" << std::endl;
    return -1; 
  }


  // print grid
  // for (int i = 0; i < GRID_SIZE; i++) {
  //   for (int j = 0; j < GRID_SIZE; j++) {
  //     std::cout << nodeCost[i][j];
  //   }
  //   std::cout << std::endl; 
  // }

    // print grid
  // for (int i = 0; i < GRID_SIZE; i++) {
  //   for (int j = 0; j < GRID_SIZE; j++) {
  //     std::cout << nodeCost[i][j];
  //   }
  //   std::cout << std::endl; 
  // }



  // Dijkstra's algortihm
  // 1. visit an unvisited node 
  // 2. go to all non-visited neighbors and calculate the cost from that node 
  // 3. set the path cost for that node if it is lower
  // 4. set the current node to being visited 
  // 5. go to the unvisited node with the smallest pathCost 
  // 6. terminate when destination node has been marked as visited  

  std::pair<int, int> currentNode(0,0); 
  pathCost[currentNode.first][currentNode.second] = 0; 

  std::vector<std::pair<int,int>> nextNodeList;

  while ( visited[GRID_SIZE*MULTIPLIER-1][GRID_SIZE*MULTIPLIER-1] != true ) {

    // std::cout << "Current Node: (" << currentNode.first << "," << currentNode.second << ")" << std::endl; 

    std::vector<std::pair<int, int>> neighbors = getValidNeighbors(currentNode, visited); 

    for (auto & node : neighbors) {
      // std::cout << "\tNeighbor Node: (" << node.first << "," << node.second << ")" << std::endl; 
      int newPathCost = pathCost[currentNode.first][currentNode.second] + getExpandedNodeCost(node.first, node.second, nodeCost);
      if (newPathCost < pathCost[node.first][node.second] || pathCost[node.first][node.second] == 0) {
        pathCost[node.first][node.second] = newPathCost; 
      }

      // if node isn't added to next node list yet, add it. 
      bool isInNext = false; 
      for (auto & next : nextNodeList) {
        if (node.first == next.first && node.second == next.second) {
          isInNext = true; 
          break;
        }
      }
      if (!isInNext) {
        nextNodeList.push_back(node); 
      }

    }

    visited[currentNode.first][currentNode.second] = true; 

    // find lowest cost 
    int minPathCost = INT_MAX; 
    std::pair<int,int> minPathCostLoc; 
    int indexOfMin=0; // should never be used at zero
    for (int i = 0; i < nextNodeList.size(); i++) {
      if (pathCost[nextNodeList[i].first][nextNodeList[i].second] < minPathCost) {
        minPathCost = pathCost[nextNodeList[i].first][nextNodeList[i].second];
        minPathCostLoc = nextNodeList[i]; 
        indexOfMin = i; 
      }
    }
    nextNodeList.erase(nextNodeList.begin()+indexOfMin); 

    // find lowest cost that isn't visited in graph 
    // TODO: this combs the entire graph, where it be better if we just kept a list of neighbors from above 
    // Problem is this list doesn't have an easy way to be accessed/sorted, so needs an intrusive code change
    // int minPathCost = INT_MAX; 
    // std::pair<int,int> minPathCostLoc; 
    // for (int i = 0; i < GRID_SIZE*MULTIPLIER; i++ ) {
    //   for (int j = 0; j < GRID_SIZE*MULTIPLIER; j++) {
    //     if (visited[i][j] == false && pathCost[i][j] < minPathCost && pathCost[i][j] != 0) {
    //       minPathCost = pathCost[i][j]; 
    //       minPathCostLoc.first = i; 
    //       minPathCostLoc.second = j; 
    //     }
    //   }
    // }

    // set current node to lowest cost on the list 
    currentNode = minPathCostLoc; 
    
  }

  // print grid
  // for (int i = 0; i < GRID_SIZE*MULTIPLIER; i++) {
  //   for (int j = 0; j < GRID_SIZE*MULTIPLIER; j++) {
  //     std::cout << std::setw(2) << pathCost[i][j];
  //   }
  //   std::cout << std::endl; 
  // }

  std::cout << "Path cost to finish node: " << pathCost[GRID_SIZE*MULTIPLIER-1][GRID_SIZE*MULTIPLIER-1] << std::endl; 

  return 0;;
}

int getExpandedNodeCost(int x, int y, int (&nc)[GRID_SIZE][GRID_SIZE]) {

  int originalCost = nc[x%GRID_SIZE][y%GRID_SIZE]; 
  int addition = x / GRID_SIZE + y / GRID_SIZE; 
  int newCost = originalCost + addition; 

  while (newCost > 9) {
    newCost -= 9; 
  }

  return newCost;
}

// validity:
// - inside of the grid
// - unvisited 
bool isValid(std::pair<int, int> node, bool (&vis)[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]) {
  if (node.first < 0 || node.first >= GRID_SIZE*MULTIPLIER) {
    return false; 
  }
  if (node.second < 0 || node.second >= GRID_SIZE*MULTIPLIER) {
    return false; 
  }  
  if (vis[node.first][node.second]) {
    return false; 
  }
  return true; 
}

// test adjacent points on four cardinal directions 
std::vector<std::pair<int, int>> getValidNeighbors(std::pair<int, int> node, bool (&vis)[GRID_SIZE*MULTIPLIER][GRID_SIZE*MULTIPLIER]) {
  std::vector<std::pair<int, int>> neighbors;

  std::pair<int,int> up(node.first, node.second+1); 
  if (isValid(up, vis)) {
    neighbors.push_back(up); 
  }

  std::pair<int,int> down(node.first, node.second-1); 
  if (isValid(down, vis)) {
    neighbors.push_back(down); 
  }

  std::pair<int,int> left(node.first-1, node.second); 
  if (isValid(left, vis)) {
    neighbors.push_back(left); 
  }

  std::pair<int,int> right(node.first+1, node.second); 
  if (isValid(right, vis)) {
    neighbors.push_back(right); 
  }  

  return neighbors; 
}