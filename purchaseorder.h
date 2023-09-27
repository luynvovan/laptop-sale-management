#ifndef PURCHASEORDER_H
#define PURCHASEORDER_H

#include "order.h"

class PurchaseOrder: public Order
{
private:

public:
    PurchaseOrder(int id, int staffId, int customerId, const QString &phone);
    PurchaseOrder(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone);
    virtual ~PurchaseOrder();
    virtual void setOrder(OrderDetail *orderDetail);
    virtual void setDelivering();
    virtual void setCompleted();
    virtual void setCanceled();
};

#endif // PURCHASEORDER_H
