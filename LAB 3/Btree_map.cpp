#include <iostream>
#include <map>
#include <vector>

#define TRUE 1
#define FALSE 0

template<class T, class Y>
struct qwerty{
    T key;
    Y data;
};

template<class T, class Y>
using dict_t = qwerty<T, Y>;

template<class T, class Y>
class Node{
    private:
        void swap(T& src, T& dst){
            T tmp = src;
            src = dst;
            dst = tmp;
        }

        void sort(int t) { 
            for (int i = 0; i < (2*t-2); i++){
                for (int j = i+1; j <= (2*t-1); j++){
                    if ((this->mas[i].key != 0) && (this->mas[j].key != 0)){
                        if ((this->mas[i].key) > (this->mas[j].key)){
                            swap(this->mas[i].key, this->mas[j].key);
                            swap(this->mas[i].data, this->mas[j].data);
                        }
                    } else 
                        break;
                }
            }
        }
        
    public:
        unsigned char leaf;
        int curr_size;
        std::vector<Node*> children;
        dict_t<T, Y>* mas;

        Node(int t, unsigned char is_leaf){
            mas = new dict_t<T, Y>[t*2-1];
            this->children.resize(t*2);
            this->leaf = is_leaf;
            this->curr_size = 0;
            for (int i = 0; i < t*2; i++)
                this->children[i] = NULL;
        }
        ~Node(){
            delete[] mas;
            for (int i = 0; i < children.size(); ++i) {
                delete children[i];
            }
        }

        void insert_to_node(dict_t<T, Y> new_elems, int t){
            this->mas[this->curr_size] = new_elems;
            this->curr_size++;
            sort(t);
        }
    

        void split_child(int i,  Node<T, Y>* node, int t){
            Node<T, Y>* tmp = new Node<T, Y>(t, node->leaf);
            tmp->curr_size = t-1;

            for (int j = 0; j < t-1; j++)
                tmp->mas[j] = node->mas[j+t];

            if (node->leaf == FALSE){
                for (int j = 0; j < t-1; j++)
                    tmp->children[j] = node->children[j+t];
            }

            node->curr_size = t-1;
            for (int j = this->curr_size; j >= i+1; j--)
                this->children[j] = this->children[j+1];

            this->children[i+1] = tmp;
            for (int j = this->curr_size-1; j >= i; j--)
                this->mas[j+1] = this->mas[j];

            this->mas[i] = node->mas[t-1];
            this->curr_size++;
        }


        void insert_non_full(dict_t<T, Y> new_elems, int t){
            int i = this->curr_size-1;

            if (this->leaf == TRUE){
                while((i >= 0) && (new_elems.key < this->mas[i].key)){ 
                    this->mas[i+1].key = this->mas[i].key;
                    i--;
                }
                // this->insert_to_node(new_elems, t);
                this->mas[i+1] = new_elems;
                this->curr_size++;
            }else {
                while((i >= 0) && (new_elems.key < this->mas[i].key)) i--;

                if (this->children[i+1]->curr_size == 2*t-1){ 
                    this->split_child(i + 1, this->children[i + 1], t);
                    if (this->mas[i+1].key < new_elems.key) i++;
                }
                this->children[i+1]->insert_non_full(new_elems, t);
            }
        }

        // void insert_non_full(dict_t<T, Y> new_elems, int t){
        //     int i = this->curr_size-1;

        //     if (this->leaf == TRUE){
        //         while((i >= 0) && (new_elems.key < this->mas[i].key)){ 
        //             this->mas[i+1].key = this->mas[i].key;
        //             this->mas[i+1].data = this->mas[i].data;
        //             i--;
        //         }
        //         this->mas[i+1].key = new_elems.key;
        //         this->mas[i+1].data = new_elems.data;
        //         this->curr_size++;
        //     }

        //     else {
        //         while((i >= 0) && (new_elems.key < this->mas[i].key)) i--;

        //         if (this->children[i+1]->curr_size == 2*t-1){ 
        //             this->split_child(i + 1, this->children[i + 1], t);
        //             if (this->mas[i+1].key < new_elems.key) i++;
        //         }
        //         this->children[i+1]->insert_non_full(new_elems, t);
        //     }
        // }

