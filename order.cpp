#include "order.h"

CustomerList *Order::customerList = nullptr;
StaffList *Order::staffList = nullptr;
LaptopList *Order::laptopList = nullptr;
SupplierList *Order::supplierList = nullptr;
OrderDetailList *Order::orderDetailList = nullptr;

void Order::setCustomerList(CustomerList *newCustomerList)
{
    customerList = newCustomerList;
}

void Order::setStaffList(StaffList *newStaffList)
{
    staffList = newStaffList;
}

void Order::setLaptopList(LaptopList *newLaptopList)
{
    laptopList = newLaptopList;
}

void Order::setSupplierList(SupplierList *newSupplierList)
{
    supplierList = newSupplierList;
}

void Order::setOrderDetailList(OrderDetailList *newOrderDetailList)
{
    orderDetailList = newOrderDetailList;
}

int Order::getId() const
{
    return id;
}

void Order::setId(int newId)
{
    id = newId;
}

OrderType Order::getType() const
{
    return type;
}

void Order::setType(OrderType newType)
{
    type = newType;
}

int Order::getStaffId() const
{
    return staffId;
}

void Order::setStaffId(int newStaffId)
{
    staffId = newStaffId;
}

int Order::getCustomerId() const
{
    return customerId;
}

void Order::setCustomerId(int newCustomerId)
{
    customerId = newCustomerId;
}

double Order::getTotalPrice() const
{
    return totalPrice;
}

void Order::setTotalPrice(double newTotalPrice)
{
    totalPrice = newTotalPrice;
}

const QString &Order::getOrderDay() const
{
    return orderDay;
}

void Order::setOrderDay(const QString &newOrderDay)
{
    orderDay = newOrderDay;
}

const QString &Order::getCompletedDay() const
{
    return completedDay;
}

void Order::setCompletedDay(const QString &newCompletedDay)
{
    completedDay = newCompletedDay;
}

OrderStatus Order::getStatus() const
{
    return status;
}

void Order::setStatus(OrderStatus newStatus)
{
    status = newStatus;
}

const QString &Order::getPhone() const
{
    return phone;
}

void Order::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

OrderDetail *Order::getOrderDetail() const
{
    return orderDetailList->at(id);
}

QString Order::getCustomerName() const
{
    if(type == salesOrder)
        return customerList->at(customerId)->getName();
    return supplierList->at(customerId)->getName();
}

QString Order::getStaffName() const
{
    return staffList->at(staffId)->getName();
}

double Order::getTotalBef() const
{
    return Order::orderDetailList->at(this->id)->getTotal();
}

Order::~Order()
{

}

Order::Order(int id, OrderType type, int staffId, int customerId, const QString &phone) :
    id(id),
    type(type),
    staffId(staffId),
    customerId(customerId),
    totalPrice(),
    orderDay(),
    completedDay("---"),
    status(preparing),
    phone(phone)
{}

Order::Order(int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone) : id(id),
    type(type),
    staffId(staffId),
    customerId(customerId),
    totalPrice(totalPrice),
    orderDay(orderDay),
    completedDay(completedDay),
    status(status),
    phone(phone)
{}
