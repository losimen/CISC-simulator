#include <iostream>
#include <bitset>
#include <chrono>
#include <thread>

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

    while (true)
    {
        std::bitset<24> num(state.mem[state.pc]);

        unsigned int opcode = state.mem[state.pc] >> SHIFT_OP;
        unsigned int arg0 = (state.mem[state.pc] >> SHIFT_ARG0) & 0x7;
        unsigned int arg1 = (state.mem[state.pc] >> SHIFT_ARG1) & 0x7;
        unsigned int arg2 = state.mem[state.pc] & 0x7;
        unsigned int addressField = state.mem[state.pc] & 0xFFF;

//        std::cout << num << "| "
//                  << "addr: " << state.pc
//                  << "| OP: " << opcode
//                  << "| ARG0: " << arg0
//                  << "| ARG1: " << arg1
//                  << "| ARG2: " << arg2
//                  << "| Adr: " << addressField
//                  << " [" << state.mem[state.pc] << "] "
//                  << std::endl;

        if (opcodes[ADD] == opcode)
        {
//            std::cout << "ADD " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            state.registers[arg2] = state.registers[arg0] + state.registers[arg1];
        }
        else if (opcodes[NAND] == opcode)
        {
//            std::cout << "NAND " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            state.registers[arg2] = ~(state.registers[arg0] & state.registers[arg1]);
        }
        else if (opcodes[LW] == opcode)
        {
//            std::cout << "LW " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            if (state.registers[arg0] + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.registers[arg1] = state.mem[state.registers[arg0] + addressField];
        }
        else if (opcodes[SW] == opcode)
        {
//            std::cout << "SW " << arg0 << " " << arg1 << " " << addressField << std::endl;
            if (state.registers[arg0] + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.mem[state.registers[arg0] + addressField] = state.registers[arg1];
        }
        else if (opcodes[BEQ] == opcode)
        {
//            std::cout << "BEQ " << arg0 << " " << arg1 << " " << addressField << std::endl;
            if (state.registers[arg0] == state.registers[arg1])
            {
                state.pc = addressField-1;
            }
        }
        else if (opcodes[JALR] == opcode)
        {
            state.registers[arg1] = state.pc;
            if(arg0 != 0)
            {
                state.pc = state.registers[arg0];
            }
            else
            {
                state.pc = 0;
            }
        }
        else if (opcodes[HALT] == opcode)
        {
            // std::cout << "HALT" << std::endl;
            break;
        }
        else if (7 == opcode)
        {
            // std::cout << "NOOP" << std::endl;
        }
        else
        {
            throw std::runtime_error("Unknown opcode at address " + std::to_string(state.pc));
        }

        state.pc++;
        state.registers[0] = 0;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    unsigned int regc = 0;
    for (auto reg: state.registers)
        std::cout << regc++ << " " << reg << std::endl;

}



int main()
{
    asol();
    ssol();

    return 0;
}
