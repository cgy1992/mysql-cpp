//
// Created by tyan on 2/7/18.
//

#ifndef MYSQL_CPP_MYSQL_WRAP_H
#define MYSQL_CPP_MYSQL_WRAP_H

#include <string>

#include <mysql/mysql.h>

using std::string;

class MySQLWrap
{
public:
    MySQLWrap();

    ~MySQLWrap();

    MYSQL *getMysql();

    const char * error();

    bool connect(const string &host, const string &user, const string &passwd, const string &db, unsigned int port,
                 const string &unix_socket, unsigned long client_flag);


private:
    MYSQL *mysql;
};


#endif //MYSQL_CPP_MYSQL_WRAP_H
