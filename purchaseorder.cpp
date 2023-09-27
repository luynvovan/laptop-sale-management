#include "purchaseorder.h"
#include "date.h"

PurchaseOrder::PurchaseOrder(int id, int staffId, int customerId, const QString &phone) :
    Order(id, purchaseOrder, staffId, customerId, phone)
{}

PurchaseOrder::PurchaseOrder(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone) :
    Order(id, type, staffId, customerId, totalPrice, orderDay, completedDay, status, phone)
{

}

PurchaseOrder::~PurchaseOrder()
{

}

void PurchaseOrder::setOrder(OrderDetail *orderDetail)
{
    totalPrice = 0;
    Node<OrderItem*> *ptr = orderDetail->getHead();
    while(ptr != nullptr)
    {
        totalPrice += ptr->getData()->getTotal();
        ptr = ptr->getNext();
    }
    orderDay = Date::getCurrentDate();
    orderDetailList->add(orderDetail);
}

void PurchaseOrder::setDelivering()
{
    status = delivering;
}

void PurchaseOrder::setCompleted()
{
    status = completed;
    Node<OrderItem*> *ptr = orderDetailList->at(id)->getHead();
    OrderItem *orderItem{};
    Laptop *item{};
    while(ptr != nullptr)
    {
        orderItem = ptr->getData();
        item = laptopList->at(orderItem->getItemId());
        item->setQuantity(orderItem->getQuantity() + item->getQuantity());
        ptr = ptr->getNext();
    }
    completedDay = Date::getCurrentDate();
    Staff *staff{staffList->at(staffId)};
    Supplier *supplier{supplierList->at(customerId)};
    staff->setCompletedOrder(staff->getCompletedOrder() + 1);
    staff->setTotalPaid(staff->getTotalPaid() + totalPrice);
    supplier->setCompletedOrder(supplier->getCompletedOrder() + 1);
    supplier->setTotalPaid(supplier->getTotalPaid() + totalPrice);
}

void PurchaseOrder::setCanceled()
{
    status = canceled;
    completedDay = Date::getCurrentDate();
}
