#include "salesorder.h"
#include "date.h"

int SalesOrder::getDiscount() const
{
    return discount;
}

void SalesOrder::setDiscount(int newDiscount)
{
    discount = newDiscount;
}

int SalesOrder::getUsedPoint() const
{
    return usedPoint;
}

void SalesOrder::setUsedPoint(int newUsedPoint)
{
    usedPoint = newUsedPoint;
}

const QString &SalesOrder::getAddress() const
{
    return address;
}

void SalesOrder::setAddress(const QString &newAddress)
{
    address = newAddress;
}

bool SalesOrder::getUsePoint() const
{
    return usePoint;
}

SalesOrder::SalesOrder(int id, int staffId, int customerId, const QString &phone, int discount, int usedPoint ,bool usePoint, const QString &address) :
    Order(id, salesOrder, staffId, customerId, phone),
    discount(discount),
    usedPoint(usedPoint),
    usePoint(usePoint),
    address(address)
{}

SalesOrder::SalesOrder(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address):
    Order(id, type, staffId, customerId, totalPrice, orderDay, completedDay, status, phone),
    discount(discount),
    usedPoint(usedPoint),
    usePoint(usePoint),
    address(address)
{

}

SalesOrder::~SalesOrder()
{

}

void SalesOrder::setOrder(OrderDetail *orderDetail)
{
    totalPrice = 0;
    Node<OrderItem*> *ptr = orderDetail->getHead();
    OrderItem *orderItem{};
    Laptop *item{};
    while(ptr != nullptr)
    {
        totalPrice += ptr->getData()->getTotal();
        orderItem = ptr->getData();
        item = laptopList->at(orderItem->getItemId());
        item->setQuantity(item->getQuantity() - orderItem->getQuantity());
        ptr = ptr->getNext();
    }
    totalPrice -= totalPrice * double(discount) / 100.0;
    if(usePoint)
    {
        double point = double(customerList->at(customerId)->getPoint());
        if(point > totalPrice)
        {
            customerList->at(customerId)->setPoint(int(double(point) - totalPrice));
            usedPoint = totalPrice;
            totalPrice = 0;
        }
        else
        {
            customerList->at(customerId)->setPoint(0);
            totalPrice -= point;
            usedPoint = point;
        }
    }
    orderDay = Date::getCurrentDate();
    status = preparing;
    orderDetailList->add(orderDetail);
}

void SalesOrder::setDelivering()
{
    status = delivering;
}

void SalesOrder::setCompleted()
{
    status = completed;
    Customer *customer{customerList->at(customerId)};
    Staff *staff{staffList->at(staffId)};
    customer->setCompletedOrder(customer->getCompletedOrder() + 1);
    customer->setTotalPaid(customer->getTotalPaid() + totalPrice);
    customer->setPoint(customer->getPoint() + int(totalPrice * 5.0 / 100.0));
    staff->setCompletedOrder(staff->getCompletedOrder() + 1);
    staff->setTotalPaid(staff->getTotalPaid() + totalPrice);
    completedDay = Date::getCurrentDate();
}

void SalesOrder::setCanceled()
{
    Node<OrderItem*> *ptr = orderDetailList->at(id)->getHead();
    OrderItem *orderItem{};
    Laptop *item{};
    while(ptr != nullptr)
    {
        orderItem = ptr->getData();
        item = laptopList->at(orderItem->getItemId());
        item->setQuantity(item->getQuantity() + orderItem->getQuantity());
        ptr = ptr->getNext();
    }
    Customer *customer{customerList->at(customerId)};
    customer->setPoint(customer->getPoint() + usedPoint);
    status = canceled;
    completedDay = Date::getCurrentDate();
}
