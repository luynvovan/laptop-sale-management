#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include "orderitem.h"
#include "laptoplist.h"

class OrderDetail
{
private:
    int orderId;
    LinkedList<OrderItem*> list;
    static LaptopList *laptopList;
public:
    OrderDetail();
    OrderDetail(int orderId);
    void push(OrderItem *orderItem); //use to load from file
    ~OrderDetail();
    bool add(int itemId, int quantity);
    void add(int itemId, int quantity, double price);
    void remove(int itemId);
    bool setQuantity(int itemId, int quantity);
    void setQuantity(int itemId, int quantity, double price);
    int getOrderId() const;
    void setOrderId(int newOrderId);
    static void setLaptopList(LaptopList *laptopList);
    Node<OrderItem*> *getHead();
    int getLength() const;
    double getTotal() const;
};

#endif // ORDERDETAIL_H
