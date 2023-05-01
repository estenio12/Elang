#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::SystemCallWrite(token_list list)
{
    const int MAX_TOKEN_WAIT = 5;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false, false };

    // # STEP 1: Expected a keyword syswrite 
    bind[0] = KEYWORDS::SYSWRITE == list[0];

    // # STEP 2: Expected a open parenthese
    bind[1] = Checker::IsOpenParam(list[1]);

    // # STEP 3: Expected a string
    bind[2] = Checker::IsValidWorld(list[2]);

    // # STEP 4: Expected a close parenthese
    bind[3] = Checker::IsCloseParam(list[3]);

    // # STEP 4: Expected a EOL Character
    bind[4] = Checker::IsEOLCharacter(list[4]);

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::SystemCallRead(token_list list)
{
    const int MAX_TOKEN_WAIT = 4;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false };

    // # STEP 1: Expected a keyword syswrite 
    bind[0] = KEYWORDS::SYSREAD == list[0];

    // # STEP 2: Expected a open parenthese
    bind[1] = Checker::IsOpenParam(list[1]);

    // # STEP 4: Expected a close parenthese
    bind[2] = Checker::IsCloseParam(list[2]);

    // # STEP 4: Expected a EOL Character
    bind[3] = Checker::IsEOLCharacter(list[3]);

    return this->ValidateMatch(bind);
}

