#include "../headers/compiler.hpp"

Compiler::Compiler(std::string sourcePath, std::string outputFileName)
{
    if(IsNotValidPath(sourcePath))
    {
        Output::PrintCustomizeError("Fatal Error: ", "source file not found!");
        exit(EXIT_FAILURE);
    }

    this->symbolTable = new SymbolTable();
    this->ast         = new Ast();
    this->lexer       = new Lexer(sourcePath);
    this->parser      = new Parser(lexer, symbolTable, ast);
    this->codegen     = new CodeGenerator(outputFileName);
}

Compiler::~Compiler()
{
    delete lexer;
}

bool Compiler::IsNotValidPath(std::string sourcePath)
{
    if(sourcePath.empty()) return false;
    return !std::filesystem::exists(std::filesystem::path(sourcePath));
}

void Compiler::Run()
{
    // # Parsing
    auto ast = this->parser->Parse();
    
    // # Output Code
    this->codegen->Run(ast);
}
