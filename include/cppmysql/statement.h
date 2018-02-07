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
using std::shared_ptr;

class StatementWrap;

class Statement
{
public:
    explicit Statement(shared_ptr<StatementWrap> _wrap) : wrap(std::move(_wrap))
    {}

    Statement(shared_ptr<StatementWrap> _wrap, string _sql) : wrap(std::move(_wrap)), sql(std::move(_sql))
    {}


    bool prepare();

    shared_ptr<ResultSet> execute();

    shared_ptr<ResultSet> execute(const string &sql);

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
    shared_ptr<StatementWrap> wrap;

    shared_ptr<MYSQL_RES> result_meta{};
    string sql;
    my_ulonglong affected_rows{};

    std::unique_ptr<MYSQL_BIND[]> inBind{};
};


#endif //MYSQL_CPP_STATEMENT_H
