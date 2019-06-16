#include <sstream>

#include "ast.hpp"
#include "parser.hpp"

/*
 * Simple template function to convert a value of any type to a string
 * representation.  The type must have an insertion operator (i.e. operator<<).
 */
template <class T>
std::string toString(const T& val) {
   std::ostringstream out;
   out << val;
   return out.str();
}

/*
 * Function to generate GraphView spec for the subtree rooted at any node in
 * an AST.
 *
 * @param node An AST node.
 *
 * @return Returns a string containing a complete GraphView specification to
 *   visualize the AST subtree rooted at node.
 */
std::string generateGVSpec(ASTNode* node) {
   std::string gvSpec = "digraph G {\n";
   std::string nodeName = "n0";
   node->generateGVSpec(nodeName, gvSpec);
   gvSpec += "}\n";
   return gvSpec;
}

/****************************************************************************
 **
 ** Below is the implementation of generateGVSpec() for each class defined in
 ** ast.hpp.  Please see the documentation in ast.hpp for a desription of
 ** this function.
 **
 ****************************************************************************/

void ASTIdentifier::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName
      + " [shape=box,label=\"Identifier: " + *this->name + "\"];\n";
}


void ASTFloat::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName
      + " [shape=box,label=\"Float: " + toString(this->value) + "\"];\n";
}


void ASTInteger::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName
      + " [shape=box,label=\"Integer: " + toString(this->value) + "\"];\n";
}


void ASTBoolean::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName
      + " [shape=box,label=\"Boolean: " + toString(this->value) + "\"];\n";
}


void ASTBinaryOperatorExpression::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   std::string lhsNodeName = nodeName + "_lhs";
   std::string rhsNodeName = nodeName + "_rhs";
   std::string opStr;
   switch (this->op) {
      case PLUS:
	 opStr = "PLUS";
	 break;
      case MINUS:
	 opStr = "MINUS";
	 break;
      case TIMES:
	 opStr = "TIMES";
	 break;
      case DIVIDEDBY:
	 opStr = "DIVIDEDBY";
	 break;
      case EQ:
	 opStr = "EQ";
	 break;
      case NEQ:
	 opStr = "NEQ";
	 break;
      case GT:
	 opStr = "GT";
	 break;
      case GTE:
	 opStr = "GTE";
	 break;
      case LT:
	 opStr = "LT";
	 break;
      case LTE:
	 opStr = "LTE";
	 break;
   }

   gvSpec += "  " + nodeName + " [label=\"" + opStr + "\"];\n";
   gvSpec += "  " + nodeName + " -> " + lhsNodeName + ";\n";
   this->lhs->generateGVSpec(lhsNodeName, gvSpec);
   gvSpec += "  " + nodeName + " -> " + rhsNodeName + ";\n";
   this->rhs->generateGVSpec(rhsNodeName, gvSpec);
}


void ASTAssignmentStatement::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   std::string lhsNodeName = nodeName + "_lhs";
   std::string rhsNodeName = nodeName + "_rhs";
   gvSpec += "  " + nodeName + " [label=\"Assignment\"];\n";
   gvSpec += "  " + nodeName + " -> " + lhsNodeName + ";\n";
   this->lhs->generateGVSpec(lhsNodeName, gvSpec);
   gvSpec += "  " + nodeName + " -> " + rhsNodeName + ";\n";
   this->rhs->generateGVSpec(rhsNodeName, gvSpec);
}


void ASTBlock::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName + " [label=\"Block\"];\n";
   for (int i = 0; i < this->statements.size(); i++) {
      std::string childNodeName = nodeName + "_" + toString(i);
      gvSpec += "  " + nodeName + " -> " + childNodeName + ";\n";
      this->statements[i]->generateGVSpec(childNodeName, gvSpec);
   }
}


void ASTIfStatement::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   std::string conditionNodeName = nodeName + "_cond";
   std::string ifBlockNodeName = nodeName + "_if";
   gvSpec += "  " + nodeName + " [label=\"If\"];\n";
   gvSpec += "  " + nodeName + " -> " + conditionNodeName + ";\n";
   this->condition->generateGVSpec(conditionNodeName, gvSpec);
   gvSpec += "  " + nodeName + " -> " + ifBlockNodeName + ";\n";
   this->ifBlock->generateGVSpec(ifBlockNodeName, gvSpec);

   if (this->elseBlock) {
      std::string elseBlockNodeName = nodeName + "_else";
      gvSpec += "  " + nodeName + " -> " + elseBlockNodeName + ";\n";
      this->elseBlock->generateGVSpec(elseBlockNodeName, gvSpec);
   }
}


void ASTWhileStatement::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   std::string conditionNodeName = nodeName + "_cond";
   std::string whileBlockNodeName = nodeName + "_while";
   gvSpec += "  " + nodeName + " [label=\"While\"];\n";
   gvSpec += "  " + nodeName + " -> " + conditionNodeName + ";\n";
   this->condition->generateGVSpec(conditionNodeName, gvSpec);
   gvSpec += "  " + nodeName + " -> " + whileBlockNodeName + ";\n";
   this->whileBlock->generateGVSpec(whileBlockNodeName, gvSpec);
}


void ASTBreakStatement::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
   gvSpec += "  " + nodeName + " [label=\"Break\"];\n";
}


llvm::Value* numericConstant(float val) {
   return llvm::ConstantFP::get(TheContext, llvm::APFloat(val));
}


llvm::Value* variableValue(const std::string& name) {
   llvm::Value* val = TheSymbolTable[name];
   if (!val) {
      std::cerr << "Invalid variable name: " << name << std::endl;
      return NULL;
   }
   return TheBuilder.CreateLoad(val, name.c_str());
}


