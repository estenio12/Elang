#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::JumpStatementReturn(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a type specifier
    bind[0] = KEYWORDS::RETURN == list[0];

    // # STEP 2: Expected a value
    bind[1] = this->CheckValue(list);

    // # STEP 3: Expected a EOL character
    bind[2] = Checker::IsEOLCharacter(list[2]);

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::JumpStatementBreak(token_list list)
{
    const int MAX_TOKEN_WAIT = 2;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false };

    // # STEP 1: Expected a type specifier
    bind[0] = KEYWORDS::BREAK == list[0];

    // # STEP 2: Expected a EOL character
    bind[1] = Checker::IsEOLCharacter(list[1]);

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::JumpStatementContinue(token_list list)
{
    const int MAX_TOKEN_WAIT = 2;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false };

    // # STEP 1: Expected a type specifier
    bind[0] = KEYWORDS::CONTINUE == list[0];

    // # STEP 2: Expected a EOL character
    bind[1] = Checker::IsEOLCharacter(list[1]);

    return this->ValidateMatch(bind);
}

