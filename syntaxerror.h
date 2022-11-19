//
// Created by Павло Коваль on 14.11.2022.
//

#ifndef KURSOVAAK_SYNTAXERROR_H
#define KURSOVAAK_SYNTAXERROR_H

#include <exception>
#include <string>
#include <utility>


class MyError: public std::exception
{
private:
    std::string message;

public:
    const char *what () const noexcept override
    {
        return message.c_str();
    }

    MyError(unsigned int line, const std::string& message)
    {
        this->message = "ERROR in line: " + std::to_string(line) + "| " + message;
    }

    explicit MyError(const std::string &message)
    {
        this->message = message;
    }
};


#endif //KURSOVAAK_SYNTAXERROR_H
