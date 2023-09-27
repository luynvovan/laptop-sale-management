#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "node.h"

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int length;

public:
    LinkedList()
        : head{nullptr}, length{} {}

    ~LinkedList()
    {
        Node<T> *ptr{head};
        while (ptr != nullptr)
        {
            ptr = ptr->getNext();
            delete head;
            head = ptr;
        }
    }

    Node<T> *getHead() const
    {
        return head;
    }

    void add(const T &data, const int &idx)
    {
        if (idx == 0)
        {
            addFirst(data);
            return;
        }
        if (idx == length)
        {
            addLast(data);
            return;
        }
        int i{1};
        Node<T> *ptr{head};
        while (i != idx)
        {
            ptr = ptr->getNext();
            ++i;
        }
        Node<T> *insert = new Node<T>(data);
        insert->setNext(ptr->getNext());
        ptr->setNext(insert);
        ++length;
    }

    void addFirst(const T &data)
    {
        Node<T> *node = new Node<T>(data);
        node->setNext(head);
        head = node;
        ++length;
    }

    void addLast(const T &data)
    {
        if (head == nullptr)
        {
            addFirst(data);
            return;
        }
        else
        {
            Node<T> *ptr{head};
            while (ptr->getNext() != nullptr)
                ptr = ptr->getNext();
            ptr->setNext(new Node<T>(data));
            ++length;
        }
    }

    void removeFirst()
    {
        if (head != nullptr)
        {
            Node<T> *ptr{head};
            head = head->getNext();
            delete ptr;
            --length;
        }
    }

    void removeLast()
    {
        if (head != nullptr)
        {
            if (length == 1)
            {
                removeFirst();
                return;
            }
            Node<T> *ptr{head};
            while (ptr->getNext()->getNext() != nullptr)
                ptr = ptr->getNext();
            delete ptr->getNext();
            ptr->setNext(nullptr);
            --length;
        }
    }

    void remove(const int &idx)
    {
        if (idx == 0)
        {
            removeFirst();
            return;
        }
        if (idx == length - 1)
        {
            removeLast();
            return;
        }
        int i{1};
        Node<T> *ptr{head};
        while (i != idx)
        {
            ptr = ptr->getNext();
            ++i;
        }
        Node<T> *del = ptr->getNext();
        ptr->setNext(del->getNext());
        delete del;
    }

    T &operator[](const int &index) const
    {
        Node<T> *ptr{head};
        int i{0};
        while (i != index && ptr != nullptr)
        {
            ++i;
            ptr = ptr->getNext();
        }
        return ptr->getData();
    }

    int getLength() const
    {
        return length;
    }

    void swap(const int &l, const int &r)
    {
        Node<T> *ptrL{head};
        int i{};
        while (i != l)
        {
            ptrL = ptrL->getNext();
            ++i;
        }
        Node<T> *ptrR{ptrL};
        while (i != r)
        {
            ptrR = ptrR->getNext();
            ++i;
        }
        T tmp{ptrL->getData()};
        ptrL->setData(ptrR->getData());
        ptrR->setData(tmp);
    }
};

#endif
