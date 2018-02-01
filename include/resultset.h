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

class ResultSet
{

public:
    explicit ResultSet(MYSQL_STMT *_stmt);

    ~ResultSet()
    {
        mysql_stmt_free_result(this->stmt);
        for (int i = 0; i < this->column_count; ++i)
        {
            switch (meta->fields[i].type)
            {
                case MYSQL_TYPE_TINY:
                {
                    delete static_cast<u_char *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_SHORT:
                {
                    delete static_cast<u_short *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_LONG:   // fallthrough
                case MYSQL_TYPE_INT24:  // fallthrough
                {
                    delete static_cast<int32_t *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_LONGLONG:
                {
                    delete static_cast<my_ulonglong *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_DECIMAL:
                {
                    break;
                }
                case MYSQL_TYPE_FLOAT:
                {
                    delete static_cast<float *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_DOUBLE:
                {
                    delete static_cast<double *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_BIT:
                {
                    delete static_cast<my_ulonglong *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_TIMESTAMP:  //fallthrough
                case MYSQL_TYPE_DATE:       //fallthrough
                case MYSQL_TYPE_DATETIME:   //fallthrough
                case MYSQL_TYPE_TIME:       //fallthrough
                {
                    delete static_cast<MYSQL_TIME *>(this->columns[i]);
                    break;
                }
                case MYSQL_TYPE_STRING:         //fallthrough
                case MYSQL_TYPE_VAR_STRING:     //fallthrough
                case MYSQL_TYPE_BLOB:           //fallthrough
                {
                    // buffer_length is unknown, set buff to nullptr and length to 0
                    // real length will be set to this->length[i]
                    delete[] static_cast<char *>(this->columns[i]);
                    this->outBind[i].buffer_length = 0;
                    break;
                }
                default:
                {
                    // TODO other type
                }
            }
        }
        mysql_free_result(this->meta);
    }

    bool next();

    int getInt(int index);

    float getFloat(int index);

    double getDouble(int index);

    string getString(unsigned int index);

    MYSQL_TIME getTime(int index);

    unsigned long row_count;
private:

    void init_bind();
    void reset_bind();

    MYSQL_STMT *stmt;

    unsigned int column_count;
    vector<void *> columns;
    std::unique_ptr<MYSQL_BIND[]> outBind;
    std::unique_ptr<my_bool[]> is_null;
    std::unique_ptr<unsigned long[]> length;

    MYSQL_RES *meta;

};


#endif //MYSQL_CPP_RESUTSET_H
