#include <iostream>
#include "simple_table.h"

using namespace std;


void    Example()
{
    // Initializing table of ints:
    simpletable::SimpleTable<int>   table;

    // setting elements - the table expands to contain the new elements:
    table.Item({3,4}, 42);
    table.Item({5,3}, 5);
    table.Item({0,0}, 1);

    // location inside table is defined by the Where class:
    simpletable::Where w{2,3};
    std::cout << table.Item(w) << '\n';

    std::cout << table << '\n';

    // Initializing a 3x3 table with default elements of 7:
    std::cout << simpletable::SimpleTable<int>({3,3}, 7) << '\n';
}


int main()
{
    for (simpletable::Where w : simpletable::Dimension(4, 5))
    {
        std::cout << w.Row() << ", " << w.Column() << '\n';
    }



    cout << "Hello" << endl;

    simpletable::Where w{2,3};

    auto    ww = w + simpletable::Where(1,1);
    ww = w - simpletable::Where(2,1);


    simpletable::SimpleTable<int>   table;

    table.Item({3,4}, 42);
    table.Item({5,3}, 5);
    table.Item({0,0}, 1);

    std::cout << '\n';
    std::cout << table << '\n';
    std::cout << simpletable::SimpleTable<int>({3,3}, 7) << '\n';
    std::cout << table << '\n';

    simpletable::SimpleTable<int>   t({5,5}, 1);
    simpletable::SimpleTable<int>   s({2,2}, 8);

    std::cout << '\n';
    std::cout << t << '\n';
    std::cout << s << '\n';
    t.SetSub(s, {2,1});
    std::cout << t << '\n';

    std::cout << '\n';
    std::cout << t.GetSub({1,2}, {2, 3}) << '\n';

    cout << "World!" << endl;
    return 0;
}
