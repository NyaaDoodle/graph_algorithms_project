#pragma once
#include "exception.h"
template<class T> class LinkedList {
public:
    class LinkedNode {
    private:
        T val;
        LinkedNode *next;
        LinkedNode(const T& val, LinkedNode * const next = nullptr) : val(val), next(next) {}
        friend class LinkedList;
    };
    LinkedList() = default;
    LinkedList(const LinkedList& ll) {
        for (T t : ll) {
            push_tail(t);
        }
    }
    LinkedList& operator=(const LinkedList& ll) {
        if (&ll != this) {
            while (!is_empty()) {
                pop_head();
            }
            for (T t : ll) {
                push_tail(t);
            }
        }
        return *this;
    }
    ~LinkedList() {
        while (!is_empty()) {
            pop_head();
        }
    }
    bool is_empty() const { return (head == nullptr && tail == nullptr); }
    void pop_head() {
        if (is_empty()) { throw EmptyListException(); }
        LinkedNode* temp = head;
        head = head->next;
        if (head == nullptr) { tail = nullptr; }
        delete temp;
    }
    void push_tail(const T& t) {
        LinkedNode *new_node = new LinkedNode(t);
        if (is_empty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    T peek_head() const {
        if (is_empty()) { throw EmptyListException(); }
        return head->val;
    }
    T peek_tail() const {
        if (is_empty()) { throw EmptyListException(); }
        return tail->val;
    }
    bool search(const T& val) const {
        LinkedNode *curr = head;
        while (curr != nullptr) {
            if (curr->val == val) { return true; }
            curr = curr->next;
        }
        return false;
    }
    void search_and_delete(const T& val) {
        if (is_empty()) { throw EmptyListException(); }
        LinkedNode *prev_found = search_prev(val);
        if (prev_found == nullptr) { pop_head(); return; }
        if (prev_found != tail) {
            LinkedNode *temp = prev_found->next;
            prev_found->next = prev_found->next->next;
            if (temp == tail) {
                tail = prev_found->next;
            }
            delete temp;
        }
        else {
            throw ItemNotFound();
        }
    }
    class iterator {
    public:
        iterator(LinkedNode * const node = nullptr) : node(node) {}
        iterator operator++() {
            node = node->next;
            return *this;
        }
        bool operator!=(iterator itr) const {
            return node != itr.node;
        }
        T operator*() const {
            return node->val;
        }
    private:
        LinkedNode *node;
        friend class LinkedList;
    };
    iterator begin() const { return head; }
    iterator end() const { return nullptr; }
private:
    LinkedNode *head = nullptr;
    LinkedNode *tail = nullptr;
    LinkedNode* search_prev(const T& val) const {
        LinkedNode *curr = head;
        LinkedNode *prev = nullptr;
        bool found = false;
        while (curr != nullptr) {
            if (curr->val == val) { found = true; }
            if (!found) {
                prev = curr;
            }
            curr = curr->next;
        }
        return prev;
    }
};
