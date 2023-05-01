#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::CallFunctionNoArgumentList(token_list list)
{
    const int MAX_TOKEN_WAIT = 4;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false};

    // # STEP 1: Expected a type specifier
    bind[0] = Checker::IsValidIdentifier(list[0]);

    // # STEP 2: Expected a open parameter
    bind[1] = Checker::IsOpenParam(list[1]);
    
    // # STEP 3: Expected a close parameter
    bind[2] = Checker::IsCloseParam(list[2]);

    // # STEP 4: Expected a EOL character
    bind[3] = Checker::IsEOLCharacter(list[3]);

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::CallFunctionWithArgumentList(token_list list)
{
    const int MAX_TOKEN_WAIT = 4;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false};

    // # STEP 1: Expected a type specifier
    bind[0] = Checker::IsValidIdentifier(list[0]);

    // # STEP 2: Expected a open parameter
    bind[1] = Checker::IsOpenParam(list[1]);

    // # STEP 3: Expected a argument list
    bind[2] = this->CheckArgumentList
    (
        Tools::ExtractArgumentListFromCallFunction(list)
    );
    
    // # STEP 4: Expected a close parameter
    bind[3] = Checker::IsCloseParam(list[3]);

    // # STEP 5: Expected a EOL character
    bind[4] = Checker::IsEOLCharacter(list[4]);

    return this->ValidateMatch(bind);
}