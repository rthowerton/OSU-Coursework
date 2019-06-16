#include <iostream>
#include <set>
#include "parser.hpp"

extern int yylex();
extern Node* root;

void print_nodes(Node*);

int main() {
  if (!yylex()) {
    std::cout << "digraph G{" << std::endl;
    print_nodes(root);
    std::cout << "}" << std::endl;
  }
}

void print_nodes(Node* node){
    if(node->nodes.size() != 0){
        for(int i = 0; i < node->nodes.size(); i++){
            std::cout << node->nodes[i]->name << ' ' << node->nodes[i]->value << std::endl;
            print_nodes(node->nodes[i]);
        }
    }
}