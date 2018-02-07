//
// Created by tyan on 2/7/18.
//

#include "mysql_wrap.h"

MYSQL *MySQLWrap::getMysql()
{
    return this->mysql;
}

MySQLWrap::MySQLWrap()
{
    this->mysql = mysql_init(nullptr);
}

MySQLWrap::~MySQLWrap()
{
    mysql_close(this->mysql);
}

bool
MySQLWrap::connect(const string &host, const string &user, const string &passwd, const string &db, unsigned int port,
                   const string &unix_socket, unsigned long client_flag)
{
    return mysql_real_connect(this->mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port,
                              unix_socket.max_size() ? nullptr : unix_socket.c_str(), client_flag) == this->mysql;
}

const char *MySQLWrap::error()
{
    return mysql_error(this->mysql);
}
