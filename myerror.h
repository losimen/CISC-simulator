//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_MYERROR_H
#define KURSOVAAK_MYERROR_H

#include <vector>
#include <map>
#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <regex>

#include "syntaxerror.h"
#include "int24_t.h"
#include "command.h"
#include "commands.h"
#include "info.h"


class SyntaxAnalyzer
{
private:
    Command command;

    static const std::vector<std::string> labelAlphabet;
    std::vector<std::string> labels;

    static void removeDuplicatedSpaces(std::string &line);

    void checkRegisterArg(const std::string &registerName) const;
    void checkLabelName(const std::string &labelName) const;

    void checkRegister();
    void checkLabel();
    void checkAddress();
    void checkOpcode() const;

    void parseCode(std::string line);
public:
    SyntaxAnalyzer();

    Commands analyzeCode(std::vector<std::string> fileContent);
    std::vector<std::string> getLabels() const;
};



#endif //KURSOVAAK_MYERROR_H
