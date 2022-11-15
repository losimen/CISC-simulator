#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"


int main()
{
    SyntaxAnalyzer syntaxAnalyzer;
    CodeGenerator codeGenerator;

    FileWorker fileWorkerIn("example.txt");
    FileWorker fileWorkerOut("output.txt");

    FileContent fileContent = fileWorkerIn.read();

    Commands commands;
    std::vector<std::string> labels;

    try
    {
        commands = syntaxAnalyzer.analyzeCode(fileContent);
        codeGenerator.generate(fileWorkerOut, commands);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
