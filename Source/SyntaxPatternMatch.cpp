#include "../Include/SyntaxPatternMatch.hpp"

SyntaxPatternMatch::SyntaxPatternMatch(){}
SyntaxPatternMatch::~SyntaxPatternMatch(){}

bool SyntaxPatternMatch::MatchVariableDeclaration(token_list buildPattern)
{
    if(this->VariableDeclarationOnlyDeclaration(buildPattern)) return true;

    return false;
}

bool SyntaxPatternMatch::ValidateMatch(std::vector<bool> matches)
{
    for(bool result : matches) if(!result) return false;
    return true;
}
















