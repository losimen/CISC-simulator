//
// Created by Павло Коваль on 15.11.2022.
//

#include "codegenerator.h"


using namespace std;
using namespace Info;


void CodeGenerator::generate(const FileWorker &fileWorker, const Commands &commands)
{
    const unsigned int commandsLength = commands.size();
    int24_t machineCode;

    fileWorker.clear();

    for (unsigned int it = 0; it < commandsLength; it++)
    {
        machineCode = getCode(commands[it], commands).to_uint();
        fileWorker.write(std::to_string(machineCode.to_uint()) + '\n');
    }
}


int24_t CodeGenerator::getCode(const Command &command, const Commands &commands)
{
    int24_t machineCode;

    if (command.opcode == ADD || command.opcode == NAND || command.opcode == JALR ||
        command.opcode == IDIV || command.opcode == XADD || command.opcode == SHL ||
        command.opcode == OR)
    {
        if (!is_number(command.arg0))
        {
            machineCode = (opcodes[command.opcode] << SHIFT_OP);
        }
        else
        {
            machineCode = (opcodes[command.opcode] << SHIFT_OP) |
                          (stoi(command.arg0) << SHIFT_ARG0) |
                          (stoi(command.arg1) << SHIFT_ARG1) |
                          stoi(command.arg2);
        }

    }
    else if (command.opcode == NOOP || command.opcode == HALT)
    {
        machineCode = (opcodes[command.opcode] << SHIFT_OP);
    }
    else if (command.opcode == LW || command.opcode == SW || command.opcode == BEQ)
    {
        unsigned int addressField = commands.getLabelAddress(command.arg2);

        machineCode = (opcodes[command.opcode] << SHIFT_OP) |
                      (stoi(command.arg0) << SHIFT_ARG0) |
                      (stoi(command.arg1) << SHIFT_ARG1) |
                      addressField;
    }
    else if (command.opcode == PUSH || command.opcode == POP || command.opcode == DEC)
    {
        machineCode = (opcodes[command.opcode] << SHIFT_OP) |
                      (stoi(command.arg0) << SHIFT_ARG0);
    }
    else if (command.opcode == FILL)
    {
        machineCode = stoi(command.arg0);
    }
    else
    {
        throw std::runtime_error("Unknown opcode");
    }

    return machineCode;
}
