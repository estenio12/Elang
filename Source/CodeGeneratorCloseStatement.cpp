#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateCloseStatement(AstNode* node)
{
    return TARGET_CODE::T_CLOSE_BRACE;
}