#include <iostream>

#include "fileworker.h"
#include "syntaxanalyzer.h"

int main() {
    FileWorker fileWorker("example.txt");
    FileContent fileContent = fileWorker.read();

    Commands commands;
    std::vector<std::string> labels;

    SyntaxAnalyzer syntaxAnalyzer;

    try
    {
        commands = syntaxAnalyzer.analyzeCode(fileContent);
        labels = syntaxAnalyzer.getLabels();

        for (auto &label: labels)
        {
            std::cout << label << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
