//
// Created by tyan on 2/7/18.
//

#ifndef MYSQL_CPP_STATEMENT_WRAP_H
#define MYSQL_CPP_STATEMENT_WRAP_H

#include <memory>
#include <string>

#include <mysql/mysql.h>

#include "mysql_wrap.h"

using std::shared_ptr;
using std::string;

class StatementWrap
{
public:
    explicit StatementWrap(shared_ptr<MySQLWrap> wrap);

    ~StatementWrap();

    my_ulonglong affected_rows();

    my_bool attr_get(enum enum_stmt_attr_type option, void *arg);

    my_bool attr_set(enum enum_stmt_attr_type option, const void *arg);

    my_bool bind_param(MYSQL_BIND *bind);

    my_bool bind_result(MYSQL_BIND *bind);

    void data_seek(my_ulonglong offset);

    unsigned int stmt_errno();

    const char *error();

    int execute();

    int fetch();

    int fetch_column(MYSQL_BIND *bind, unsigned int column, unsigned long offset);

    unsigned int field_count();

    my_ulonglong insert_id();

    int next_result();

    my_ulonglong num_rows();

    unsigned long param_count();

    int prepare(const string &sql);

    my_bool reset();

    shared_ptr<MYSQL_RES> result_metadata();

    MYSQL_ROW_OFFSET row_seek(MYSQL_ROW_OFFSET offset);

    MYSQL_ROW_OFFSET row_tell();

    my_bool send_long_data(unsigned int parameter_number, const char *data, unsigned long length);

    const char *sqlstate();

    int store_result();

    my_bool free_result();

private:
    shared_ptr<MySQLWrap> wrap;

    MYSQL_STMT *stmt;
};


#endif //MYSQL_CPP_STATEMENT_WRAP_H
