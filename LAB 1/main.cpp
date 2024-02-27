#include <iostream>
#include "priority_queue.cpp"

#define N 100


int main(){
    
    PQ<int> pq(N);

    for (int i = 1; i < N; i++)
        pq.insert(i);

    std::cout << "emty: " <<pq.is_empty() << std::endl;
    std::cout << "size: " << pq.get_size() << std::endl;
    std::cout << "max: " << pq.get_max() << std::endl << std::endl;
    pq.print();
    std::cout << std::endl;
    pq.del_max();
    pq.print();
}