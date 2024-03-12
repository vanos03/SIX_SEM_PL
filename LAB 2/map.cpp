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
                int height;

                Node(T key, Y data){
                    this->key = key;
                    this->data = data;
                    this->left = NULL;
                    this->right = NULL;
                    this->height = 1;
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
         int get_height(Node<T>* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int get_balance_fcktr(Node<T>* node) {
        if (node == NULL) return 0;
        return get_height(node->left) - get_height(node->right);
    }

    Node<T>* rotate_right(Node<T>* y) {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(get_height(y->left), get_height(y->right)) + 1;
        x->height = std::max(get_height(x->left), get_height(x->right)) + 1;

        return x;
    }

    Node<T>* rotate_left(Node<T>* x) {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(get_height(x->left), get_height(x->right)) + 1;
        y->height = std::max(get_height(y->left), get_height(y->right)) + 1;

        return y;
    }

    Node<T>* insert_node(Node<T>* node, T key, Y data) {
        if (node == NULL) return new Node<T>(key, data);

        if (key < node->key)
            node->left = insert_node(node->left, key, data);
        else if (key > node->key)
            node->right = insert_node(node->right, key, data);

        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        int balance = get_balance_fcktr(node);

        if (balance > 1 && key < node->left->key)
            return rotate_right(node);

        if (balance < -1 && key > node->right->key)
            return rotate_left(node);

        if (balance > 1 && key > node->left->key) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }

    public:
        Node<T>* root;

        Map(){root = NULL;}
        Map(const Map& a){this->root = clone(a.root);}
         
        void insert(T key, Y data) {this->root = insert_node(root, key, data);}

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

        int height_helper(Node<T>* node) {
            if (node == nullptr) return 0;
            
            int left_height = height_helper(node->left);
            int right_height = height_helper(node->right);

            return std::max(left_height, right_height) + 1;
        }

        int get_height(){
            return height_helper(this->root);
        }

        void print_tree(Node<T>* node, int level = 0, char prefix = ' ') {
            if (node != nullptr) {
                print_tree(node->right, level + 1, '/');
                std::cout << std::string(level * 4, ' ') << prefix << node->key << std::endl;
                print_tree(node->left, level + 1, '\\');
            }
        }

        void del_all(){this->root = NULL;}
        ~Map(){this->root = NULL;}
};


#define N 20

int main(){
    Map<int, double> test;
    // for (int i = 1; i < N; i++)
    //     test.insert(i, (double)i/5);

    test.insert(2, 5);
    test.insert(4, 5);
    test.insert(3, 5);
 

     

    test.print_tree(test.root);

     int a = 11;
    if (test.search(a) == NULL) {
        std::cout << a << " not exist" << std::endl;
    } else {
        std::cout << a << " is exist" << std::endl;
    }

    std::cout << "get date by key: " << test.get_date(a) << std::endl;
    std::cout << "height: " << test.get_height() << std::endl;

    test.del_all();
    if (test.search(a) == NULL) {
        std::cout << a << " not exist" << std::endl;
    } else {
        std::cout << a << " is exist" << std::endl;
    }

    return 0;
}