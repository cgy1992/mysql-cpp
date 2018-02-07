//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_SQLEXCEPTION_H
#define MYSQL_CPP_SQLEXCEPTION_H

#include <exception>
#include <string>

using std::string;
using std::exception;
using std::move;

class SQLException : exception
{
public:
    explicit SQLException(string what) : _what(move(what))
    {};

    const char *what() const noexcept final
    {
        return _what.c_str();
    }

private:
    string _what;
};

#endif //MYSQL_CPP_SQLEXCEPTION_H
