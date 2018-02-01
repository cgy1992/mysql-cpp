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
