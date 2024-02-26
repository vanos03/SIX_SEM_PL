#include <iostream>
#include "priority_queue.h"

template <class T>
void test_pq(){
    PQ<T> pq(5);
    // pq.get_size();
    // if (pq.is_empty() == 0) std::cout << "empty";
    pq.insert(1);
    pq.insert(1);
    // if (pq.is_empty()) std::cout << "empty";

}

int main(){
    
    test_pq<int>();
    return 0;
}