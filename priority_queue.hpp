#ifndef PRIORITY_QUEUE_H   
#define PRIORITY_QUEUE_H  


template <class T>
class PQ{
    public:
        PQ(int size);
        int is_empty();
        int get_size();
        void insert(T new_item);
        void del_max();
        T get_max();
        void print();
};

#endif PRIORITY_QUEUE_H   