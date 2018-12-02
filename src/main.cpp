#include <iostream>
#include "simple_table.h"

using namespace std;

int main()
{
    cout << "Hello" << endl;

    simpletable::Where w{2,3};

    auto    ww = w + simpletable::Where(1,1);
    ww = w - simpletable::Where(2,1);


    simpletable::SimpleTable<int>   table;

    table.Item({3,4}, 42);
    table.Item({5,3}, 5);
    table.Item({0,0}, 1);

    std::cout << table << '\n';
    std::cout << simpletable::SimpleTable<int>({3,3}, 7) << '\n';

    cout << "World!" << endl;
    return 0;
}
