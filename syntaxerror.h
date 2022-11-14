//
// Created by Павло Коваль on 14.11.2022.
//

#ifndef KURSOVAAK_SYNTAXERROR_H
#define KURSOVAAK_SYNTAXERROR_H

#include <exception>
#include <string>


class SyntaxError: public std::exception
{
private:
    std::string message;

public:
    const char *what () const throw ()
    {
        return message.c_str();
    }

    SyntaxError(unsigned int line, std::string message)
    {
        this->message = "ERROR in line: " + std::to_string(line) + "| " + message;
    }

};


#endif //KURSOVAAK_SYNTAXERROR_H
