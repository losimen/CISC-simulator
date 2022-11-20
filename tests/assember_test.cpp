#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include "syntaxanalyzer.h"
#include "fileworker.h"

// TODO: add stack tests overflow
// TODO: add stack tests is empty

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
    const std::string fileName = "test_cases/Opcode_Unknown.txt";

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

        if (what.find("Unknown opcode - lk") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Register, MustBeNumber)
{
    const std::string fileName = "test_cases/Register_MustBeNumber.txt";

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

        if (what.find("Register name must be digit number") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Register, OutOfRange)
{
    const std::string fileName = "test_cases/Register_OutOfRange.txt";

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

        if (what.find("Register number is out of range") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Label, MustNotStartWithDigit)
{
    const std::string fileName = "test_cases/Label_MustNotStartWithDigit.txt";

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

        if (what.find("Label name must not start with digit") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Label, NameIsToLong)
{
    const std::string fileName = "test_cases/Label_NameIsToLong.txt";

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

        if (what.find("Label name is too long") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Label, InvalidCharacter)
{
    const std::string fileName = "test_cases/Label_InvalidCharacter.txt";

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

        if (what.find("Label name contains invalid character") == std::string::npos)
        {
            FAIL();
        }
    }
}


TEST(Label, AlreadyExists)
{
    const std::string fileName = "test_cases/Label_AlreadyExists.txt";

    FileWorker fileWorker(fileName);
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer;

    ASSERT_THROW(syntaxAnalyzer.analyzeCode(fileContent), MyError);

    try {
        syntaxAnalyzer.analyzeCode(fileContent);
    }
    catch (MyError &e) {
        std::string what = e.what();

        if (what.find("Label already exists") == std::string::npos) {
            FAIL();
        }
    }
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

        std::cout << what << std::endl;
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


TEST(TestProgram, Test1)
{
    const std::string fileName = "test_cases/TestProgram_Test1.txt";

    FileWorker fileWorker(fileName);
    FileContent fileContent = fileWorker.read();

    SyntaxAnalyzer syntaxAnalyzer;

    ASSERT_NO_THROW(syntaxAnalyzer.analyzeCode(fileContent));
}


#pragma clang diagnostic pop
