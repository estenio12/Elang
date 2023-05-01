#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::ArgumentListSingleValue(token_list list)
{
    const int MAX_TOKEN_WAIT = 1;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    return this->CheckValue(list);
}

bool SyntaxPatternMatch::ArgumentListMultiValue(token_list list)
{
    const int MAX_TOKEN_WAIT = 1;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind;

    for(auto item : list)
    {
        bind.push_back(this->CheckValue(list));
    }

    return this->ValidateMatch(bind);
}