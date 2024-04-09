#include <iostream>
#include <functional>
#include <stdexcept>

template<class T, class Y>
struct qwerty {
    T key;
    Y data;
};

template<class T, class Y>
using dict_t = qwerty<T, Y>;

template<class T, class Y>
class Node {
public:
    T key;
    dict_t<T, Y> val;
    Node<T, Y>* next;

    Node() {
        next = nullptr;
    }

    void add(dict_t<T,Y> new_el) {
        val = new_el;
    }

};

template<class T, class Y>
class list_map {
public:
    Node<T, Y>* first;
    Node<T, Y>* last;
    int size;
    // int h_key;

    list_map() {
        first = nullptr;
        last = nullptr;
        size = 0;
        // h_key = 0;
    }

    ~list_map() {
        Node<T, Y>* current = first;
        while (current != nullptr) {
            Node<T, Y>* next = current->next;
            delete current;
            current = next;
        }
    }

     int insert(T key, Y data, int h_key) {
        Node<T, Y>* new_node = new Node<T, Y>();
        // int h_key = key;
        dict_t<T, Y> new_el;
        // this->key = h_key;
        new_el.key = key;
        new_el.data = data;
        new_node->add(new_el);
        new_node->key = h_key;
        
        if (first == nullptr) {
            first = new_node;
            last = new_node;
            size++;
            return 1;
        }

        Node<T, Y>* current = first;
        while (current->next != nullptr && current->key != h_key) {
            current = current->next;
        }

        if (current->key == h_key) {
            current->add(new_el);
            current->key = h_key;
            size++;
            return 0;
        } else {
            last->next = new_node;
            last = new_node;
            size++;
            return 0;
        }
    }

    int del_val(T key) {
        Node<T, Y>* curr = first;
        Node<T, Y>* prev = nullptr;

        if (curr != nullptr && key == curr->key) {
            first = curr->next;
            delete curr;
            size--;
            return 0;
        }

        while (curr != nullptr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != nullptr) {
            prev->next = curr->next;
            delete curr;
            size--;
            return 0;
        } else {
            return 1;
        }
    }

    void clear() {
        Node<T, Y>* curr = first;
        while (curr != nullptr) {
            Node<T, Y>* temp = curr;
            curr = curr->next;
            delete temp;
        }
        first = nullptr;
        size = 0;
    }



    int get_size() {return size;}

    dict_t<T, Y>& operator[](T key) {
        Node<T, Y>* curr = first;

        while (curr != nullptr && curr->key != key)
            curr = curr->next;

        if (curr != nullptr && curr->key == key)
            return curr->val;
        else
            throw std::out_of_range("Ключ не найден");
    }

};

