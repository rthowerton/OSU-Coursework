#include <iostream>

#include "ast.hpp"
#include "parser.hpp"

extern int yylex();

extern ASTBlock* programBlock;

/*int main() {
  if (!yylex()) {
    if (programBlock) {
      std::cout << generateGVSpec(programBlock);
    }
  }
}*/

int main(int argc, char const *argv[]) {
   TheModule = new llvm::Module("LLVM_Demo", TheContext);

   llvm::FunctionType* fooFnType = llvm::FunctionType::get(
	 llvm::Type::getFloatTy(TheContext), false
	 );

   llvm::Function* fooFn = llvm::Function::Create(
	 fooFnType,
	 llvm::GlobalValue::ExternalLinkage,
	 "foo",
	 TheModule
	 );

   llvm::BasicBlock* entryBlock =
      llvm::BasicBlock::Create(TheContext, "entry", fooFn);
   TheBuilder.SetInsertPoint(entryBlock);

   llvm::Value* expr1 = binaryOperation(
	 numericConstant(4),
	 numericConstant(2),
	 '*'
	 );
   llvm::Value* expr2 = binaryOperation(
	 expr1,
	 numericConstant(8),
	 '+'
	 );

   std::string var1("a");
   llvm::Value* assn = assignmentStatement(var1, expr2);

   llvm::Value* expr3 = binaryOperation(
	 variableValue(var1),
	 numericConstant(4),
	 '/'
	 );
   std::string var2("b");
   llvm::Value* assn2 = assignmentStatement(var2, expr3);

   llvm::Value* ifElse = ifElseStatement();

   // TheBuilder.CreateRetVoid();
   TheBuilder.CreateRet(variableValue("c"));

   doOptimizations(fooFn);

   llvm::verifyFunction(*fooFn);
   TheModule->print(llvm::outs(), NULL);

   std::string filename = "foo.o";
   generateObjCode(filename);

   delete TheModule;
   return 0;
}
