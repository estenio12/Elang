#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::LogicalExpression(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a value
    bind[0] = this->CheckValue(list);

    // # STEP 2: Expected a identifier
    bind[1] = 
    (
        LOGICAL::OR      == list[1] || 
        LOGICAL::AND     == list[1] || 
        LOGICAL::NAND    == list[1] || 
        LOGICAL::XOR     == list[1] || 
        LOGICAL::DIFF    == list[1] || 
        LOGICAL::EQUALS  == list[1] || 
        LOGICAL::GREAT   == list[1] || 
        LOGICAL::LESS    == list[1] || 
        LOGICAL::GREATEQ == list[1] || 
        LOGICAL::LESSEQ  == list[1] 
    );

    // # STEP 3: Expected a value
    bind[2] = this->CheckValue(list);

    return this->ValidateMatch(bind);
}