#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

#include "map.cpp"

int main() {
    Hash_map<int, int> map;
    dict_t<int, int> d;

    for (int i = 0; i < 3; i++){
        map.insert(i, i);
        map.insert(i*2, i*2);
        map.insert(i*5, i*5);
    }
    std::cout << "size: " << map.get_size() << std::endl;
    map.print_vec();
    map.del_el(1);

    std::cout << "size: " << map.get_size() << std::endl;
    map.print_vec();
    map.dell_all();
    return 0;
}
