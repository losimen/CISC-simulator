//
// Created by Павло Коваль on 06.11.2022.
//

#include "syntaxanalyzer.h"

using namespace Info;

const std::vector<std::string> SyntaxAnalyzer::labelAlphabet {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                                                              "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                                                              "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "_", "$"};


SyntaxAnalyzer::SyntaxAnalyzer()
{
    labels = std::vector<std::string>();
}


Commands SyntaxAnalyzer::analyzeCode(std::vector<std::string> fileContent)
{
    Commands commands;

    for (auto &line : fileContent)
    {
        command.clear();
        command.address = commands.size();

        removeDuplicatedSpaces(line);
        parseCode(line);

        if (!command.label.empty())
            checkLabel();

        checkOpcode();
        checkRegister();
        checkAddress();

        commands.push_back(command);
    }

    return commands;
}


void SyntaxAnalyzer::removeDuplicatedSpaces(std::string &line)
{
    std::string::iterator new_end = std::unique(line.begin(), line.end(),
                                                [](char lhs, char rhs)
                                                {
                                                        return (lhs == rhs) && (lhs == ' ');
                                                }
    );
    line.erase(new_end, line.end());
}


void SyntaxAnalyzer::parseCode(std::string line)
{
    if (line[0] != ' ')
    {
        command.label = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
    }
    else
    {
        line = line.substr(line.find(' ') + 1);
    }

    command.opcode = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    command.arg0 = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    command.arg1 = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    command.arg2 = line.substr(0, line.find(' '));

//    std::cout << "LABEL " << command.label << std::endl;
//    std::cout << "OPCODE " << command.opcode << std::endl;
//    std::cout << "ARG0 " << command.arg0 << std::endl;
//    std::cout << "ARG1 " << command.arg1 << std::endl;
//    std::cout << "ARG2 " << command.arg2 << std::endl;
//    std::cout << std::endl;
}


void SyntaxAnalyzer::checkRegister()
{
    if (command.opcode == ADD || command.opcode == NAND ||
        command.opcode == LW || command.opcode == SW ||
        command.opcode == BEQ || command.opcode == JALR)
    {
        checkRegisterArg(command.arg0);
        checkRegisterArg(command.arg1);
    }

    if (command.opcode == ADD || command.opcode == NAND)
    {
        checkRegisterArg(command.arg2);
    }
}


void SyntaxAnalyzer::checkRegisterArg(const std::string &registerName) const
{
    if (!std::isdigit(registerName[0]))
    {
        throw SyntaxError(command.address + 1, "Register name must be digit number");
    }

    if (std::stoi(registerName) < 0 || std::stoi(registerName) > 7)
    {
        throw SyntaxError(command.address + 1, "Register number is out of range");
    }
}


void SyntaxAnalyzer::checkAddress()
{
    if (command.opcode == LW || command.opcode == SW ||
        command.opcode == BEQ)
    {
        checkLabelName(command.arg2);
    }

    if (command.opcode == FILL)
    {
        checkLabelName(command.arg1);
    }
}


void SyntaxAnalyzer::checkOpcode() const
{
    if (opcodes.find(command.opcode) == opcodes.end())
    {
        throw SyntaxError(command.address + 1, "Unknown opcode - " + command.opcode);
    }
}


void SyntaxAnalyzer::checkLabelName(const std::string &labelName) const
{
    if (std::isdigit(labelName[0]))
    {
        throw SyntaxError(command.address + 1, "Label name must not start with digit");
    }

    if (labelName.length() > MAX_LABEL_LENGTH)
    {
        throw SyntaxError(command.address + 1, "Label name is too long");
    }

    for (auto &ch: labelName)
    {
        if (std::find(labelAlphabet.begin(), labelAlphabet.end(), std::string(1, ch)) == labelAlphabet.end())
        {
            throw SyntaxError(command.address + 1, "Label name contains invalid character");
        }
    }
}


void SyntaxAnalyzer::checkLabel()
{
    checkLabelName(command.label);

    if (std::find(labels.begin(), labels.end(), command.label) != labels.end())
    {
        throw SyntaxError(command.address + 1, "Label already exists");
    }
    labels.push_back(command.label);

    if (labels.size() > MAX_LABELS_AMOUNT)
    {
        throw SyntaxError(command.address + 1, "Too many labels");
    }
}


std::vector<std::string> SyntaxAnalyzer::getLabels() const
{
    return labels;
}
