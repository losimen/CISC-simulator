#include <gtest/gtest.h>
#include <cstdio>

#include "fileworker.h"
#include "syntaxanalyzer.h"
#include "codegenerator.h"
#include "simulator.h"


void testProgram(const std::string &programName, const int expectedReg, const int expectedValue)
{
    FileWorker fileWorkerIn(programName);
    FileWorker fileWorkerOut("output.txt");

    FileContent fileContent = fileWorkerIn.read();
    Commands commands;

    SyntaxAnalyzer syntaxAnalyzer;
    commands = syntaxAnalyzer.analyzeCode(fileContent);

    CodeGenerator codeGenerator;
    codeGenerator.generate(fileWorkerOut, commands);

    Simulator simulator(fileWorkerOut.read());
    simulator.run();

    ASSERT_EQ(simulator.getRegisters()[expectedReg].to_int(), expectedValue);
    remove("output.txt");
}


void testError(const std::string &fileName, const std::string &errStr)
{
    FileWorker fileWorker(fileName);
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer;

    ASSERT_THROW(syntaxAnalyzer.analyzeCode(fileContent), MyError);

    try
    {
        syntaxAnalyzer.analyzeCode(fileContent);
    }
    catch (MyError &e)
    {
        std::string what = e.what();

        if (what.find(errStr) == std::string::npos)
        {
            FAIL();
        }
    }
}



TEST(FileWorker, NotExistingFile)
{
    const std::string fileName = "test_cases/noExisting.txt";

    FileWorker fileWorker(fileName);

    ASSERT_THROW(fileWorker.read(), std::runtime_error);
}


TEST(FileWorker, ExistingFile)
{
    const std::string fileName = "test_cases/FileWorker_ExistingFile.txt";

    FileWorker fileWorker(fileName);

}


TEST(Opcode, UnknownOpcode)
{
    testError("test_cases/Opcode_Unknown.txt", "Unknown opcode");
}


TEST(Register, MustBeNumber)
{
    testError("test_cases/Register_MustBeNumber.txt", "Register name must be digit number");
}


TEST(Register, OutOfRange)
{
    testError("test_cases/Register_OutOfRange.txt", "Register number is out of range");
}


TEST(Label, MustNotStartWithDigit)
{
    testError("test_cases/Label_MustNotStartWithDigit.txt", "Label name must not start with digit");
}


TEST(Label, NameIsToLong)
{
    testError("test_cases/Label_NameIsToLong.txt", "Label name is too long");
}


TEST(Label, InvalidCharacter)
{
    testError("test_cases/Label_InvalidCharacter.txt", "Label name contains invalid character");
}


TEST(Label, AlreadyExists)
{
    testError("test_cases/Label_AlreadyExists.txt", "Label already exists");
}


TEST(Label, ToManyLabels)
{
    const std::string fileName = "test_cases/Label_ToManyLabels.txt";

    FileWorker fileWorker(fileName);
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer1;

    ASSERT_THROW(syntaxAnalyzer1.analyzeCode(fileContent), MyError);

    try
    {
        SyntaxAnalyzer syntaxAnalyzer2;
        syntaxAnalyzer2.analyzeCode(fileContent);
    }
    catch (MyError &e)
    {
        std::string what = e.what();

        if (what.find("Too many labels") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Label, Correct)
{
    const std::string fileName = "test_cases/Label_Correct.txt";

    FileWorker fileWorker(fileName);
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer;

    ASSERT_NO_THROW(syntaxAnalyzer.analyzeCode(fileContent));
}


TEST(TestProgram, ADC_)
{
    testProgram("example_programs/ADC.txt", 3, -16777214);
    testProgram("example_programs/ADC.txt", 4, 1);
}


TEST(TestProgram, add_XADD_pure)
{
    testProgram("example_programs/add_XADD_pure.txt", 1, 3);
    testProgram("example_programs/add_XADD_pure.txt", 2, 2);
    testProgram("example_programs/add_XADD_pure.txt", 3, 5);
}


TEST(TestProgram, add_XADD_stack)
{
    testProgram("example_programs/add_XADD_stack.txt", 1, 3);
    testProgram("example_programs/add_XADD_stack.txt", 2, 2);
    testProgram("example_programs/add_XADD_stack.txt", 3, 5);
}


TEST(TestProgram, cmp_JE)
{
    testProgram("example_programs/cmp_JE.txt", 1, 3);
}


TEST(TestProgram, cmp_JNE)
{
    testProgram("example_programs/cmp_JL.txt", 1, 2);
    testProgram("example_programs/cmp_JL.txt", 2, 3);
}


TEST(TestProgram, count10_ADD_pure)
{
    testProgram("example_programs/count10_ADD_pure.txt", 1, -10);
}


TEST(TestProgram, count10_ADD_stack)
{
    testProgram("example_programs/count10_ADD_stack.txt", 1, 10);
}


TEST(TestProgram, count10_DEC_pure)
{
    testProgram("example_programs/count10_DEC_pure.txt", 1, -10);
}


TEST(TestProgram, count10_DEC_stack)
{
    testProgram("example_programs/count10_DEC_stack.txt", 1, -25);
}


TEST(TestProgram, div2_IDIV_pure)
{
    testProgram("example_programs/div2_IDIV_pure.txt", 1, 10);
    testProgram("example_programs/div2_IDIV_pure.txt", 2, 5);
    testProgram("example_programs/div2_IDIV_pure.txt", 3, 2);
}


TEST(TestProgram, div2_IDIV_stack)
{
    testProgram("example_programs/div2_IDIV_stack.txt", 1, 10);
    testProgram("example_programs/div2_IDIV_stack.txt", 2, 5);
    testProgram("example_programs/div2_IDIV_stack.txt", 3, 2);
}


TEST(TestProgram, div_minus_IDIV_pure)
{
    testProgram("example_programs/div-_IDIV_pure.txt", 1, -10);
    testProgram("example_programs/div-_IDIV_pure.txt", 2, 5);
    testProgram("example_programs/div-_IDIV_pure.txt", 3, -2);
}


TEST(TestProgram, JMA_good)
{
    testProgram("example_programs/JMA_good.txt", 1, 4);
}


TEST(TestProgram, JMNE_good)
{
    testProgram("example_programs/JMNE_good.txt", 1, 2);
}


TEST(TestProgram, neg_NEG_pure)
{
    testProgram("example_programs/neg_NEG_pure.txt", 1, -3);
}


TEST(TestProgram, neg_NEG_stack)
{
    testProgram("example_programs/neg_NEG_stack.txt", 1, -3);
}


TEST(TestProgram, or_OR_pure)
{
    testProgram("example_programs/or_OR_pure.txt", 1, 5);
    testProgram("example_programs/or_OR_pure.txt", 2, 160);
}


TEST(TestProgram, or_OR_stack)
{
    testProgram("example_programs/or_OR_stack.txt", 1, 2);
    testProgram("example_programs/or_OR_stack.txt", 2, 3);
    testProgram("example_programs/or_OR_stack.txt", 2, 3);
}


TEST(TestProgram, shl_SHL_pure)
{
    testProgram("example_programs/shl_SHL_pure.txt", 1, 2);
    testProgram("example_programs/shl_SHL_pure.txt", 2, 4);
}


TEST(TestProgram, shl_SHL_stack)
{
    testProgram("example_programs/shl_SHL_stack.txt", 1, 2);
    testProgram("example_programs/shl_SHL_stack.txt", 2, 3);
    testProgram("example_programs/shl_SHL_stack.txt", 3, 16);
}
