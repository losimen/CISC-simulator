//
// Created by Павло Коваль on 16.11.2022.
//

#include "simulator.h"

using namespace Info;


Simulator::Simulator(const std::vector<std::string> &fileContent)
{
    for (auto &line: fileContent)
    {
        if (state.numMemory.to_uint() >= MAX_WORDS)
        {
            throw std::runtime_error("Exceed memory size");
        }

        state.mem[state.numMemory.to_uint()] = std::stoi(line);
        state.numMemory = state.numMemory.to_uint() + 1;
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
            if (arg0 == 0 && arg1 == 0 && arg2 == 0)
            {
                // TODO: move to functions
                state.isStackEmpty();
                arg0 = state.stack.top().to_int();
                state.stack.pop();

                state.isStackEmpty();
                arg1 = state.stack.top().to_int();
                state.stack.pop();

                state.stack.push(arg0 + arg1);
            }
            else
            {
                state.registers[arg2] = state.registers[arg0].to_int() + state.registers[arg1].to_int();
            }
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
        else if (opcodes[NOOP] == opcode)
        {
            // std::cout << "NOOP" << std::endl;
        }
        else if (opcodes[PUSH] == opcode)
        {
            if (state.stack.size() > STACK_SIZE)
            {
                throw MyError(state.pc.to_uint(), "Exceed stack size");
            }

            state.stack.push(state.registers[arg0]);
        }
        else if (opcodes[POP] == opcode)
        {
            if (state.stack.empty())
            {
                throw MyError(state.pc.to_uint(), "Stack is empty");
            }

            state.registers[arg0] = state.stack.top();
            state.stack.pop();
        }
        else
        {
            throw std::runtime_error("Unknown opcode at address " + std::to_string(state.pc.to_uint()));
        }

        state.pc = state.pc.to_uint() + 1;
        state.registers[0] = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }


    unsigned int regc = 0;
    for (auto reg: state.registers)
        std::cout << regc++ << " " << reg.to_int() << std::endl;
}

void Simulator::doRInstruction(unsigned int arg0, unsigned int arg1, unsigned int arg2,
                               std::function<unsigned int(unsigned int, unsigned int, unsigned int)> func)
{
    if (arg0 == 0 && arg1 == 0 && arg2 == 0)
    {
        state.isStackEmpty();
        arg0 = state.stack.top().to_int();
        state.stack.pop();

        state.isStackEmpty();
        arg1 = state.stack.top().to_int();
        state.stack.pop();

        state.stack.push(func(arg0, arg1, arg2));
    }
    else
    {
        state.registers[arg2] = state.registers[arg0].to_int() + state.registers[arg1].to_int();
    }
}


void Simulator::StateStruct::isStackEmpty() const
{
    if (stack.empty())
    {
        throw MyError(pc.to_uint(), "Stack is empty");
    }
}