        Node<T, Y>* search(T key){
            int i = 0;
            while ((i < this->curr_size) && (key < this->mas[i].key)) i++;
            if (key == this->mas[i].key)
                return this;
            else if (this->leaf == TRUE)
                return NULL;
            else
                return this->children[i]->search(key);
        }
};

template<class T, class Y>
class Btree_map{
    public:
        Node<T, Y>* root;
        int t;

        Btree_map(int new_rang);
        Btree_map(Btree_map* tree);
        ~Btree_map();

        int is_empty();
        void del_all();
        void insert(T key, Y data);
        dict_t<T, Y> search(T key);

        // void print_tree_rec(Node<T, Y>* node, Node<T, Y>* parent, int level) {
        //     if (node != nullptr) {
        //         for (int i = 0; i < node->curr_size; ++i) {
        //             print_tree_rec(node->children[i], node, level + 1);
        //             for (int j = 0; j < level; ++j) {
        //                 std::cout << "    ";
        //             }
        //             std::cout << " " << node->mas[i].key ;
        //             if (parent != nullptr) {
        //                 std::cout << " (" << parent->mas[0].key << ")" << std::endl;
        //             } else {
        //                 std::cout << " (Root)" << std::endl;
        //             }
        //         }
        //         print_tree_rec(node->children[node->curr_size], node, level + 1);
        //     }
        // }

        // void print_tree() {
        //     if (root != nullptr) {
        //         print_tree_rec(root, nullptr, 0);
        //     } else {
        //         std::cout << "Tree is empty" << std::endl;
        //     }
        // }

        void print_tree_rec(Node<T, Y>* node, int level) {
            if (node != nullptr) {
                std::cout << "lvl " << level << ": ";
                for (int i = 0; i < node->curr_size; ++i) {
                    std::cout << node->mas[i].key << " ";
                }
                std::cout << std::endl;
                for (int i = 0; i <= node->curr_size; ++i) 
                    print_tree_rec(node->children[i], level + 1);
            }
        }

        void print_keys() {
            std::cout << "Keys in the tree:" << std::endl;
            print_tree_rec(root, 0);
        }



};

template<class T, class Y>
Btree_map<T, Y>::Btree_map(int new_rang){
    this->root = new Node<T, Y>(new_rang, TRUE);
    this->t = new_rang;
}

template<class T, class Y>
void Btree_map<T, Y>::insert(T key, Y data){
    dict_t<T, Y> new_elems;
    new_elems.key = key;
    new_elems.data = data;

    if(this->root == NULL){
        this->root = new Node<T, Y>(this->t, TRUE);
        this->root->insert_to_node(new_elems, this->t);
        this->root->curr_size = 1;
    } else {
        Node<T, Y>* curr = this->root;
        if (curr->curr_size == 2*t-1){
            Node<T, Y>* new_root = new Node<T, Y>(this->t, FALSE);

            new_root->children[0] = curr;
            new_root->split_child(0, curr, this->t);

            if (new_root->mas[0].key < key) 
                new_root->children[0]->insert_non_full(new_elems, this->t);
            else new_root->children[1]->insert_non_full(new_elems, this->t);

            this->root = new_root;
        }
        curr->insert_non_full(new_elems, this->t);
    }
}

template<class T, class Y>
dict_t<T, Y> Btree_map<T, Y>::search(T key){
    Node<T, Y>* tmp_node = this->root->search(key);
    if (tmp_node == NULL) 
        return dict_t<T, Y>();

    for (int i = 0; i < tmp_node->curr_size; i++) {
        if (tmp_node->mas[i].key == key)
            return tmp_node->mas[i]; 
    }

    return dict_t<T, Y>();
}

template<class T, class Y>
int Btree_map<T, Y>::is_empty(){
    if (this->root == NULL) return 0;
    return 1;
}

template<typename T, typename Y>
Btree_map<T, Y>::~Btree_map() {}

#define N 18

int main(){

    Btree_map<int, int> tree(3); 
    for (int i = N-1; i < N*2; i++){
        tree.insert(i, i*i);
        tree.print_keys();
        std::cout << std::endl;
    }
    tree.insert(38, 2);
    tree.insert(22, 2);



    // dict_t<int, int> res = tree.search(9);
    // std::cout << " " << res.key <<  " " << res.data << std::endl;
    // tree.print_tree();
    tree.print_keys();
    
    return 0;
}