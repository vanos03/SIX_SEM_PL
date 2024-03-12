#include <iostream>

#define TRUE 1


template<class T, class Y>
class Map{
    private:
    template<class U>
        class Node{
            public:
                T key;
                Y data;
                Node<T>* left;
                Node<T>* right;

                Node(T key, Y data){
                    this->key = key;
                    this->data = data;
                    this->left = NULL;
                    this->right = NULL;
                }
        };

        Node<T>* clone(const Node<T>* node) {
            if (node == NULL) return NULL;

            Node<T>* new_node = new Node<T>(node->key, node->data);
            new_node->left = clone(node->left);
            new_node->right = clone(node->right);
            return new_node;
        }

        int height(Node<T>* node){
            if (node == NULL) return 0;
            return 1 + std::max(height(node->left), height(node->right));
        }
        void left_rotate(Node<T>*& node){
            Node<T>* tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            node = tmp;
        }
        void right_rotate(Node<T>*& node){
            Node<T>* tmp = node->left;
            node->right = tmp->right;
            tmp->right = node;
            node = tmp;
        }

        void balance(Node<T>*& node){
            if(node != NULL){
                if ((height(node->right) - height(node->left)) > 1){
                    if(height(node->right->right) >= height(node->right->left)){
                        left_rotate(node);
                    } else {
                        right_rotate(node->right);
                        left_rotate(node);
                    }
                }
                if ((height(node->right) - height(node->left)) < -1){
                    if(height(node->left->left) >= height(node->left->right)){
                        right_rotate(node);
                    } else {
                        left_rotate(node->left);
                        right_rotate(node);
                    }
                }
            }
        }

    public:
        Node<T>* root;

        Map(){root = NULL;}
        Map(const Map& a){this->root = clone(a.root);}

        void insert(T key, Y data){
            Node<T>* new_el = new Node<T>(key, data);

            if (this->root == NULL){ 
                this->root = new_el;
            } else{
                Node<T>* curr = this->root;
                Node<T>* parent = NULL;

                while(TRUE){
                    parent = curr;
                    if (key < curr->key){
                        curr = curr->left;
                        if(curr == NULL){
                            parent->left = new_el;
                            break;
                        }
                    } else{
                        curr = curr->right;
                        if(curr == NULL){
                            parent->right = new_el;
                            break;
                        }
                    }
                }
            }
            balance(new_el);
        } 

        Node<T>* search(T key){
            Node<T>* curr = this->root;
            while(curr!=NULL){
                if(curr->key == key) {
                    return curr;
                } else if (key < curr->key){
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }
            return NULL;
        } 

        int is_empty(){
            if (this->root == NULL) return 0;
            if (this->root != NULL) return 1;
        }
        Y get_date(T key){
            if (search(key) != NULL) {
                return search(key)->data;
            } else {
                return NULL;
            }
        }

        void del_all(){this->root = NULL;}
        


        ~Map(){this->root = NULL;}
};


#define N 100

int main(){
    Map<int, double> test;
    for (int i = 1; i < N; i++)
        test.insert(i, (double)i/5);

    int a = 11;
    if (test.search(a) == NULL) {
        std::cout << a << " not exist" << std::endl;
    } else {
        std::cout << a << " is exist" << std::endl;
    }

    std::cout << "get date by key: " << test.get_date(a) << std::endl;

    test.del_all();
    if (test.search(a) == NULL) {
        std::cout << a << " not exist" << std::endl;
    } else {
        std::cout << a << " is exist" << std::endl;
    }

    return 0;
}