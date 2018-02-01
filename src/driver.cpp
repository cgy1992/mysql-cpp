//
// Created by tyan on 1/31/18.
//

#include "driver.h"

Driver *Driver::get_instance()
{
    auto driver = new Driver();
    driver->mysql = mysql_init(nullptr);

    return driver;
}

Connection *Driver::connect(const string &host, const string &user, const string &password, const string &db)
{
    return connect(host, user, password, db, 0, nullptr, 0);
}

Connection *
Driver::connect(const string &host, const string &user, const string &password, const string &db, unsigned int port,
                const char *unix_socket,
                unsigned long flag)
{
    if (mysql_real_connect(this->mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(),
                           port,
                           unix_socket,
                           flag))
    {
        auto connection = new Connection(this->mysql);
        return connection;
    } else
    {
        throw SQLException(mysql_error(this->mysql));
    }
}
