#ifndef MYSTRINGLIST_H
#define MYSTRINGLIST_H

#include "node.h"
#include <QString>

class MyStringList
{
private:
    Node<QString> *head;
    QString trash;
    int length;
public:
    MyStringList() :
        head(nullptr), length(0)
    {}
    void setString(const QString &line)
    {
        Node<QString> *ptr{nullptr};
        int size = line.size();
        int left{}, right{};
        {
            while(right != size && line[right] != ',')
            {
                ++right;
            }
            int n{right - left};
            QChar buff[n + 1];
            for(int i{}; i != n; ++i)
            {
                buff[i] = line[i + left];
            }
            buff[n] = '\0';
            ptr = new Node<QString>(QString(buff));
            ++length;
            if(right == size)
            {
                head = ptr;
                return;
            }
            left = ++right;
        }
        head = ptr;
        while(right < size)
        {
            if(line[right] == ',')
            {
                int n{right - left};
                QChar buff[n + 1];
                for(int i{}; i != n; ++i)
                {
                    buff[i] = line[i + left];
                }
                left = ++right;
                buff[n] = '\0';
                ptr->setNext(new Node<QString>(QString(buff)));
                ++length;
                ptr = ptr->getNext();
                continue;
            }
            ++right;
        }
        int n{right - left};
        QChar buff[n + 1];
        for(int i{}; i != n; ++i)
        {
            buff[i] = line[i + left];
        }
        buff[n] = '\0';
        ptr->setNext(new Node<QString>(QString(buff)));
        ++length;
    }
    ~MyStringList()
    {
        Node<QString> *ptr = head;
        while(ptr != nullptr)
        {
            head = ptr;
            ptr = ptr->getNext();
            delete head;
        }
    }
    QString &operator[](int idx)
    {
        Node<QString> *ptr = head;
        int i = 0;
        while(ptr != nullptr)
        {
            if(i == idx)
            {
                return ptr->getData();
            }
            ptr = ptr->getNext();
            ++i;
        }
        return trash;
    }
    const int &getSize() const
    {
        return length;
    }
};

#endif // MYSTRINGLIST_H
