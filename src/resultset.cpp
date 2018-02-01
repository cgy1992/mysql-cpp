//
// Created by tyan on 1/31/18.
//

#include "resultset.h"

ResultSet::ResultSet(MYSQL_STMT *_stmt) : stmt(_stmt)
{
    this->meta = mysql_stmt_result_metadata(this->stmt);

    this->column_count = this->meta->field_count;

    this->outBind = std::unique_ptr<MYSQL_BIND[]>(new MYSQL_BIND[this->column_count]());
    this->is_null = std::unique_ptr<my_bool[]>(new my_bool[this->column_count]());
    this->length = std::unique_ptr<unsigned long[]>(new unsigned long[this->column_count]());

    this->columns.resize(this->column_count, nullptr);

    init_bind();

    mysql_stmt_bind_result(this->stmt, this->outBind.get());
    this->row_count = mysql_stmt_num_rows(this->stmt);
}

bool ResultSet::next()
{
    reset_bind();
    auto r = mysql_stmt_fetch(this->stmt);
    if (r == 1)
    {
        throw SQLException(mysql_stmt_error(this->stmt));
    } else return r != 100;

}

int ResultSet::getInt(int index)
{
    return *static_cast<int *>(this->columns[index]);
}

string ResultSet::getString(unsigned int index)
{
    // create buff with real length
    this->columns[index] = new char[this->length[index] + 1]();
    this->outBind[index].buffer = this->columns[index];
    this->outBind[index].buffer_length = this->length[index];

    mysql_stmt_fetch_column(this->stmt, &this->outBind[index], index, 0);

    return string(static_cast<char *>(this->columns[index]));
}

void ResultSet::init_bind()
{
    for (int i = 0; i < this->column_count; ++i)
    {
        // set each bind to correct type
        this->outBind[i].buffer_type = meta->fields[i].type;
        // for each bind, alloc buff
        auto &p = this->columns[i];

        switch (meta->fields[i].type)
        {
            case MYSQL_TYPE_TINY:
            {
                p = new u_char;
                break;
            }
            case MYSQL_TYPE_SHORT:
            {
                p = new u_short;
                break;
            }
            case MYSQL_TYPE_LONG:   // fallthrough
            case MYSQL_TYPE_INT24:  // fallthrough
            {
                p = new int32_t;
                break;
            }
            case MYSQL_TYPE_LONGLONG:
            {
                p = new my_ulonglong;
                break;
            }
            case MYSQL_TYPE_DECIMAL:
            {
                break;
            }
            case MYSQL_TYPE_FLOAT:
            {
                p = new float;
                break;
            }
            case MYSQL_TYPE_DOUBLE:
            {
                p = new double;
                break;
            }
            case MYSQL_TYPE_BIT:
            {
                p = new my_ulonglong;
                break;
            }
            case MYSQL_TYPE_TIMESTAMP:  //fallthrough
            case MYSQL_TYPE_DATE:       //fallthrough
            case MYSQL_TYPE_DATETIME:   //fallthrough
            case MYSQL_TYPE_TIME:       //fallthrough
            {
                p = new MYSQL_TIME;
                break;
            }
            case MYSQL_TYPE_STRING:         //fallthrough
            case MYSQL_TYPE_VAR_STRING:     //fallthrough
            case MYSQL_TYPE_BLOB:           //fallthrough
            {
                // buffer_length is unknown, set buff to nullptr and length to 0
                // real length will be set to this->length[i]
                p = nullptr;
                this->outBind[i].buffer_length = 0;
                break;
            }
            default:
            {
                // TODO other type
            }
        }
        this->outBind[i].buffer = this->columns[i];
        this->outBind[i].is_null = &this->is_null[i];
        this->outBind[i].length = &this->length[i];
    }
}

/**
 * only need to reset MYSQL_TYPE_STRING, MYSQL_TYPE_VAR_STRING, MYSQL_TYPE_BLOB
 */
void ResultSet::reset_bind()
{
    for (int i = 0; i < this->column_count; ++i)
    {
        auto &p = this->columns[i];

        switch (meta->fields[i].type)
        {
            case MYSQL_TYPE_STRING:         //fallthrough
            case MYSQL_TYPE_VAR_STRING:     //fallthrough
            case MYSQL_TYPE_BLOB:           //fallthrough
            {
                delete[] static_cast<char *>(p);
                p = nullptr;
                this->outBind[i].buffer_length = 0;
                break;
            }
            default:
            {
                continue;
            }
        }
    }
}

double ResultSet::getDouble(int index)
{
    return *static_cast<double *>(this->columns[index]);
}

float ResultSet::getFloat(int index)
{
    return *static_cast<float *>(this->columns[index]);
}

MYSQL_TIME ResultSet::getTime(int index)
{
    return *static_cast<MYSQL_TIME *>(this->columns[index]);
}
