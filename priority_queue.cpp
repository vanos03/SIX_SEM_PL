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

        void sort_heap(int i){
            unsigned int left = 2*i+1;
            unsigned int right = 2*i+2; 

            if (left < this->size){
                if (this->mas[i] < this->mas[left]){
                    swap(this->mas[i], this->mas[left]);
                    sort_heap(left);
                }
            }

            if (right < this->size){
                if (this->mas[i] < this->mas[right]){
                    swap(this->mas[i], this->mas[right]);
                    sort_heap(right);
                }
            }
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

        int get_size(){return this->size;}

        void insert(T new_item){
            unsigned int i = this->size;
            unsigned int parent = (i-1)/2;
            this->mas[i] = new_item;

            while (parent >= 0 && i > 0){
                if(this->mas[i] > this->mas[parent])
                    swap(this->mas[i], mas[parent]);

                i = parent;
                parent = (i-1)/2;
            }

            this->size++;
        }

        void del_max(){
            this->mas[0] = this->mas[this->size-1];
            this->size--;
            sort_heap(0);
        }

        T get_max(){return this->mas[0];}

        void print(){
            unsigned int i = 0;
            unsigned int k = 1;

            // for (int i = 0; i < this->size; i++)
            //     std::cout << this->mas[i] << " ";
            // std::cout << std::endl;

            while (i < this->size){
                while((i < k) && (i < this->size)){
                    std::cout << this->mas[i] << " ";
                    i++;
                }
                std::cout << std::endl;
                k = k*2+1;
            }
        }

        ~PQ(){
            this->size = 0;
            delete [] this->mas;
        }
};


#define N 100

template <class T>
void test_pq(){
    PQ<T> pq(N);

    for (int i = 1; i < N; i++)
        pq.insert(i);

    pq.print();
    std::cout << std::endl;
    pq.del_max();
    pq.print();


}

int main(){
    
    test_pq<int>();
    return 0;
}