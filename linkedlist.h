#pragma once
template<class T> class LinkedList {
public:
    class LinkedNode {
    public:
        LinkedNode(const T t, const LinkedNode *next = nullptr) : t(t), next(next) {}
    private:
        T t;
        LinkedNode *next;
        friend class LinkedList;
    };
private:
    
};
