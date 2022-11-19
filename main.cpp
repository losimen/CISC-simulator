#include <iostream>
#include <stack>

#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"
#include "simulator.h"


void asol()
{
    SyntaxAnalyzer syntaxAnalyzer;
    CodeGenerator codeGenerator;

    FileWorker fileWorkerIn("example_programs/or_OR_pure.txt");
    FileWorker fileWorkerOut("output.txt");

    FileContent fileContent = fileWorkerIn.read();
    Commands commands;

    try
    {
        commands = syntaxAnalyzer.analyzeCode(fileContent);
        codeGenerator.generate(fileWorkerOut, commands);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}


void ssol()
{
    FileWorker fileWorker("output.txt");
    FileContent fileContent = fileWorker.read();
    Simulator simulator(fileContent);

    try
    {
        simulator.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}


int main()
{
    asol();
    ssol();

    return 0;
}