llvm::Value* binaryOperation(llvm::Value* lhs, llvm::Value* rhs, char op) {
   if (!lhs || !rhs) {
      return NULL;
   }

   switch (op) {
      case '+':
	 return TheBuilder.CreateFAdd(lhs, rhs, "addtmp");
      case '-':
	 return TheBuilder.CreateFSub(lhs, rhs, "subtmp");
      case '*':
	 return TheBuilder.CreateFMul(lhs, rhs, "multmp");
      case '/':
	 return TheBuilder.CreateFDiv(lhs, rhs, "divtmp");
      case '<':
	 lhs = TheBuilder.CreateFCmpULT(lhs, rhs, "lttmp");
	 return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
      default:
	 std::cerr << "Invalid operator:" << op << std::endl;
	 return NULL;
   }
}


llvm::AllocaInst* generateEntryBlockAlloca(std::string& name) {
   llvm::Function* currFn =
      TheBuilder.GetInsertBlock()->getParent();
   llvm::IRBuilder<> tmpBuilder(&currFn->getEntryBlock(),
	 currFn->getEntryBlock().begin());

   return tmpBuilder.CreateAlloca(llvm::Type::getFloatTy(TheContext), 0, name.c_str());
}


llvm::Value* assignmentStatement(std::string& lhs, llvm::Value* rhs) {
   if (!rhs) {
      return NULL;
   }
   if (!TheSymbolTable.count(lhs)) {
      // Allocate lhs
	 TheSymbolTable[lhs] = generateEntryBlockAlloca(lhs);
   }
   return TheBuilder.CreateStore(rhs, TheSymbolTable[lhs]);
}


llvm::Value* ifElseStatement() {
   llvm::Value* cond = binaryOperation(variableValue("b"), numericConstant(8), '<');
   if (!cond) {
      return NULL;
   }
   cond = TheBuilder.CreateFCmpONE(cond, numericConstant(0), "ifcond");

   llvm::Function* currFn =
      TheBuilder.GetInsertBlock()->getParent();
   llvm::BasicBlock* ifBlock =
      llvm::BasicBlock::Create(TheContext, "ifBlock", currFn);
   llvm::BasicBlock* elseBlock =
      llvm::BasicBlock::Create(TheContext, "elseBlock");
   llvm::BasicBlock* contBlock =
      llvm::BasicBlock::Create(TheContext, "contBlock");

   TheBuilder.CreateCondBr(cond, ifBlock, elseBlock);
   TheBuilder.SetInsertPoint(ifBlock);

   /* If block */
   llvm::Value* aTimesB = binaryOperation(
	 variableValue("a"),
	 variableValue("b"),
	 '*'
	 );
   std::string var("c");
   llvm::Value* ifBlockStatement = assignmentStatement(var, aTimesB);
   TheBuilder.CreateBr(contBlock);

   /* Else block */
   currFn->getBasicBlockList().push_back(elseBlock);
   TheBuilder.SetInsertPoint(elseBlock);
   llvm::Value* aPlusB = binaryOperation(
	 variableValue("a"),
	 variableValue("b"),
	 '+'
	 );
   llvm::Value* elseBlockStatement = assignmentStatement(var, aPlusB);
   TheBuilder.CreateBr(contBlock);

   currFn->getBasicBlockList().push_back(contBlock);
   TheBuilder.SetInsertPoint(contBlock);

   return contBlock;
}


void generateObjCode(const std::string& filename) {
   std::string targetTriple = llvm::sys::getDefaultTargetTriple();

   llvm::InitializeAllTargetInfos();
   llvm::InitializeAllTargets();
   llvm::InitializeAllTargetMCs();
   llvm::InitializeAllAsmParsers();
   llvm::InitializeAllAsmPrinters();

   std::string error;
   const llvm::Target* target =
      llvm::TargetRegistry::lookupTarget(targetTriple, error);
   if (!target) {
      std::cerr << error << std::endl;
   } else {
      std::string cpu = "generic";
      std::string features = "";
      llvm::TargetOptions options;
      llvm::TargetMachine* targetMachine =
	 target->createTargetMachine(targetTriple, cpu, features,
	       options, llvm::Optional<llvm::Reloc::Model>());

      TheModule->setDataLayout(targetMachine->createDataLayout());
      TheModule->setTargetTriple(targetTriple);

      std::error_code ec;
      llvm::raw_fd_ostream file(filename, ec, llvm::sys::fs::F_None);
      if (ec) {
	 std::cerr << "Could not open output file: " << ec.message() << std::endl;
      } else {
	 llvm::TargetMachine::CodeGenFileType type = llvm::TargetMachine::CGFT_ObjectFile;
	 llvm::legacy::PassManager pm;
	 if (targetMachine->addPassesToEmitFile(pm, file, NULL, type)) {
	    std::cerr << "Unable to emit target code" << std::endl;
	 } else {
	    pm.run(*TheModule);
	    file.close();
	 }
      }
   }
}


void doOptimizations(llvm::Function* fn) {
   llvm::legacy::FunctionPassManager* fpm =
      new llvm::legacy::FunctionPassManager(TheModule);

   fpm->add(llvm::createPromoteMemoryToRegisterPass());
   // fpm->add(llvm::createInstructionCombiningPass());
   fpm->add(llvm::createReassociatePass());
   fpm->add(llvm::createGVNPass());
   fpm->add(llvm::createCFGSimplificationPass());

   fpm->run(*fn);
}
