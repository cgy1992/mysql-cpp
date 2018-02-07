//
// Created by tyan on 1/31/18.
//

#include <cstring>
#include "cppmysql/statement.h"
#include "statement_wrap.h"

using std::make_shared;

shared_ptr<ResultSet> Statement::execute()
{
    if (this->sql.empty())
    {
        throw SQLException("sql can not be empty");
    }

    if (param_count)
    {
        this->wrap->bind_param(this->inBind.get());
    }

    if (this->wrap->execute())
    {
        throw SQLException(this->wrap->error());
    }

    this->affected_rows = this->wrap->affected_rows();

    this->result_meta = this->wrap->result_metadata();

    if (this->result_meta)
    {
        this->wrap->store_result();

        auto resultSet = make_shared<ResultSet>(this->wrap);
        return resultSet;
    }

    return nullptr;
}

shared_ptr<ResultSet> Statement::execute(const string &sql)
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
    if (this->wrap->prepare(this->sql))
    {
        throw SQLException(this->wrap->error());
    }

    param_count = this->wrap->param_count();
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
