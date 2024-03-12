
#ifndef MAP_H
#define MAP_H

template<class T>
class Map{
    private:
    template<class U>
        class Node{
            public:
                T key;
                T data;
                Node* left;
                Node* right;

                Node(T key, T data){}
        };

        int height(Node<T>* node){}
        void left_rotate(Node<T>*& node){}
        void right_rotate(Node<T>*& node){}

        void balance(Node<T>*& node){}

    public:
        Node<T>* root;

        Map(){}
        Map(const Map& a){}

        void insert(T key, T data); 
        void search(T key); 
        void del(T key);

        ~Map(){}
};

#endif