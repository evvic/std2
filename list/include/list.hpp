#ifndef LIST_HPP
#define LIST_HPP

#include "../../std2/std2.hpp" // for std2::move, std2::forward
#include "../../memory/memory.hpp" // for std2::unique_ptr

namespace std2 {

    template <typename T>
    class list {
    public:
        struct Node;      // Forward declaration of Node
        struct iterator;  // Forward declaration of iterator

        list() {
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
        }

        ~list() {
            iterator it = begin();
            // while (it.m_node) {

            // }
        }

        iterator begin() {
            return iterator(m_head);
        }

        iterator end() {
            return iterator(nullptr);
        }


        void push_back(T element) {
            Node* new_node = new Node(element);
            new_node->prev = m_tail;
            new_node->next = nullptr;
            if (m_tail) m_tail->next = new_node;
            m_tail = new_node;
            if (!m_head) m_head = m_tail;
            m_size++;
        }

        void push_front(T element) {
            Node* new_node = new Node(element);
            new_node->next = m_head;
            new_node->prev = nullptr;
            if (m_head) m_head->prev = new_node;
            m_head = new_node;
            if (!m_tail) m_tail = m_head;
            m_size++;
        }

        void insert(iterator& it, T element) {
            add_node(it, element);
        }

        iterator erase(iterator& it) {
            
        }

        void pop_back() {

        }

        void pop_front() {

        }

        
        std::size_t size() {
            return m_size;
        }

        struct Node {
            T data;
            Node* next;
            Node* prev;
            Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        };

        struct iterator {
        public:
            explicit iterator(Node* node) : m_node(node) {}
            T& operator*() const { return m_node->data; }
            // pre-incrementer: incrments this and returns current value
            iterator& operator++() {
                if(m_node) m_node = m_node->next;
                return *this;
            }
            // post-incrementer: incrments this and returns the un-incremented value
            iterator operator++(int) {
                iterator temp = *this;
                if(m_node) m_node = m_node->next;
                return temp;
            }
            bool operator==(const iterator& other) const { return m_node == other.m_node; }
            bool operator!=(const iterator& other) const { return m_node != other.m_node; }

            Node* m_node;
        };
    private:

        // position == 0 is front of head, position == m_size is behind tail
        bool add_node(iterator it, T element) {
            if (m_size > 0 && !it.m_node) return false;

            if (!it.m_node) push_back(element);
            else if (it.m_node == m_head) push_front(element);
            // else if (it.m_node == m_tail) push_back(element);
            else {
                Node* new_node = new Node(element);
                new_node->next = it.m_node;
                new_node->prev = it.m_node->prev;
                if (it.m_node->prev) it.m_node->prev->next = new_node;
                it.m_node->prev = new_node;
                m_size++;
            }
            return true;

        }

        Node* m_head = nullptr;
        Node* m_tail = nullptr;
        std::size_t m_size = 0;
    };


}

#endif // LIST_HPP