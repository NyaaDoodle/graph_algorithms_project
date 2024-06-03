#pragma once
#include "exception.h"
template<class T> class LinkedList {
public:
    LinkedList() = default;
    LinkedList(const LinkedList& ll) = delete;
    LinkedList& operator=(const LinkedList& ll) = delete;
    ~LinkedList() {
        while (!(is_empty())) {
            pop_head();
        }
    }
    bool is_empty() const { return (head == nullptr && tail == nullptr); }
    void pop_head() {
        if (is_empty()) { throw EmptyListException(); }
        LinkedList* temp = head;
        head = head->next;
        if (head == nullptr) { tail = nullptr; }
        delete temp;
    }
    void push_tail(const T& t) {
        LinkedList *new_node = new LinkedList(t);
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
private:
    struct LinkedNode {
        const T val;
        LinkedNode *next;
        LinkedNode(const T& val, const LinkedNode *next = nullptr) : val(val), next(next) {}
    };
    LinkedNode *head = nullptr;
    LinkedNode *tail = nullptr;
};
