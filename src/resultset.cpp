//
// Created by tyan on 1/31/18.
//

#include "cppmysql/resultset.h"

#include "statement_wrap.h"

ResultSet::ResultSet(shared_ptr<StatementWrap> _wrap) : wrap(std::move(_wrap))
{
    this->meta = this->wrap->result_metadata();

    this->column_count = this->meta->field_count;

    this->out_bind = std::unique_ptr<MYSQL_BIND[]>(new MYSQL_BIND[this->column_count]());
    this->is_null = std::unique_ptr<my_bool[]>(new my_bool[this->column_count]());
    this->length = std::unique_ptr<unsigned long[]>(new unsigned long[this->column_count]());

    this->columns.resize(this->column_count, nullptr);

    init_bind();

    this->wrap->bind_result(this->out_bind.get());

    this->row_count = this->wrap->num_rows();
}

bool ResultSet::next()
{
    auto r = this->wrap->fetch();
    if (r == 1)
    {
        throw SQLException(this->wrap->error());
    } else return r != 100;

}

int ResultSet::getInt(int index)
{
    return *reinterpret_cast<int *>(this->columns[index]);
}

string ResultSet::getString(unsigned int index)
{
    // create buff with real length
    this->columns[index] = new char[this->length[index] + 1]();
    this->out_bind[index].buffer = this->columns[index];
    this->out_bind[index].buffer_length = this->length[index];

    this->wrap->fetch_column(&this->out_bind[index], index, 0);
    auto str = string(this->columns[index]);
    // delete buffer
    delete[] this->columns[index];
    this->out_bind[index].buffer = nullptr;
    this->columns[index] = nullptr;
    this->out_bind[index].buffer_length = 0;
    return str;
}

void ResultSet::init_bind()
{
    for (int i = 0; i < this->column_count; ++i)
    {
        auto type = this->meta->fields[i].type;
        auto &p = this->columns[i];
        auto &bind = this->out_bind[i];

        bind.buffer_type = type;

        switch (type)
        {
            case MYSQL_TYPE_NULL:
                bind.buffer_length = 0;
                break;
            case MYSQL_TYPE_TINY:
                p = new char[1];
                bind.buffer_length = 1;
                break;
            case MYSQL_TYPE_SHORT:
                p = new char[2];
                bind.buffer_length = 2;
                break;
            case MYSQL_TYPE_INT24:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_FLOAT:
                p = new char[4];
                bind.buffer_length = 4;
                break;
            case MYSQL_TYPE_DOUBLE:
            case MYSQL_TYPE_LONGLONG:
                p = new char[8];
                bind.buffer_length = 8;
                break;
            case MYSQL_TYPE_YEAR:
                p = new char[2];
                bind.buffer_length = 2;
                bind.buffer_type = MYSQL_TYPE_SHORT;
                break;
            case MYSQL_TYPE_TIMESTAMP:
            case MYSQL_TYPE_DATE:
            case MYSQL_TYPE_TIME:
            case MYSQL_TYPE_DATETIME:
                p = new char[sizeof(MYSQL_TIME)];
                bind.buffer_length = sizeof(MYSQL_TIME);
                break;
            case MYSQL_TYPE_TINY_BLOB:
            case MYSQL_TYPE_MEDIUM_BLOB:
            case MYSQL_TYPE_LONG_BLOB:
            case MYSQL_TYPE_BLOB:
            case MYSQL_TYPE_STRING:
            case MYSQL_TYPE_VAR_STRING:
                // set buffer to nullptr and length to 0
                // real length will be return after fetch
                p = nullptr;
                bind.buffer_length = 0;
                break;
            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_NEWDECIMAL:
                p = new char[64];
                bind.buffer_length = 64;
                break;
            case MYSQL_TYPE_BIT:
                p = new char[8];
                bind.buffer_length = 8;
                break;
            case MYSQL_TYPE_GEOMETRY:
            default:
                throw SQLException("known type");
        }


        this->out_bind[i].buffer = p;
        this->out_bind[i].length = &this->length[i];
        this->out_bind[i].is_null = &this->is_null[i];

    }
}

double ResultSet::getDouble(int index)
{
    return *reinterpret_cast<double *>(this->columns[index]);
}

float ResultSet::getFloat(int index)
{
    return *reinterpret_cast<float *>(this->columns[index]);
}

MYSQL_TIME ResultSet::getTime(int index)
{
    return *reinterpret_cast<MYSQL_TIME *>(this->columns[index]);
}

ResultSet::~ResultSet()
{
    this->wrap->free_result();
    for (int i = 0; i < this->column_count; ++i)
    {
        delete[] this->columns[i];
    }
}
