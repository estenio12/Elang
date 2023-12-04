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
    
    this->symbolTable->InsertFunctionIdentifier(this->LoadcharToStr());
    this->symbolTable->InsertFunctionIdentifier(this->LoadcharToInt());

    this->symbolTable->InsertFunctionIdentifier(this->Loadsyscmd());
    this->symbolTable->InsertFunctionIdentifier(this->Loadprint());
    this->symbolTable->InsertFunctionIdentifier(this->LoadreadLine());
    this->symbolTable->InsertFunctionIdentifier(this->LoadreadKey());
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

FunctionIdenfierModel* Parser::LoadcharToStr()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_CHAR;

    elang_lib_fun->name = "charToStr";
    elang_lib_fun->type = TYPE::T_STRING;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadcharToInt()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_CHAR;

    elang_lib_fun->name = "charToInt";
    elang_lib_fun->type = TYPE::T_INT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::Loadsyscmd()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_STRING;

    elang_lib_fun->name = "syscmd";
    elang_lib_fun->type = TYPE::T_INT;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::Loadprint()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();
    auto param  = new ParameterDeclaration();
    param->name = "__elang_param";
    param->type = TYPE::T_STRING;

    elang_lib_fun->name = "print";
    elang_lib_fun->type = TYPE::T_VOID;
    elang_lib_fun->parameterList.push_back(param);

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadreadLine()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();

    elang_lib_fun->name = "readLine";
    elang_lib_fun->type = TYPE::T_STRING;

    return elang_lib_fun;
}

FunctionIdenfierModel* Parser::LoadreadKey()
{   
    auto elang_lib_fun = new FunctionIdenfierModel();

    elang_lib_fun->name = "readKey";
    elang_lib_fun->type = TYPE::T_CHAR;

    return elang_lib_fun;
}
























