#include <iostream>
#include <bitset>


#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"


struct StateStruct
{
    int pc = 0;
    std::array<int, MAX_WORDS> mem;
    std::array<int, AMOUNT_OF_REGISTERS> registers;
    int numMemory = 0;
} state;


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

    unsigned int lineCounter = 0;
    for (auto &line: fileContent)
    {
        // TODO: check whether only integers
        if (state.numMemory >= MAX_WORDS)
        {
            throw std::runtime_error("Exceed memory size");
        }

        state.mem[state.numMemory] = std::stoi(line);
        state.numMemory++;
    }


    for (unsigned int it = 0; it < state.numMemory; it++) {
        std::bitset<24> num(state.mem[it]);

        unsigned int opcode = state.mem[it] >> SHIFT_OP;
        unsigned int arg0 = (state.mem[it] >> SHIFT_ARG0) & 0x7;
        unsigned int arg1 = (state.mem[it] >> SHIFT_ARG1) & 0x7;
        unsigned int arg2 = state.mem[it] & 0x7;
        unsigned int addressField = state.mem[it] & 0xFFF;

//        std::cout << num << "| "
//                  << "addr: " << lineCounter++
//                  << "| OP: " << opcode
//                  << "| ARG0: " << arg0
//                  << "| ARG1: " << arg1
//                  << "| ARG2: " << arg2
//                  << "| Adr: " << addressField
//                  << " [" << state.mem[it] << "] "
//                  << std::endl;

        if (opcodes[ADD] == opcode)
        {
            std::cout << "ADD: " << arg2 << " = " << arg0 << " + " << arg1 << std::endl;
            std::cout << "ADD: " << state.registers[arg2] << " = " << state.registers[arg0] << " + " << state.registers[arg1] << std::endl << std::endl;
            state.registers[arg2] = state.registers[arg0] + state.registers[arg1];
        }
        else if (opcodes[LW] == opcode)
        {
            state.registers[arg1] = state.mem[state.registers[arg0] + addressField];
        }
        else if (opcodes[HALT] == opcode)
        {
            break;
        }

    }

    int regc = 0;
    for (auto reg: state.registers)
        std::cout << regc++ << " " << reg << std::endl;

}



int main()
{
    //asol();
    ssol();

    return 0;
}
