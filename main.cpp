#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"

int main() {
    FileWorker fileWorker("example.txt");
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer;

    unsigned long lineCounter = 1;
    for (auto &line : fileContent)
    {
        try
        {
            Command code = syntaxAnalyzer.analyzeCode(line);
            lineCounter++;
        }
        catch (std::exception &e)
        {
            std::cerr << "Error in line " << lineCounter << ": " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
