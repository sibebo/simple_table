#ifndef SIMPLE_TABLE_H
#define SIMPLE_TABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace simpletable
{
class Where
{
    size_t  row{0};
    size_t  column{0};
public:
    Where() = default;
    Where(size_t row, size_t column) : row(row), column(column) {}

    Where&  operator+=(const Where &a) {row += a.row; column += a.column; return *this;}
    Where&  operator-=(const Where &a) {row -= a.row; column -= a.column; return *this;}
    friend  Where    operator+(const Where &a, const Where &b) {return {a.row + b.row, a.column + b.column};}
    friend  Where    operator-(const Where &a, const Where &b) {return {a.row - b.row, a.column - b.column};}
    friend  bool    operator==(const Where &a, const Where &b) {return a.row == b.row && a.column == b.column;}

    size_t  Row() const {return row;}
    size_t  Column() const {return column;}

    void    Row(size_t row) {this->row = row;}
    void    Column(size_t column) {this->column = column;}

    void    Set(size_t row, size_t column) {this->row = row; this->column = column;}
};

class Dimension
{
    size_t  row_count{0};
    size_t  column_count{0};
public:
    Dimension() {}
    Dimension(size_t row_count, size_t column_count) : row_count(row_count), column_count(column_count) {}
    Dimension(const Where &dimension) : row_count(dimension.Row()), column_count(dimension.Column()){}

    Dimension&  operator+=(const Dimension &a) {row_count += a.row_count; column_count += a.column_count; return *this;}
    Dimension&  operator-=(const Dimension &a) {row_count -= a.row_count; column_count -= a.column_count; return *this;}
    friend  Dimension    operator+(const Dimension &a, const Dimension &b) {return {a.row_count + b.row_count, a.column_count + b.column_count};}
    friend  Dimension    operator-(const Dimension &a, const Dimension &b) {return {a.row_count - b.row_count, a.column_count - b.column_count};}
    friend  bool    operator==(const Dimension &a, const Dimension &b) {return a.row_count == b.row_count && a.column_count == b.column_count;}

    size_t  RowCount() const {return row_count;}
    size_t  ColumnCount() const {return column_count;}

    void    Row(size_t row_count) {this->row_count = row_count;}
    void    Column(size_t column_count) {this->column_count = column_count;}

    void    Set(size_t row_count, size_t column_count) {this->row_count = row_count; this->column_count = column_count;}
    void    Set(const Where &dimension) {this->row_count = dimension.Row(); this->column_count = dimension.Column();}
};

class RowIterator
{
    Where   state;
public:
    RowIterator(const Where &where) : state(where) {}

    void            operator++() {state.Column(state.Column() + 1);}
    const Where&    operator*() {return state;}
    friend  bool    operator==(const RowIterator &a, const RowIterator &b) {return a.state == b.state;}
};

class ColumnIterator
{
    Where   state;
public:
    ColumnIterator(const Where &where) : state(where) {}

    void            operator++() {state.Row(state.Row() + 1);}
    const Where&    operator*() {return state;}
    friend  bool    operator==(const ColumnIterator &a, const ColumnIterator &b) {return a.state == b.state;}
};


template<typename T>
class SimpleTable
{
protected:
    T           default_item{T()};
    Dimension   dimension;

    std::vector<std::vector<T>> table;

    void    Rectangulize()
    {
        Resize(dimension);
    }

    void    Resize(const Dimension &d)
    {
        table.resize(d.RowCount(), std::vector<T>(d.ColumnCount(), default_item));

        for (auto &r : table)
        {
            r.resize(d.ColumnCount(), default_item);
        }

        dimension = d;
    }

    void    Expand(const Dimension &d)
    {
        Dimension   new_dimension{std::max(d.RowCount(), dimension.RowCount()),
                    std::max(d.ColumnCount(), dimension.ColumnCount())};

        Resize(new_dimension);
    }

public:
    SimpleTable() {}
    SimpleTable(size_t row_count, size_t column_count, const T &default_item = T())
        : default_item(default_item),
          dimension(row_count, column_count)
    {Rectangulize();}
    SimpleTable(const Dimension &dimension, const T &default_item = T())
        : default_item(default_item),
          dimension(dimension)
    {Rectangulize();}

    bool    Contains(const Where &where) const
    {
        return where.Row() < dimension.RowCount() && where.Column() < dimension.ColumnCount();
    }

    T&      Item(const Where &where)
    {
        if (!Contains(where))
        {
            throw std::runtime_error("out of bounds");
        }

        return table[where.Row()][where.Column()];
    }

    const T&    Item(const Where &where) const
    {
        return Item(where);
    }

    void    Item(const Where &where, const T &item)
    {
        if (!Contains(where))
        {
            Expand({where + Where(1,1)});
        }

        table[where.Row()][where.Column()] = item;
    }

    std::string     ToString(char column_separator = '\t', char row_separator = '\n') const
    {
        std::stringstream   stream;
        for (const auto &r : table)
        {
            size_t  column{0};
            bool    first{true};
            for (const auto &c : r)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    stream << column_separator;
                }

                stream << c;
            }

            stream << row_separator;
        }

        return stream.str();
    }

    void    FromString(const std::string &data, char column_separator = '\t', char row_separator = '\n') const
    {
        table.clear();

        std::stringstream   stream(data);

        std::string     line;
        size_t          row{0};
        while (std::getline(stream, line, row_separator))
        {
            std::stringstream   stream(line);
            size_t          column{0};
            T   value;
            while (stream >> value)
            {
                Item({row, column++}, value);
            }

            ++row;
        }
    }

    friend  std::ostream&   operator<<(std::ostream &stream, const SimpleTable<T> &table)
    {
        stream << table.ToString();
        return stream;
    }
};

}   // namespace simpletable


#endif // SIMPLE_TABLE_H
