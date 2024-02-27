#include <iostream>
#include "priority_queue.cpp"

#define N 100


int main(){
    
    PQ<int> pq(N);

    for (int i = 1; i < N; i++)
        pq.insert(i);

    pq.print();
    std::cout << std::endl;
    pq.del_max();
    pq.print();
}