#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;

public:
    Node(const T &data)
        : data{data}, next{nullptr} {}

    ~Node() {}

    T &getData()
    {
        return data;
    }

    void setData(const T &data)
    {
        this->data = data;
    }

    Node<T> *getNext() const
    {
        return next;
    }

    void setNext(Node<T> *node)
    {
        this->next = node;
    }
};

#endif
