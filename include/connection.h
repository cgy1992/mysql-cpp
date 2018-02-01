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
    Connection(MYSQL *_mysql,
               const string &_host,
               const string &_user,
               const string &_password,
               const string &_db,
               unsigned int _port,
               const string &_unix_socket,
               unsigned long _flag);

    ~Connection()
    {
        mysql_close(this->mysql);
    }

    Statement *createStatement();

    Statement *prepareStatement(const string &sql);

    bool connect();

private:

    MYSQL *mysql;
    string host;
    string user;
    string password;
    string db;
    unsigned int port;
    string unix_socket;
    unsigned long flag;
};

#endif //MYSQL_CPP_CONNECTION_H
