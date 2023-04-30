#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::VariableDeclarationOnlyDeclaration(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a type specifier
    bind[0] = Checker::IsValidType(list[0]);

    // # STEP 2: Expected a identifier
    bind[1] = Checker::IsValidIdentifier(list[1]);

    // # STEP 3: Expected a EOL character
    bind[2] = Checker::IsEOLCharacter(list[2]);

    return this->ValidateMatch(bind);
}