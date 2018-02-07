//
// Created by tyan on 2/7/18.
//

#include "statement_wrap.h"

StatementWrap::~StatementWrap()
{
    mysql_stmt_close(this->stmt);
}

StatementWrap::StatementWrap(shared_ptr<MySQLWrap> _wrap) : wrap(std::move(_wrap))
{
    this->stmt = mysql_stmt_init(this->wrap->getMysql());
}

my_ulonglong StatementWrap::affected_rows()
{
    return mysql_stmt_affected_rows(this->stmt);
}

my_bool StatementWrap::attr_get(enum enum_stmt_attr_type option, void *arg)
{
    return mysql_stmt_attr_get(this->stmt, option, arg);
}

my_bool StatementWrap::attr_set(enum enum_stmt_attr_type option, const void *arg)
{
    return mysql_stmt_attr_set(this->stmt, option, arg);
}

my_bool StatementWrap::bind_param(MYSQL_BIND *bind)
{
    return mysql_stmt_bind_param(this->stmt, bind);
}

my_bool StatementWrap::bind_result(MYSQL_BIND *bind)
{
    return mysql_stmt_bind_result(this->stmt, bind);
}

void StatementWrap::data_seek(my_ulonglong offset)
{
    mysql_stmt_data_seek(this->stmt, offset);
}

const char *StatementWrap::error()
{
    return mysql_stmt_error(this->stmt);
}

unsigned int StatementWrap::stmt_errno()
{
    return mysql_stmt_errno(this->stmt);
}

int StatementWrap::execute()
{
    return mysql_stmt_execute(this->stmt);
}

int StatementWrap::fetch()
{
    return mysql_stmt_fetch(this->stmt);
}

int StatementWrap::fetch_column(MYSQL_BIND *bind, unsigned int column, unsigned long offset)
{
    return mysql_stmt_fetch_column(this->stmt, bind, column, offset);
}

unsigned int StatementWrap::field_count()
{
    return mysql_stmt_field_count(this->stmt);
}

my_ulonglong StatementWrap::insert_id()
{
    return mysql_stmt_insert_id(this->stmt);
}

int StatementWrap::next_result()
{
    return mysql_stmt_next_result(this->stmt);
}

my_ulonglong StatementWrap::num_rows()
{
    return mysql_stmt_num_rows(this->stmt);
}

unsigned long StatementWrap::param_count()
{
    return mysql_stmt_param_count(this->stmt);
}

int StatementWrap::prepare(const string &sql)
{
    return mysql_stmt_prepare(this->stmt, sql.c_str(), sql.length());
}

my_bool StatementWrap::reset()
{
    return mysql_stmt_reset(this->stmt);
}

shared_ptr<MYSQL_RES> StatementWrap::result_metadata()
{
    return shared_ptr<MYSQL_RES>(mysql_stmt_result_metadata(this->stmt), mysql_free_result);;
}

MYSQL_ROW_OFFSET StatementWrap::row_seek(MYSQL_ROW_OFFSET offset)
{
    return mysql_stmt_row_seek(this->stmt, offset);
}

MYSQL_ROW_OFFSET StatementWrap::row_tell()
{
    return mysql_stmt_row_tell(this->stmt);
}

my_bool StatementWrap::send_long_data(unsigned int parameter_number, const char *data, unsigned long length)
{
    return mysql_stmt_send_long_data(this->stmt, parameter_number, data, length);
}

const char *StatementWrap::sqlstate()
{
    return mysql_stmt_sqlstate(this->stmt);
}

int StatementWrap::store_result()
{
    return mysql_stmt_store_result(this->stmt);
}

my_bool StatementWrap::free_result()
{
    return mysql_stmt_free_result(this->stmt);
}
