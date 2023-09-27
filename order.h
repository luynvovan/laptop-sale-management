#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include "customerlist.h"
#include "stafflist.h"
#include "laptoplist.h"
#include "supplierlist.h"
#include "orderdetaillist.h"
#include <QDateTime.h>

enum OrderStatus
{
    preparing, delivering, completed, canceled
};

enum OrderType
{
    salesOrder, purchaseOrder
};

class Order
{
protected:
    int id;
    OrderType type;
    int staffId;
    int customerId; // customer or supplier id
    double totalPrice;
    QString orderDay;
    QString completedDay;
    OrderStatus status;
    QString phone;

    static CustomerList *customerList;
    static StaffList *staffList;
    static LaptopList *laptopList;
    static SupplierList *supplierList;
    static OrderDetailList *orderDetailList;
public:
    Order(int id, OrderType type, int staffId, int customerId, const QString &phone);
    Order(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone);
    virtual ~Order();
    virtual void setOrder(OrderDetail *orderDetail) = 0;
    virtual void setDelivering() = 0;
    virtual void setCompleted() = 0;
    virtual void setCanceled() = 0;
    static void setCustomerList(CustomerList *newCustomerList);
    static void setStaffList(StaffList *newStaffList);
    static void setLaptopList(LaptopList *newLaptopList);
    static void setSupplierList(SupplierList *newSupplierList);
    static void setOrderDetailList(OrderDetailList *newOrderDetailList);
    int getId() const;
    void setId(int newId);
    OrderType getType() const;
    void setType(OrderType newType);
    int getStaffId() const;
    void setStaffId(int newStaffId);
    int getCustomerId() const;
    void setCustomerId(int newCustomerId);
    double getTotalPrice() const;
    void setTotalPrice(double newTotalPrice);
    const QString &getOrderDay() const;
    void setOrderDay(const QString &newOrderDay);
    const QString &getCompletedDay() const;
    void setCompletedDay(const QString &newCompletedDay);
    OrderStatus getStatus() const;
    void setStatus(OrderStatus newStatus);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    OrderDetail *getOrderDetail() const;
    QString getCustomerName() const;
    QString getStaffName() const;
    double getTotalBef() const;
};

#endif // ORDER_H
