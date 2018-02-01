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

class Driver
{
public:
    static Driver *get_instance();

    Connection *connect(const string &host, const string &user, const string &password, const string &db);

    Connection *
    connect(const string &host, const string &user, const string &password, const string &db, unsigned int port,
            const string &unix_socket, unsigned long flag);

private:

    MYSQL *mysql = nullptr;


};


#endif //MYSQL_CPP_DRIVER_H
