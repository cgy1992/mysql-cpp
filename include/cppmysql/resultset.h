//
// Created by tyan on 1/31/18.
//

#ifndef MYSQL_CPP_RESUTSET_H
#define MYSQL_CPP_RESUTSET_H

#include <vector>
#include <mysql/mysql.h>
#include <memory>
#include <string>

#include "sqlexception.h"

using std::vector;
using std::string;
using std::shared_ptr;

class StatementWrap;

class ResultSet
{

public:
    explicit ResultSet(shared_ptr<StatementWrap> _stmt);

    ~ResultSet();

    bool next();

    int getInt(int index);

    float getFloat(int index);

    double getDouble(int index);

    string getString(unsigned int index);

    MYSQL_TIME getTime(int index);

    unsigned long row_count;
private:

    void init_bind();

    shared_ptr<StatementWrap> wrap;

    unsigned int column_count;
    vector<char *> columns;
    std::unique_ptr<MYSQL_BIND[]> out_bind;
    std::unique_ptr<my_bool[]> is_null;
    std::unique_ptr<unsigned long[]> length;

    shared_ptr<MYSQL_RES> meta{};

};


#endif //MYSQL_CPP_RESUTSET_H
