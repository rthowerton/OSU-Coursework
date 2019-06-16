#include <iostream>
#include <set>
#include <vector>

extern int yylex();
extern bool _error;
extern std::set<std::string> identifiers;
extern std::vector<std::string> statements;

int main() {
  std::cout << "#include <iostream>" << std::endl;
  std::cout << "int main(){" << std::endl;
  if (!yylex()) {
    if (!_error) {
      std::cout << "\n/* Variables */\n" << std::endl;
      std::set<std::string>::iterator its;
      for (its = identifiers.begin(); its != identifiers.end(); its++) {
        std::cout << "double " << *its << ";" << std::endl;
      }

      std::cout << "\n/* Begin program */\n" << std::endl;

      std::vector<std::string>::iterator itv;
      for (itv = statements.begin(); itv != statements.end(); itv++) {
        std::cout << *itv << std::endl;
      }

      std::cout << "\n/* End program */\n" << std::endl;
      
      for (its = identifiers.begin(); its != identifiers.end(); its++){
        std::cout << "std::cout << \"" << *its << ": \" << " << *its << " << std::endl;" << std::endl;
      }

      std::cout << "return 0;" << std::endl;
      std::cout << "}" << std::endl;
    }
    return 0;
  } else {
    return 1;
  }
}