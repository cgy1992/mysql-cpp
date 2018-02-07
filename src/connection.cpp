//
// Created by tyan on 1/31/18.
//

#include <utility>

#include "cppmysql/connection.h"
#include "statement_wrap.h"

using std::make_shared;

shared_ptr<Statement> Connection::createStatement()
{
    auto stmtWrap = make_shared<StatementWrap>(wrap);

    return make_shared<Statement>(stmtWrap);
}

shared_ptr<Statement> Connection::prepareStatement(const string &sql)
{
    auto stmtWrap = make_shared<StatementWrap>(wrap);
    auto stmt = make_shared<Statement>(stmtWrap, sql);
    stmt->prepare();

    return stmt;
}
