#include <iostream>
#include <bitset>


#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"


int main()
{
//    SyntaxAnalyzer syntaxAnalyzer;
//    CodeGenerator codeGenerator;
//
//    FileWorker fileWorkerIn("example.txt");
//    FileWorker fileWorkerOut("output.txt");
//
//    FileContent fileContent = fileWorkerIn.read();
//
//    Commands commands;
//    std::vector<std::string> labels;
//
//    try
//    {
//        commands = syntaxAnalyzer.analyzeCode(fileContent);
//        codeGenerator.generate(fileWorkerOut, commands);
//    }
//    catch (std::exception &e)
//    {
//        std::cerr << e.what() << std::endl;
//    }

    FileWorker fileWorker("output.txt");

    FileContent fileContent = fileWorker.read();

    unsigned int lineCounter = 0;
    for (auto &line: fileContent)
    {
        int machineCode = std::stoi(line);
        std::bitset<24> num(machineCode);

        unsigned int opcode = machineCode >> SHIFT_OP;
        unsigned int arg0 = (machineCode >> SHIFT_ARG0) & 0x7;
        unsigned int arg1 = (machineCode >> SHIFT_ARG1) & 0x7;
        unsigned int arg2 = machineCode & 0x7;
        unsigned int addressField = machineCode & 0xFFF;

        std::cout << num << "| "
                  << "line: " << ++lineCounter
                  << "| OP: " << opcode
                  << "| ARG0: " << arg0
                  << "| ARG1: " << arg1
                  << "| ARg2: " << arg2
                  << "| Adr: " << addressField << std::endl;
    }

    return 0;
}
