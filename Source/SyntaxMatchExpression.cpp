#include "../Include/SyntaxPatternMatch.hpp"

bool SyntaxPatternMatch::ExpressionAdditive(token_list list)
{
    const int MAX_TOKEN_WAIT = 1;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    return this->AdditiveExpression(list);
}

bool SyntaxPatternMatch::ExpressionMultiplicative(token_list list)
{
    const int MAX_TOKEN_WAIT = 1;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    return this->MultiplicativeExpression(list);
}

bool SyntaxPatternMatch::ExpressionOperation(token_list list)
{
    const int MAX_TOKEN_WAIT = 3;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false };

    // # STEP 1: Expected a additive | multiplicative
    bind[0] = 
    (
        this->AdditiveExpression(list)       ||
        this->MultiplicativeExpression(list)
    );

    // # STEP 2: Expected a operator + | - | * | /
    bind[1] = 
    (
        list[1] == OPERATOR::PLUS     || 
        list[1] == OPERATOR::SUBTRACT ||
        list[1] == OPERATOR::MULTIPLY ||
        list[1] == OPERATOR::DIVIDE
    );

    // # STEP 3: Expected a additive | multiplicative
    bind[2] = 
    (
        this->AdditiveExpression(list)       ||
        this->MultiplicativeExpression(list)
    );

    return this->ValidateMatch(bind);
}

bool SyntaxPatternMatch::ExpressionOperationScoped(token_list list)
{
    const int MAX_TOKEN_WAIT = 5;
    if(list.size() > MAX_TOKEN_WAIT || list.size() < MAX_TOKEN_WAIT) return false;

    std::vector<bool> bind { false, false, false, false, false };

    // # STEP 1: Expected a open parenthese
    bind[0] = Checker::IsOpenParam(list[0]);

    // # STEP 2: Expected a additive | multiplicative
    bind[1] = 
    (
        this->AdditiveExpression(list)       ||
        this->MultiplicativeExpression(list)
    );

    // # STEP 3: Expected a operator + | - | * | /
    bind[2] = 
    (
        list[2] == OPERATOR::PLUS     || 
        list[2] == OPERATOR::SUBTRACT ||
        list[2] == OPERATOR::MULTIPLY ||
        list[2] == OPERATOR::DIVIDE
    );

    // # STEP 4: Expected a additive | multiplicative
    bind[3] = 
    (
        this->AdditiveExpression(list)       ||
        this->MultiplicativeExpression(list)
    );

    // # STEP 5: Expected a open parenthese
    bind[4] = Checker::IsOpenParam(list[4]);

    return this->ValidateMatch(bind);
}




