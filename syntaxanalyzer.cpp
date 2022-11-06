//
// Created by Павло Коваль on 06.11.2022.
//

#include "syntaxanalyzer.h"

const std::vector<std::string> SyntaxAnalyzer::opcodes {".fill",
                                                        "add",
                                                        "nand",
                                                        "lw",
                                                        "sw",
                                                        "beq",
                                                        "jalr",
                                                        "noop",
                                                        "halt"};

const std::vector<std::string> SyntaxAnalyzer::labelAlphabetName {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                                                                 "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                                                                 "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "_", "$"};


SyntaxAnalyzer::SyntaxAnalyzer()
{
    labels = std::vector<std::string>();
    variables = std::vector<std::string>();
}


Code SyntaxAnalyzer::analyzeCode(std::string line)
{
    Code result;

    removeDuplicatedSpaces(line);
    std::cout << "--Line: " << line << std::endl;

    result = parseCode(line);

    if (result["label"] != "")
        checkLabel(result);

    checkOpcode(result);
    checkRegister(result);
    checkAddress(result);

    return result;
}


void SyntaxAnalyzer::removeDuplicatedSpaces(std::string &line)
{
    std::string::iterator new_end = std::unique(line.begin(), line.end(),
                                                [](char lhs, char rhs)
                                                {
                                                        return (lhs == rhs) && (lhs == ' ');;
                                                }
    );
    line.erase(new_end, line.end());
}


Code SyntaxAnalyzer::parseCode(std::string line)
{
    Code result;

    result["label"] = "";
    result["opcode"] = "";
    result["arg0"] = "";
    result["arg1"] = "";
    result["arg2"] = "";

    if (line[0] != ' ')
    {
        result["label"] = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
    }
    else
    {
        line = line.substr(line.find(' ') + 1);
    }

    result["opcode"] = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    result["arg0"] = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    result["arg1"] = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);

    result["arg2"] = line.substr(0, line.find(' '));

    std::cout << "LABEL " << result["label"] << std::endl;
    std::cout << "OPCODE " << result["opcode"] << std::endl;
    std::cout << "ARG0 " << result["arg0"] << std::endl;
    std::cout << "ARG1 " << result["arg1"] << std::endl;
    std::cout << "ARG2 " << result["arg2"] << std::endl;
    std::cout << std::endl;

    return result;
}


void SyntaxAnalyzer::checkRegister(Code &code)
{
    if (code["opcode"] == "add" || code["opcode"] == "nand" ||
        code["opcode"] == "lw" || code["opcode"] == "sw" ||
        code["opcode"] == "beq" || code["opcode"] == "jalr")
    {
        checkRegisterArg(code["arg0"]);
        checkRegisterArg(code["arg1"]);
    }

    if (code["opcode"] == "add" || code["opcode"] == "nande")
    {
        checkRegisterArg(code["arg2"]);
    }
}


void SyntaxAnalyzer::checkRegisterArg(const std::string &registerName)
{
    if (!std::isdigit(registerName[0]))
    {
        throw std::runtime_error("Register name must be digit number");
    }

    if (std::stoi(registerName) < 0 || std::stoi(registerName) > 7)
    {
        throw std::runtime_error("Register number is out of range");
    }
}


void SyntaxAnalyzer::checkAddress(Code &code)
{
    if (code["opcode"] == "lw" || code["opcode"] == "sw" ||
        code["opcode"] == "beq")
    {
        checkAddressArg(code["arg2"]);
    }

    if (code["opcode"] == ".fill")
    {
        checkAddressArg(code["arg0"]);
    }
}


void SyntaxAnalyzer::checkOpcode(Code &code)
{
    if (std::find(opcodes.begin(), opcodes.end(), code["opcode"]) == opcodes.end())
    {
        throw std::runtime_error("Unknown opcode - " + code["opcode"]);
    }
}


void SyntaxAnalyzer::checkAddressArg(const std::string &address)
{
    checkLabelName(address);
}


void SyntaxAnalyzer::checkLabelName(const std::string &labelName)
{
    if (std::isdigit(labelName[0]))
    {
        throw std::runtime_error("Label name must not start with digit");
    }

    if (labelName.length() > MAX_LABEL_LENGTH)
    {
        throw std::runtime_error("Label name is too long");
    }

    for (auto &ch: labelName)
    {
        if (std::find(labelAlphabetName.begin(), labelAlphabetName.end(), std::string(1, ch)) == labelAlphabetName.end())
        {
            throw std::runtime_error("Label name contains invalid character");
        }
    }
}


void SyntaxAnalyzer::checkLabel(Code &code)
{
    checkLabelName(code["label"]);

    if (std::find(labels.begin(), labels.end(), code["label"]) != labels.end())
    {
        throw std::runtime_error("Label already exists");
    }
    labels.push_back(code["label"]);

    if (labels.size() > MAX_LABELS_AMOUNT)
    {
        throw std::runtime_error("Too many labels");
    }
}
