//
// Created by Павло Коваль on 14.11.2022.
//

#ifndef KURSOVAAK_COMMAND_H
#define KURSOVAAK_COMMAND_H

#include <string>

struct Command
{
    std::string label;
    std::string opcode;
    std::string arg0;
    std::string arg1;
    std::string arg2;

    Command() = default;
};


#endif //KURSOVAAK_COMMAND_H
