//
// Created by Павло Коваль on 15.11.2022.
//

#include "commands.h"

unsigned int Commands::getLabelAddress(const std::string &label) const
{
    for (auto &command: commands)
    {
        if (command.label == label)
        {
            return command.address;
        }
    }

    throw SyntaxError("Label not found " + label);
}


void Commands::push_back(const Command &command)
{
    commands.push_back(command);
}

void Commands::clear()
{
    commands.clear();
}


unsigned int Commands::size() const
{
    return commands.size();
}

Command Commands::operator[](unsigned int index) const
{
    return commands[index];
}
