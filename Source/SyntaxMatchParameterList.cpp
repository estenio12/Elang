#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::ParameterListSingleParamenter(token_list list)
{
    const int MAX_TOKEN_WAIT = 2;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a type specifier
    bind[0] = Checker::IsValidType(list[0]);

    // # STEP 2: Expected a identifier
    bind[1] = Checker::IsValidIdentifier(list[1]);

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::ParameterListMultiParamenter(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;
    if(list[0] == DELIMITERS::COMMA) return false;

    std::vector<bool> bind;
    
    const uint8_t EMPTY = 0;
    const uint8_t TYPE  = 1;
    const uint8_t ID    = 2;
    const uint8_t COMMA = 3;
    uint8_t historic = EMPTY;

    for(auto token : list)
    {
        switch(historic)
        {
            case EMPTY:
            case COMMA:
                bind.push_back(Checker::IsValidType(token));
                historic = 1;
            break;

            case TYPE:
                bind.push_back(Checker::IsValidIdentifier(token));
                historic = ID;
            break;

            case ID:
                bind.push_back(DELIMITERS::COMMA == token);
                historic = COMMA;
            break;
        }
    }

    return this->ValidateMatch(bind);
}

