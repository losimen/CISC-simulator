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

#include "int24_t.h"
#include "command.h"

typedef std::map<int, int24_t> Register;


class SyntaxAnalyzer
{
private:
    static const std::vector<std::string> labelAlphabetName;
    std::vector<std::string> labels;

    static void removeDuplicatedSpaces(std::string &line);
    static void checkRegisterArg(const std::string &registerName);
    static void checkAddressArg(const std::string &address);
    static void checkLabelName(const std::string &labelName);

    static void checkRegister(Command &command);
    void checkLabel(Command &command);
    static void checkAddress(Command &command);
    static void checkOpcode(Command &code);

    static Command parseCode(std::string line);
public:
    SyntaxAnalyzer();

    Command analyzeCode(std::string line);
};



#endif //KURSOVAAK_SYNTAXANALYZER_H
