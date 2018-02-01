//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_CONNECTION_H
#define MYSQL_CPP_CONNECTION_H

#include <mysql/mysql.h>
#include <string>

#include "statement.h"

using std::string;

class Connection
{
public:
    explicit Connection(MYSQL *_mysql) : mysql(_mysql)
    {};

    ~Connection()
    {
        mysql_close(this->mysql);
    }

    Statement *createStatement();

    Statement *prepareStatement(const string &sql);

private:
    MYSQL *mysql;
};

#endif //MYSQL_CPP_CONNECTION_H
