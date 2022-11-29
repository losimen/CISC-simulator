#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"
#include "simulator.h"


bool asol(const std::string &inputProgram)
{
    SyntaxAnalyzer syntaxAnalyzer;
    CodeGenerator codeGenerator;

    try
    {
        FileWorker fileWorkerIn(inputProgram);
        FileWorker fileWorkerOut("output.txt");

        FileContent fileContent = fileWorkerIn.read();
        Commands commands;

        commands = syntaxAnalyzer.analyzeCode(fileContent);
        codeGenerator.generate(fileWorkerOut, commands);
        return true;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
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


int main(int argc, char** argv)
{
    std::string inputProgram;

    if (argc == 1)
    {
        std::cout << "Enter program name: ";
        std::cin >> inputProgram;
    }
    else
    {
        inputProgram = argv[1];
    }

    bool isGenerated = asol(inputProgram);
    if (isGenerated)
    {
        ssol();
    }

    return 0;
}
