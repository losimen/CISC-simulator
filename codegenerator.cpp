//
// Created by Павло Коваль on 15.11.2022.
//

#include "codegenerator.h"
#include <iostream>

using namespace std;
using namespace Info;


void CodeGenerator::generate(const FileWorker &fileWorker, const Commands &commands)
{
    const unsigned int commandsLength = commands.size();
    unsigned int machineCode;

    fileWorker.clear();

    for (unsigned int it = 0; it < commandsLength; it++)
    {
        machineCode = _getCode(commands[it], commands);
        fileWorker.write(std::to_string(machineCode) + '\n');
    }
}


unsigned int CodeGenerator::_getCode(const Command &command, const Commands &commands)
{
    unsigned int machineCode = 0;

    if (command.opcode == ADD || command.opcode == NAND || command.opcode == JALR)
    {
        machineCode = (opcodes[command.opcode] << SHIFT_OP) |
                       (stoi(command.arg0) << SHIFT_ARG0) |
                       (stoi(command.arg1) << SHIFT_ARG1) |
                        stoi(command.arg2);
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
    else if (command.opcode == FILL)
    {
        machineCode = stoi(command.arg0);
    }

    return machineCode;
}
