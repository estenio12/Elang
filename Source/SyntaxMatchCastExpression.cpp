#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::CastExpression(token_list list)
{
    const int MAX_TOKEN_WAIT = 4;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false };

    // # STEP 1: Expected a open parentheses
    bind[0] = DELIMITERS::OPEN_PARAM == list[0];

    // # STEP 2: Expected a identifier
    bind[1] = Checker::IsValidType(list[1]);

    // # STEP 3: Expected a close parentheses
    bind[2] = DELIMITERS::CLOSE_PARAM == list[2];

    // # STEP 4: Expected a value
    bind[3] = this->CheckValue(list);

    return this->ValidateMatch(bind);
}