//
// Created by tyan on 1/31/18.
//

#include "cppmysql/driver.h"

#include "mysql_wrap.h"

using std::make_shared;

Driver *Driver::get_instance()
{
    return new Driver();
}

unique_ptr<Connection> Driver::connect(const string &host, const string &user, const string &password, const string &db)
{
    return connect(host, user, password, db, 0, "", 0);
}

unique_ptr<Connection>
Driver::connect(const string &host, const string &user, const string &password, const string &db, unsigned int port,
                const string &unix_socket,
                unsigned long flag)
{
    auto wrap = make_shared<MySQLWrap>();
    if (wrap->getMysql() == nullptr)
    {
        throw SQLException("insufficient memory, failed to init mysql");
    } else
    {
        auto r = wrap->connect(host, user, password, db, port, unix_socket, flag);
        if (r)
        {
            return unique_ptr<Connection>(new Connection(wrap));
        } else throw SQLException(wrap->error());
    }
}
