#include "../headers/parser.hpp"

void Parser::LoadElangLibrary()
{
    this->symbolTable->InsertFunctionIdentifier(this->LoadfloatToInt());
    this->symbolTable->InsertFunctionIdentifier(this->LoadstrToInt());
    this->symbolTable->InsertFunctionIdentifier(this->LoadstrToFloat());
    this->symbolTable->InsertFunctionIdentifier(this->LoadstrToBool());
    
    this->symbolTable->InsertFunctionIdentifier(this->LoadfloatToStr());
    this->symbolTable->InsertFunctionIdentifier(this->LoadintToStr());
    this->symbolTable->InsertFunctionIdentifier(this->LoadboolToStr());
    this->symbolTable->InsertFunctionIdentifier(this->LoadintToFloat());
}

FunctionIdenfierModel* Parser::LoadfloatToInt()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_FLOAT;

    elang_lib_fun->name = "floatToInt";
    elang_lib_fun->type = TYPE::T_INT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadstrToInt()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_STRING;

    elang_lib_fun->name = "strToInt";
    elang_lib_fun->type = TYPE::T_INT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadstrToFloat()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_STRING;

    elang_lib_fun->name = "strToFloat";
    elang_lib_fun->type = TYPE::T_FLOAT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadstrToBool()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_STRING;

    elang_lib_fun->name = "strToBool";
    elang_lib_fun->type = TYPE::T_BOOL;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadfloatToStr()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_FLOAT;

    elang_lib_fun->name = "floatToStr";
    elang_lib_fun->type = TYPE::T_STRING;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadintToStr()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_INT;

    elang_lib_fun->name = "intToStr";
    elang_lib_fun->type = TYPE::T_STRING;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadboolToStr()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_BOOL;

    elang_lib_fun->name = "boolToStr";
    elang_lib_fun->type = TYPE::T_STRING;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadintToFloat()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_INT;

    elang_lib_fun->name = "intToFloat";
    elang_lib_fun->type = TYPE::T_FLOAT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}









