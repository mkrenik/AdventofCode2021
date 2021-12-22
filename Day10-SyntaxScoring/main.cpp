  
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 

#define FILE_NAME "input"

struct Node * head_ref = nullptr; 

struct Node {
  char type;
  struct Node *prev; 
};

void addNode(struct Node * prev, char new_data) {
    struct Node * new_node = new Node(); 
    new_node->prev = prev; 
    new_node->type = new_data; 
    head_ref = new_node; 
}

void removeNode() {
  struct Node * node_to_delete = head_ref; 
  head_ref = head_ref->prev;
  delete node_to_delete; 
}

std::string cleanNodes() {
  std::string completion = ""; 
  while (head_ref != nullptr) {
    if (head_ref->type == '{') {
      completion.append("}"); 
    } else if (head_ref->type == '[') {
      completion.append("]"); 
    } else if (head_ref->type == '<') {
      completion.append(">"); 
    } else if (head_ref->type == '(') {
      completion.append(")"); 
    }
    removeNode(); 
  }
  return completion; 
}

int main() {  
  std::fstream f(FILE_NAME, std::ios_base::in);
  std::string temp; 
  std::vector<long int> completionScores; 
  int errorScore = 0; 
  long int completionScore; 

  while (getline(f, temp)) {
    std::cout << temp << std::endl; 
    for (int i =0; i< temp.length(); i++) {
      if (temp[i] == '{' || 
          temp[i] == '[' || 
          temp[i] == '<' ||
          temp[i] == '(') {
        addNode(head_ref, temp[i]); 
      } else if (temp[i] == '}') {
        if (head_ref->type == '{') {
          removeNode(); 
        } else {
          std::cout << "broken line" << std::endl;
          errorScore += 1197;
          cleanNodes();
          break; 
        }
      } else if (temp[i] == ']') {
        if (head_ref->type == '[') {
          removeNode(); 
        } else {
          std::cout << "broken line" << std::endl;
          errorScore += 57;
          cleanNodes();
          break; 
        }        
      } else if (temp[i] == '>') {
        if (head_ref->type == '<') {
          removeNode(); 
        } else {
          std::cout << "broken line" << std::endl;
          errorScore += 25137;
          cleanNodes();
          break; 
        }        
      } else if (temp[i] == ')') {
        if (head_ref->type == '(') {
          removeNode(); 
        } else {
          std::cout << "broken line" << std::endl; 
          errorScore += 3;
          cleanNodes();
          break; 
        }        
      } else {
        std::cout << "ERROR" << std::endl; 
        return -1; 
      }
    }

    // Part 2: get string to finish incomplete lines 
    std::string completionString = cleanNodes(); 
    std::cout << "completion: " << completionString << std::endl; 

    // calculate scores and add to list 
    completionScore = 0; 
    for (int i = 0; i < completionString.length(); i++) {
      completionScore *= 5; 

      int scoreAddition; 
      if (completionString[i] == ')') scoreAddition = 1; 
      else if  (completionString[i] == ']') scoreAddition = 2;
      else if  (completionString[i] == '}') scoreAddition = 3;
      else if  (completionString[i] == '>') scoreAddition = 4;

      completionScore += scoreAddition; 
    }
    std::cout << "completion score: " << completionScore << std::endl;
    if (completionScore != 0) {
      completionScores.push_back(completionScore); 
    }
    // sort list 
    std::sort(completionScores.begin(), completionScores.end()); 
  }

  std::cout << "Total error: " << errorScore << std::endl; 
  std::cout << "Median completion score: " << completionScores.at(completionScores.size()/2) << std::endl; 
}
