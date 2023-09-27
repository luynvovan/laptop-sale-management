#include "orderdetail.h"

int OrderDetail::getOrderId() const
{
    return orderId;
}

void OrderDetail::setOrderId(int newOrderId)
{
    orderId = newOrderId;
}

void OrderDetail::setLaptopList(LaptopList *laptopList)
{
    OrderDetail::laptopList = laptopList;
}

Node<OrderItem *> *OrderDetail::getHead()
{
    return list.getHead();
}

int OrderDetail::getLength() const
{
    return list.getLength();
}

double OrderDetail::getTotal() const
{
    Node<OrderItem*> *ptr = list.getHead();
    double total{};
    while(ptr != nullptr)
    {
        total += ptr->getData()->getTotal();
        ptr = ptr->getNext();
    }
    return total;
}

OrderDetail::OrderDetail() :
    orderId(-1), list()
{}

OrderDetail::OrderDetail(int orderId) :
    orderId(orderId)
{
}

void OrderDetail::push(OrderItem *orderItem)
{
    list.addFirst(orderItem);
}

OrderDetail::~OrderDetail()
{
    Node<OrderItem*> *ptr = list.getHead();
    while(ptr != nullptr)
    {
        delete ptr->getData();
        ptr = ptr->getNext();
    }
}

LaptopList *OrderDetail::laptopList = nullptr;

bool OrderDetail::add(int itemId, int quantity)
{
    Node<OrderItem*> *ptr = list.getHead();
    Laptop *item = laptopList->at(itemId);
    bool alreadyExist{false};
    while(ptr != nullptr)
    {
        if(ptr->getData()->getItemId() == itemId)
        {
            alreadyExist = true;
            break;
        }
        ptr = ptr->getNext();
    }
    if(alreadyExist)
    {
        if(ptr->getData()->getQuantity() + quantity > item->getQuantity())
            return false;
        ptr->getData()->setQuantity(ptr->getData()->getQuantity() + quantity);
    }
    else
    {
        if(quantity > item->getQuantity())
            return false;
        list.addFirst(new OrderItem(this->orderId, itemId, quantity, item->getPrice(), item->getDiscount()));
    }
    return true;
}

void OrderDetail::add(int itemId, int quantity, double price)
{
    Node<OrderItem*> *ptr = list.getHead();
    bool alreadyExist{false};
    while(ptr != nullptr)
    {
        if(ptr->getData()->getItemId() == itemId)
        {
            alreadyExist = true;
            break;
        }
        ptr = ptr->getNext();
    }
    if(alreadyExist)
    {
        ptr->getData()->setQuantity(ptr->getData()->getQuantity() + quantity);
    }
    else
    {
        list.addFirst(new OrderItem(this->orderId, itemId, quantity, price, 0));
    }
}

void OrderDetail::remove(int itemId)
{
    Node<OrderItem*> *ptr = list.getHead();
    int idx{};
    while(ptr != nullptr)
    {
        if(ptr->getData()->getItemId() == itemId)
        {
            break;
        }
        ptr = ptr->getNext();
        ++idx;
    }
    list.remove(idx);
}

bool OrderDetail::setQuantity(int itemId, int quantity)
{
    if(quantity <= 0)
    {
        remove(itemId);
        return true;
    }
    Node<OrderItem*> *ptr = list.getHead();
    Laptop *item = laptopList->at(itemId);
    while(ptr != nullptr)
    {
        if(ptr->getData()->getItemId() == itemId)
        {
            break;
        }
        ptr = ptr->getNext();
    }
    if(ptr->getData()->getQuantity() + quantity > item->getQuantity())
        return false;
    ptr->getData()->setQuantity(ptr->getData()->getQuantity() + quantity);
    return true;
}

void OrderDetail::setQuantity(int itemId, int quantity, double price)
{
    Node<OrderItem*> *ptr = list.getHead();
    while(ptr != nullptr)
    {
        if(ptr->getData()->getItemId() == itemId)
        {
            break;
        }
        ptr = ptr->getNext();
    }
    ptr->getData()->setQuantity(quantity);
    ptr->getData()->setPrice(price);
}
