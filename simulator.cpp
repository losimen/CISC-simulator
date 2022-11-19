//
// Created by Павло Коваль on 16.11.2022.
//

#include "simulator.h"

using namespace Info;


Simulator::Simulator(const std::vector<std::string> &fileContent)
{
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

    for (auto &reg: state.registers)
    {
        reg = 0;
    }
}


void Simulator::run()
{
    while (true)
    {
        std::bitset<24> num(state.mem[state.pc.to_uint()].to_uint());

        unsigned int opcode = state.mem[state.pc.to_uint()].to_uint() >> SHIFT_OP;
        unsigned int arg0 = (state.mem[state.pc.to_uint()].to_uint() >> SHIFT_ARG0) & 0x7;
        unsigned int arg1 = (state.mem[state.pc.to_uint()].to_uint() >> SHIFT_ARG1) & 0x7;
        unsigned int arg2 = state.mem[state.pc.to_uint()].to_uint() & 0x7;
        unsigned int addressField = state.mem[state.pc.to_uint()].to_uint() & 0xFFF;

        std::cout << num << "| "
                  << "addr: " << state.pc.to_uint()
                  << "| OP: " << opcode
                  << "| ARG0: " << arg0
                  << "| ARG1: " << arg1
                  << "| ARG2: " << arg2
                  << "| Adr: " << addressField
                  << " [" << state.mem[state.pc.to_uint()].to_uint() << "] "
                  << std::endl;

        if (opcodes[ADD] == opcode)
        {
//            std::cout << "ADD " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            state.registers[arg2] = state.registers[arg0].to_int() + state.registers[arg1].to_int();
        }
        else if (opcodes[NAND] == opcode)
        {
//            std::cout << "NAND " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            state.registers[arg2] = ~(state.registers[arg0].to_uint() & state.registers[arg1].to_uint());
        }
        else if (opcodes[LW] == opcode)
        {
//            std::cout << "LW " << arg0 << " " << arg1 << " " << arg2 << std::endl;
            if (state.registers[arg0].to_int() + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.registers[arg1] = state.mem[state.registers[arg0].to_uint() + addressField];
        }
        else if (opcodes[SW] == opcode)
        {
//            std::cout << "SW " << arg0 << " " << arg1 << " " << addressField << std::endl;
            if (state.registers[arg0].to_uint() + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.mem[state.registers[arg0].to_uint() + addressField] = state.registers[arg1];
        }
        else if (opcodes[BEQ] == opcode)
        {
//            std::cout << "BEQ " << arg0 << " " << arg1 << " " << addressField << std::endl;
            if (state.registers[arg0].to_uint() == state.registers[arg1].to_uint())
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
            throw std::runtime_error("Unknown opcode at address " + std::to_string(state.pc.to_uint()));
        }

        state.pc = state.pc.to_uint() + 1;
        state.registers[0] = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    unsigned int regc = 0;
    for (auto reg: state.registers)
        std::cout << regc++ << " " << reg.to_int() << std::endl;
}
