//
// Created by tyan on 1/31/18.
//

#include <cstring>
#include "statement.h"

ResultSet *Statement::execute()
{
    if (this->sql.empty())
    {
        throw SQLException("sql can not be empty");
    }

    if (param_count)
    {
        mysql_stmt_bind_param(this->stmt, this->inBind.get());
    }

    if (mysql_stmt_execute(this->stmt))
    {
        throw SQLException(mysql_stmt_error(this->stmt));
    }

    this->affected_rows = mysql_stmt_affected_rows(this->stmt);

    this->result_meta = mysql_stmt_result_metadata(this->stmt);

    if (this->result_meta)
    {
        mysql_stmt_store_result(stmt);

        auto resultSet = new ResultSet(this->stmt);
        return resultSet;
    }

    return nullptr;
}

ResultSet *Statement::execute(const string &sql)
{
    this->sql = sql;

    prepare();

    return this->execute();
}


void Statement::setParam(int index, const string &val)
{
    this->inBind[index].buffer_type = MYSQL_TYPE_BLOB;
    this->inBind[index].buffer = const_cast<char *>(val.c_str());
    this->inBind[index].buffer_length = val.length();
}

void Statement::setParam(int index, int val)
{
    delete static_cast<int *>(this->inBind[index].buffer);

    auto pVal = new int;
    *pVal = val;
    this->inBind[index].buffer_type = MYSQL_TYPE_LONG;
    this->inBind[index].buffer = pVal;
}

bool Statement::prepare()
{
    if (mysql_stmt_prepare(this->stmt, this->sql.c_str(), this->sql.length()))
    {
        throw SQLException(mysql_stmt_error(this->stmt));
    }

    param_count = mysql_stmt_param_count(this->stmt);
    if (param_count)
    {
        this->inBind = std::unique_ptr<MYSQL_BIND[]>(new MYSQL_BIND[param_count]());
    }
    return true;
}

void Statement::setParam(int index, float val)
{
    delete static_cast<float *>(this->inBind[index].buffer);

    auto pVal = new float;
    *pVal = val;
    this->inBind[index].buffer_type = MYSQL_TYPE_FLOAT;
    this->inBind[index].buffer = pVal;
}

void Statement::setParam(int index, double val)
{
    delete static_cast<double *>(this->inBind[index].buffer);

    auto pVal = new double;
    *pVal = val;
    this->inBind[index].buffer_type = MYSQL_TYPE_DOUBLE;
    this->inBind[index].buffer = pVal;
}
