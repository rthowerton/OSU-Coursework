#include <iostream>
#include <set>
#include <string>
#include "parser.hpp"

extern int yylex();
extern Node* root;

void print_nodes(Node*);

int main() {
  if (!yylex()) {
    std::cout << "digraph G{" << std::endl;
    print_nodes(root, -1);
    std::cout << "}" << std::endl;
  }
}

void print_nodes(Node* node, int depth){
    if(node->nodes.size() != 0){
        for(int i = 0; i < node->nodes.size(); i++){
            if(node->value.empty()){
                if(depth >= 0){
                    std::cout << "  n0_" << depth << " [label=\"" << node->name << "\"];" << std::endl;
                    std::cout << "  n0_" << depth << std::endl;
                }
                else{
                    std::cout << "  n0" << " [label=\"" << node->name << "\"];" << std::endl;
                    std::cout << "  n0 -> n0_" << depth+1 << std::endl;
                }
            }
            else{
                if(depth >= 0){
                    std::cout << "  n0_" << depth << " [shape=box,label=\"" << node->nodes[i]->name << ": " << node->nodes[i]->value << "\"];" std::endl;
                }
                else{

                }
            }
        }
        print_nodes(node->nodes[i], depth+1);
    }
}