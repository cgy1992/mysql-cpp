//
// Created by tyan on 1/31/18.
//

#include "driver.h"

#include "defines.h"

Driver *Driver::get_instance()
{
    return new Driver();
}

Connection *Driver::connect(const string &host, const string &user, const string &password, const string &db)
{
    return connect(host, user, password, db, 0, "", 0);
}

Connection *
Driver::connect(const string &host, const string &user, const string &password, const string &db, unsigned int port,
                const string &unix_socket,
                unsigned long flag)
{
    auto mysql = mysql_init(nullptr);
    if (!mysql)
    {
        throw SQLException("insufficient memory, failed to init mysql");
    } else
    {
        auto connection = new Connection(mysql, FWD(host), FWD(user), FWD(password), FWD(db), port, FWD(unix_socket),
                                         flag);
        connection->connect();
        return connection;
    }
}
