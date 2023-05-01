#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::MultiplicativeExpression(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a digit | identifier | call function
    bind[0] = 
    (
        Checker::IsDigit(list[0])           ||
        Checker::IsValidIdentifier(list[0]) ||
        this->CheckCallFunction(list)
    );

    // # STEP 2: Expected a operator * | /
    bind[1] = 
    (
        list[1] == OPERATOR::MULTIPLY || 
        list[1] == OPERATOR::DIVIDE
    );

    // # STEP 3: Expected a digit | identifier | call function
    bind[2] = 
    (
        Checker::IsDigit(list[2])           ||
        Checker::IsValidIdentifier(list[2]) ||
        this->CheckCallFunction(list)
    );

    return this->ValidateMatch(bind);
}