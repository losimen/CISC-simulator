#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"

int main() {
    FileWorker fileWorker("test_cases/Label_Correct.txt");
    FileContent fileContent = fileWorker.read();
    std::vector<Command> commands;

    SyntaxAnalyzer syntaxAnalyzer;

    try
    {
        commands = syntaxAnalyzer.analyzeCode(fileContent);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
