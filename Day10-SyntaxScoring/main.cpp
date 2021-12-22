  
#include <iostream> 
#include <fstream> 

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

int main() {  
  std::fstream f(FILE_NAME, std::ios_base::in);
  std::string temp; 

  int errorScore = 0; 

  // read in height map 
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
          errorScore += 1197;
          break; 
        }
      } else if (temp[i] == ']') {
        if (head_ref->type == '[') {
          removeNode(); 
        } else {
          errorScore += 57;
          break; 
        }        
      } else if (temp[i] == '>') {
        if (head_ref->type == '<') {
          removeNode(); 
        } else {
          errorScore += 25137;
          break; 
        }        
      } else if (temp[i] == ')') {
        if (head_ref->type == '(') {
          removeNode(); 
        } else {
          errorScore += 3;
          break; 
        }        
      } else {
        std::cout << "ERROR" << std::endl; 
        return -1; 
      }
    }
  }

  std::cout << "Total error: " << errorScore << std::endl; 
}
