#include <iostream>

template <class T>
class PQ{
    private:
        unsigned int size;
        T *mas;

        void swap(T& a, T& b){
            T temp = a;
            a = b;
            b = temp;
        }

    public:
        PQ(int size){
            this->size = 0;
            this->mas = new T[size];
        }

        int is_empty(){
            if(this->size == 0) return 0;
            else return 1;
        }

        int get_size(){
            return this->size;
        }

        void insert(T new_item){
            unsigned int i = this->size;
            unsigned int parent = (i-1)/2;

            while (parent >= 0 && i > 0){
                if(this->mas[i] > this->mas[parent])
                    swap(mas[i], mas[parent]);

                i = parent;
                parent = (i-1)/2;
            }

            this->size++;
        }

        void del_item(){}

        T get_max(){}

        void print(){
            
        }

        ~PQ(){
            this->size = 0;
            delete [] this->mas;
        }
};