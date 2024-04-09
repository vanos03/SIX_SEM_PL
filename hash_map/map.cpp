#include "list.cpp"
#include <vector>



template<class T, class Y>
class Hash_map {
private:
    list_map<T, Y>* mas_list;
    int size;
    float fill_fac;
    int m;
    float max_ff = 2.0;

    void rehash_map();

public:
    Hash_map() {
        size = 0;
        fill_fac = 0;
        m = 2;
        mas_list = new list_map<T, Y>[m];
        for (int i = 0; i < m; i++){
            mas_list[i].first = nullptr;
        }
    }

    ~Hash_map(){
        delete[] mas_list;
        size = 0;
    }

    void insert(T key, Y data);
    void print_vec();
    int get_size(){return this->size;}
    dict_t<T, Y>& operator[](T key);
    void set_ff(int new_ff);
    void del_el(T key);
};


template<class T, class Y>
void Hash_map<T,Y>::del_el(T key) {
    int h_key = std::hash<T>{}(key) % m;
     
    for (int i = 0; i < m; i++) {
               
        if (mas_list[i].first != nullptr) {
            std::cout << mas_list[i].first->key << " " << h_key << std::endl;
            if (mas_list[i].first->key == h_key) {
                mas_list[h_key].clear();
                size--;
                
                break;
            }
        }
    }
}



template<class T, class Y>
void Hash_map<T,Y>::rehash_map() {
    int old_m = m;
    m = 2 * this->size + 1;

    list_map<T, Y>* mas_list_tmp = new list_map<T, Y>[m];
    // size = 0;

    for (int i = 0; i < old_m; i++){
        Node<T,Y>* curr = mas_list[i].first;

        while(curr != NULL){
            int h_key = std::hash<T>{}(curr->val.key) % m;
            if (mas_list_tmp[h_key].first == nullptr) size++;
            mas_list_tmp[h_key].insert(curr->val.key, curr->val.data, h_key);

            curr = curr->next;
        }
    }
    
    // for (int i = 0; i < m; i++){
    //     if(mas_list_tmp[i].first == nullptr) size++;
    // }

    delete[] mas_list;
    mas_list = mas_list_tmp;
}


// template<class T, class Y>
// void Hash_map<T,Y>::insert(T key, Y data) {
//     int h_key = std::hash<T>{}(key) % m; 
//     size++;
//     // std::cout << "size: " << this->size << std::endl;
    
//     fill_fac = static_cast<float>(this->size) / m;
//     // std::cout << "ff: " << fill_fac << std::endl;

//     while(fill_fac >= max_ff) {
//         rehash_map();
//         fill_fac = static_cast<float>(this->size) / m;
//     }

// }

template<class T, class Y>
void Hash_map<T,Y>::insert(T key, Y data) {
    int h_key = std::hash<T>{}(key) % m; 

    int new_cell_added = mas_list[h_key].insert(key, data, h_key);

     size++;
    

    // std::cout << "size: " << this->size << std::endl;
    
    fill_fac = static_cast<float>(this->size) / m;
    std::cout << "ff: " << fill_fac << std::endl;

    while(fill_fac >= max_ff) {
        rehash_map();
        fill_fac = static_cast<float>(this->size) / m;
    }
}



template<class T, class Y>
void Hash_map<T,Y>::print_vec() {
    for (int i = 0; i <= m; i++){
        if(mas_list[i].first != nullptr){
            std::cout << mas_list[i].first->key << " " <<  mas_list[i].first->val.data << std::endl;
            }
    }
}

template<class T, class Y>
void Hash_map<T,Y>::set_ff(int new_ff) {
    max_ff = new_ff;
    rehash_map();
}
