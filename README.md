# simple_table
A dynamic templated table - aka 2D array


## example:

```c++
#include <iostream>
#include "simple_table.h"

int main()
{
    // Initializing table of ints:
    simpletable::SimpleTable<int>   table;

    // setting elements - the table expands to contain the new elements:
    table.Item({3,4}, 42);
    table.Item({5,3}, 5);
    table.Item({0,0}, 1);
    
    // location inside table is defined by the Where class:
    simpletable::Where w{2,3};
    std::cout << table.Item(w) << '\n;

    std::cout << table << '\n';
    
    // Initializing a 3x3 table with default elements of 7:
    std::cout << simpletable::SimpleTable<int>({3,3}, 7) << '\n';

    return 0;
}
```
