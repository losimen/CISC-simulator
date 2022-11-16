#include <iostream>
#include <bitset>

#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"
#include "simulator.h"


void asol()
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
}


void ssol()
{
    using namespace Info;
    FileWorker fileWorker("output.txt");
    FileContent fileContent = fileWorker.read();
    Simulator simulator(fileContent);

    simulator.run();
}



int main()
{
    asol();
    ssol();

    return 0;
}
