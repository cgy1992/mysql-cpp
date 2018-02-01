//
// Created by tyan on 1/31/18.
//

#include "connection.h"

Statement *Connection::createStatement()
{
    auto stmt = mysql_stmt_init(this->mysql);

    if (stmt)
    {
        return new Statement(stmt);
    } else
    {
        throw SQLException(mysql_error(this->mysql));
    }
}

Statement *Connection::prepareStatement(const string &sql)
{
    auto stmt = mysql_stmt_init(this->mysql);

    if (stmt)
    {
        auto statement = new Statement(stmt, sql);
        statement->prepare();
        return statement;
    } else
    {
        throw SQLException(mysql_error(this->mysql));
    }
}

Connection::Connection(MYSQL *_mysql,
                       const string &_host,
                       const string &_user,
                       const string &_password,
                       const string &_db,
                       unsigned int _port,
                       const string &_unix_socket,
                       unsigned long _flag) :
        mysql(_mysql),
        host(_host),
        user(_user),
        password(_password),
        db(_db),
        port(_port),
        unix_socket(_unix_socket),
        flag(_flag)
{
}

/**
 * do real connect
 * @return
 */
bool Connection::connect()
{
    if (mysql_real_connect(mysql, host.c_str(),
                           user.c_str(),
                           password.c_str(),
                           db.c_str(),
                           port,
                           unix_socket.empty() ? nullptr : unix_socket.c_str(),
                           flag))
    {
        return true;
    } else
    {
        throw SQLException(mysql_error(this->mysql));
    }
}
