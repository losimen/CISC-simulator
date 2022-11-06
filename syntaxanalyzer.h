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

#define AMOUNT_OF_REGISTERS 8
#define MAX_LABEL_LENGTH 7
#define MAX_LABELS_AMOUNT 100


typedef std::map<int, int> Register;
typedef std::map<std::string, std::string> Code;

class SyntaxAnalyzer
{
private:
    static const std::vector<std::string> opcodes;
    static const std::vector<std::string> labelAlphabetName;
    std::array<Register, AMOUNT_OF_REGISTERS> registers;

    std::vector<std::string> labels;
    std::vector<std::string> variables;

    static void removeDuplicatedSpaces(std::string &line);
    static void checkRegisterArg(const std::string &registerName);
    static void checkAddressArg(const std::string &address);
    static void checkLabelName(const std::string &labelName);

    static void checkRegister(Code &code);
    void checkLabel(Code &code);
    void checkAddress(Code &code);
    void checkOpcode(Code &code);

    Code parseCode(std::string line);

public:
    SyntaxAnalyzer();

    Code analyzeCode(std::string line);
};



#endif //KURSOVAAK_SYNTAXANALYZER_H
