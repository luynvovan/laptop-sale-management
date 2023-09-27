#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "linkedlist.h"

template<typename T>
class Queue
{
private:
    LinkedList<T> *queue;
public:
    Queue() :
        queue(new LinkedList<T>)
    {}
    ~Queue()
    {
        delete queue;
    }
    T front() const
    {
        return (*queue)[0];
    }
    T back() const
    {
        return (*queue)[queue->getLength() - 1];
    }
    void push(const T &elm)
    {
        int idx{};
        Node<T> *ptr = queue->getHead();
        while(idx != queue->getLength() && elm > ptr->getData())
        {
            ++idx;
            ptr = ptr->getNext();
        }
        queue->add(elm, idx);
    }
    void pop()
    {
        queue->removeFirst();
    }
    int getLength() const
    {
        return queue->getLength();
    }
    bool isEmpty() const
    {
        return queue->getLength() == 0;
    }
};

#endif // QUEUE_H
