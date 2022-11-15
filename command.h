//
// Created by Павло Коваль on 14.11.2022.
//

#ifndef KURSOVAAK_COMMAND_H
#define KURSOVAAK_COMMAND_H

#include <string>

struct Command
{
    unsigned int address;

    std::string label;
    std::string opcode;
    std::string arg0;
    std::string arg1;
    std::string arg2;

    Command()
    {
        address = 0;
        label = "";
        opcode = "";
        arg0 = "";
        arg1 = "";
        arg2 = "";
    }

    void clear()
    {
        address = 0;

        label.clear();
        opcode.clear();
        arg0.clear();
        arg1.clear();
        arg2.clear();
    }

};


#endif //KURSOVAAK_COMMAND_H
