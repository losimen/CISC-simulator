//
// Created by Павло Коваль on 15.11.2022.
//

#ifndef KURSOVAAK_COMMANDS_H
#define KURSOVAAK_COMMANDS_H

#include <vector>

#include "command.h"
#include "myerror.h"


class Commands
{
private:
    std::vector<Command> commands;

public:
    void push_back(const Command &command);
    void clear();
    unsigned int size() const;

    unsigned int getLabelAddress(const std::string &label) const;
    Command operator[](unsigned int index) const;
};


#endif //KURSOVAAK_COMMANDS_H
