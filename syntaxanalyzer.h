//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_SYNTAXANALYZER_H
#define KURSOVAAK_SYNTAXANALYZER_H

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

typedef std::map<int, int24_t> Register;


#define ADD "add"
#define NAND "nand"
#define LW "lw"
#define SW "sw"
#define BEQ "beq"
#define JALR "jalr"
#define HALT "halt"
#define NOOP "noop"

#define FILL ".fill"

typedef std::vector<Command> Commands;


class SyntaxAnalyzer
{
private:
    Command command;

    static const std::vector<std::string> labelAlphabet;
    std::vector<std::string> labels;

    void removeDuplicatedSpaces(std::string &line);
    void checkRegisterArg(const std::string &registerName);
    void checkLabelName(const std::string &labelName);

    void checkRegister();
    void checkLabel();
    void checkAddress();
    void checkOpcode();

    void parseCode(std::string line);
public:
    SyntaxAnalyzer();

    Commands analyzeCode(std::vector<std::string> fileContent);
};



#endif //KURSOVAAK_SYNTAXANALYZER_H
