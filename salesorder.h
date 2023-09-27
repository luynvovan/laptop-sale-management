#ifndef SALESORDER_H
#define SALESORDER_H

#include "order.h"

class SalesOrder: public Order
{
private:
    int discount;
    int usedPoint;
    bool usePoint;
    QString address;
public:
    SalesOrder(int id, int staffId, int customerId, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address);
    SalesOrder(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address);
    virtual ~SalesOrder();
    virtual void setOrder(OrderDetail *orderDetail);
    virtual void setDelivering();
    virtual void setCompleted();
    virtual void setCanceled();
    int getDiscount() const;
    void setDiscount(int newDiscount);
    int getUsedPoint() const;
    void setUsedPoint(int newUsedPoint);
    const QString &getAddress() const;
    void setAddress(const QString &newAddress);
    bool getUsePoint() const;
};

#endif // SALESORDER_H
