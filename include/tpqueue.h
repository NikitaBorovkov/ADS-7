// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
 private:
    struct ITEM {
        T value;
        ITEM* next;
        ITEM* prev;
    };
    TPQueue::ITEM* create(const T&);
    ITEM* tail;
    ITEM* head;
 public:
    TPQueue():head(nullptr), tail(nullptr) {}
    void push(const T&);
    T pop();
};

struct SYM {
  char ch;
  int prior;
};

template<typename T>
typename TPQueue<T>::ITEM* TPQueue<T>::create(const T& value) {
    ITEM* item = new ITEM;
    item->value = value;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}

template < typename T >
void TPQueue <T>::push(const T& value) {
    ITEM* temp = head;
    ITEM* item = create(value);
    while (temp && temp->value.prior >= value.prior) {
        temp = temp->next;
    }
    if (!temp && head) {
        tail->next = item;
        item->prev = tail;
        tail = item;
    } else if (!temp && !head) {
        head = tail = item;
    } else if (!temp->prev) {
        head->prev = item;
        item->next = head;
        head = item;
    } else {
        temp->prev->next = item;
        item->prev = temp->prev;
        item->next = temp;
        temp->prev = item;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    if (head && tail) {
        ITEM* temp = head->next;
        if (temp) {
            temp->prev = nullptr;
        }
        T value = head->value;
        delete head;
        head = temp;
        if (!head) {
            tail = nullptr;
        }
        return value;
    } else {
        throw std::string("Empty!");
    }
}

#endif  // INCLUDE_TPQUEUE_H_
