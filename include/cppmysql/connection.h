//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_CONNECTION_H
#define MYSQL_CPP_CONNECTION_H

#include <mysql/mysql.h>
#include <string>

#include "statement.h"

using std::string;
using std::shared_ptr;

class MySQLWrap;

class Connection
{
public:

    explicit Connection(shared_ptr<MySQLWrap> _wrap) : wrap(_wrap)
    {}

    ~Connection() = default;

    shared_ptr<Statement> createStatement();

    shared_ptr<Statement> prepareStatement(const string &sql);

private:
    shared_ptr<MySQLWrap> wrap;
};

#endif //MYSQL_CPP_CONNECTION_H
