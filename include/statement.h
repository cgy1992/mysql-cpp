//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_STATEMENT_H
#define MYSQL_CPP_STATEMENT_H


#include <mysql/mysql.h>
#include <string>
#include <utility>
#include <memory>

#include "sqlexception.h"
#include "resultset.h"

using std::string;
using std::move;

#include <iostream>


class Statement
{
public:
    explicit Statement(MYSQL_STMT *_stmt) : stmt(_stmt)
    {}

    Statement(MYSQL_STMT *_stmt, string _sql) : stmt(_stmt), sql(move(_sql))
    {}

    ~Statement()
    {
        mysql_stmt_close(this->stmt);
        mysql_free_result(this->result_meta);
    }

    bool prepare();

    ResultSet *execute();

    ResultSet *execute(const string &sql);

    void setParam(int index, int val);

    void setParam(int index, float val);

    void setParam(int index, double val);

    void setParam(int index, const string &val);

    template<int I, typename T>
    void setParams(T val)
    {
        setParam(I, std::forward<T>(val));
    };

    /**
     * leave empty
     * @tparam I
     */
    template<int I>
    void setParams()
    {};

    template<int I = 0, typename T, typename... Ts>
    void setParams(T &&val, Ts &&...ts)
    {
        setParams<I>(std::forward<T>(val));
        setParams<I + 1>(std::forward<Ts>(ts)...);
    };

    unsigned long param_count = 0;

private:
    MYSQL_STMT *stmt;
    MYSQL_RES *result_meta = nullptr;
    string sql;
    my_ulonglong affected_rows;

    std::unique_ptr<MYSQL_BIND[]> inBind;
};


#endif //MYSQL_CPP_STATEMENT_H
