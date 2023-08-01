#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateCallFunction(AstNode* node)
{  
   return this->VisitorExpression(node);
}


