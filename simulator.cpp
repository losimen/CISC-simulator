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
    unsigned int amountOfInstructions = 0;
    while (true)
    {
        opcode = state.mem[state.pc.to_uint()].to_uint() >> SHIFT_OP;
        arg0 = (state.mem[state.pc.to_uint()].to_uint() >> SHIFT_ARG0) & 0x7;
        arg1 = (state.mem[state.pc.to_uint()].to_uint() >> SHIFT_ARG1) & 0x7;
        arg2 = state.mem[state.pc.to_uint()].to_uint() & 0x7;
        addressField = state.mem[state.pc.to_uint()].to_uint() & 0xFFF;

        std::cout << "addr: " << state.pc.to_uint()
                  << "| OP: " << opcode
                  << "| ARG0: " << arg0
                  << "| ARG1: " << arg1
                  << "| ARG2: " << arg2
                  << "| Adr: " << addressField
                  << " [" << state.mem[state.pc.to_uint()].to_uint() << "] "
                  << std::endl;

        if (opcodes[ADD] == opcode)
        {
            doRInstruction([](int a, int b) { return a + b; });
            state.CF = true;
        }
        else if (opcodes[NAND] == opcode)
        {
            doRInstruction([](int a, int b) { return ~(a & b); });
        }
        else if (opcodes[LW] == opcode)
        {
            if (state.registers[arg0].to_int() + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.registers[arg1] = state.mem[state.registers[arg0].to_uint() + addressField];
        }
        else if (opcodes[SW] == opcode)
        {
            if (state.registers[arg0].to_uint() + addressField >= MAX_WORDS)
            {
                throw std::runtime_error("Exceed memory size");
            }

            state.mem[state.registers[arg0].to_uint() + addressField] = state.registers[arg1];
        }
        else if (opcodes[BEQ] == opcode)
        {
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
            break;
        }
        else if (opcodes[NOOP] == opcode)
        {
            // NOTHING
        }
        else if (opcodes[DEC] == opcode)
        {
            if (arg0 == 0)
            {
                state.stack.push(state.stack.top());
            }
            else
            {
                arg2 = arg0;
            }

            doRInstruction([](int a, int) { return a - 1; });
            if (arg0 == 0)
            {
                state.stack.pop();
            }
        }
        else if (opcodes[IDIV] == opcode)
        {
            doRInstruction([](int a, int b) { return a / b; });
        }
        else if (opcodes[XADD] == opcode)
        {
            doRInstruction([](int a, int b) { return a + b; });

            int24_t temp = state.registers[arg0];
            state.registers[arg0] = state.registers[arg1];
            state.registers[arg1] = temp;
        }
        else if (opcodes[SHL] == opcode)
        {
            doRInstruction([](int a, int b) { return a << b; });
        }
        else if (opcodes[OR] == opcode)
        {
            doRInstruction([](int a, int b) { return a | b; });
        }
        else if (opcodes[NEG] == opcode)
        {
            if (arg0 == 0)
            {
                state.stack.push(state.stack.top());
            }
            else
            {
                arg2 = arg0;
            }
            doRInstruction([](int a, int) { return -a; });
            if (arg0 == 0)
            {
                state.stack.pop();
            }
        }
        else if (opcodes[PUSH] == opcode)
        {
            if (state.stack.size() > STACK_SIZE)
            {
                throw MyError(state.pc.to_uint(), "Exceed stack size");
            }

            state.stack.push(arg0);
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
        else if (opcodes[JMA] == opcode)
        {
            if (state.registers[arg0].to_uint() > state.registers[arg1].to_uint())
            {
                state.pc = addressField-1;
            }
        }
        else if (opcodes[JMNE] == opcode)
        {
            if (state.registers[arg0].to_uint() != state.registers[arg1].to_uint())
            {
                state.pc = addressField-1;
            }
        }
        else if (opcodes[ADC] == opcode)
        {
            try
            {
                doRInstruction([this](int a, int b) { return a + b + this->state.CF; });
                state.CF = false;
            }
            catch (std::overflow_error &e)
            {
                state.CF = true;
            }
        }
        else
        {
            throw std::runtime_error("Unknown opcode at address " + std::to_string(state.pc.to_uint()));
        }

        unsigned int regc = 0;
        for (auto reg: state.registers)
            std::cout << "register[" << regc++ << "] " << reg.to_int() << std::endl;

        std::cout << "CF: " << state.CF << std::endl;
        std::cout << "ZF: " << state.ZF << std::endl;
        std::cout << "SF: " << state.SF << std::endl;
        std::cout << std::endl;

        state.pc = state.pc.to_uint() + 1;
        state.registers[0] = 0;
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
        amountOfInstructions++;
    }

    std::cout << "Total amount of instructions: " << amountOfInstructions << std::endl;
}


void Simulator::doRInstruction(std::function<unsigned int(int, int)> func)
{
    if (arg0 == 0)
    {
        state.isStackEmpty();
        arg0 = state.stack.top().to_int();
        state.stack.pop();

        state.isStackEmpty();
        arg1 = state.stack.top().to_int();
        state.stack.pop();

        state.stack.push(func(state.registers[arg0].to_int(), state.registers[arg1].to_int()));

        if (state.stack.top().isOverflow1())
        {
            state.CF = true;
        }
        else
        {
            state.CF = false;
        }
    }
    else
    {
        state.registers[arg2] = func(state.registers[arg0].to_int(), state.registers[arg1].to_int());
        if (state.registers[arg2].isOverflow1())
        {
            state.CF = true;
        }
        else
        {
            state.CF = false;
        }
    }
}


void Simulator::StateStruct::isStackEmpty() const
{
    if (stack.empty())
    {
        throw MyError(pc.to_uint(), "Stack is empty");
    }
}
