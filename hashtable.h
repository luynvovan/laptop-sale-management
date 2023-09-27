#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "linkedlist.h"

template <typename T, int N>
class HashTable
{
private:
    const int length{N};
    LinkedList<T> *hashTable[N];
    int count;
    T returnThisIfNotFound; // return this if not found in operator[]
    int (*takeKey)(const T &data);
    bool (*isEqual)(const T &l, const T &r);
    int hashFunc(const int &key)
    {
        return key % N;
    }
public:
    HashTable(int (*takeKey)(const T &data), bool (*isEqual)(const T &l, const T &r))
        : takeKey{takeKey}, count{}, returnThisIfNotFound{}, isEqual(isEqual)
    {
        for (int i{}; i != length; ++i)
            hashTable[i] = new LinkedList<T>();
    }

    ~HashTable()
    {
        for (int i{}; i != length; ++i)
            delete hashTable[i];
    }

    int getCount() const
    {
        return count;
    }

    void add(const T &data)
    {
        const int idx = hashFunc((*takeKey)(data));
        bool alreadyExist{false};
        Node<T> *headIdx = hashTable[idx]->getHead();
        while (headIdx != nullptr)
        {
            if ((*isEqual)(headIdx->getData(), data))
            {
                alreadyExist = true;
                break;
            }
            headIdx = headIdx->getNext();
        }
        if (!alreadyExist)
        {
            hashTable[idx]->addFirst(data);
            ++count;
        }
    }

    T &operator[](const int &key)// return the first elment that have "key", if !found return returnThisIfNotFound
    {
        const int idx = hashFunc(key);
        Node<T> *headIdx = hashTable[idx]->getHead();
        while (headIdx != nullptr)
        {
            if ((*takeKey)(headIdx->getData()) == key)
            {
                return headIdx->getData();
            }
            headIdx = headIdx->getNext();
        }
        return returnThisIfNotFound;
    }

    int getLength() const
    {
        return length;
    }

    Node<T> *getHeadatIdx(const int &idx) const
    {
        return hashTable[idx]->getHead();
    }

    void remove(const T &elm)
    {
        const int idx = hashFunc((*takeKey)(elm));
        Node<T> *headIdx = hashTable[idx]->getHead();
        int idxLinkedList{};
        while (headIdx != nullptr)
        {
            if ((*isEqual)(headIdx->getData(), elm))
            {
                hashTable[idx]->remove(idxLinkedList);
                break;
            }
            ++idxLinkedList;
            headIdx = headIdx->getNext();
        }
        --count;
    }

    void remove(const int &key) // remove the first elm that have that key
    {
        int idxLinkedList{};
        Node<T> *rev = hashTable[hashFunc(key)]->getHead();
        while((*takeKey)(rev->getData()) != key)
        {
            rev = rev->getNext();
            ++idxLinkedList;
        }
        hashTable[hashFunc(key)]->remove(idxLinkedList);
        --count;
    }

    bool isExist(const T &elm)
    {
        const int idx = hashFunc((*takeKey)(elm));
        Node<T> *headIdx = hashTable[idx]->getHead();
        while (headIdx != nullptr)
        {
            if ((*isEqual)(headIdx->getData(), elm))
            {
                return true;
            }
            headIdx = headIdx->getNext();
        }
        return false;
    }
};

#endif
