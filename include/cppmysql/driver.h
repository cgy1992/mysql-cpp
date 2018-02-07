//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_DRIVER_H
#define MYSQL_CPP_DRIVER_H

#include <mysql/mysql.h>
#include <string>

#include "connection.h"
#include "sqlexception.h"

using std::string;
using std::unique_ptr;

class Driver
{
public:
    static Driver *get_instance();

    unique_ptr<Connection> connect(const string &host, const string &user, const string &password, const string &db);

    unique_ptr<Connection>
    connect(const string &host, const string &user, const string &password, const string &db, unsigned int port,
            const string &unix_socket, unsigned long flag);

private:

    MYSQL *mysql = nullptr;


};


#endif //MYSQL_CPP_DRIVER_H
