#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"

#include <bitset>

#define SHIFT_OP 21
#define SHIFT_ARG0 18
#define SHIFT_ARG1 15


int main() {
    SyntaxAnalyzer syntaxAnalyzer;
    FileWorker fileWorker("example.txt");
    FileContent fileContent = fileWorker.read();

    Commands commands;
    std::vector<std::string> labels;

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
