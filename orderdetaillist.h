#ifndef ORDERDETAILLIST_H
#define ORDERDETAILLIST_H

#include "orderdetail.h"
#include "hashtable.h"

class OrderDetailList
{
private:
    HashTable<OrderDetail*, 100> list;
public:
    OrderDetailList(LaptopList *laptopList);
    ~OrderDetailList();
    static int takeKey(OrderDetail* const &orderDetail);
    static bool isEqual(OrderDetail* const &l, OrderDetail* const &r);
    void add(OrderDetail *oD);
    void remove(int orderId);
    OrderDetail *at(int orderId);
    void save();
    void load();
    bool isContainItem(int id);
};

#endif // ORDERDETAILLIST_H
