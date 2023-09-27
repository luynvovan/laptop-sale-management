#ifndef ORDERITEM_H
#define ORDERITEM_H
#include "laptoplist.h"

class OrderItem
{
private:
    int orderId;
    int itemId;
    int quantity;
    double price; // 1 item's price
    int discount;
    double total;
    void computeTotal();
    static LaptopList *laptopList;
public:
    OrderItem();
    OrderItem(int orderId, int itemId, int quantity, double price, int discount);
    int getOrderId() const;
    void setOrderId(int newOrderId);
    int getItemId() const;
    void setItemId(int newItemId);
    int getQuantity() const;
    void setQuantity(int newQuantity);
    double getPrice() const;
    void setPrice(double newPrice);
    int getDiscount() const;
    void setDiscount(int newDiscount);
    double getTotal() const;
    static void setLaptopList(LaptopList *newLaptopList);
    QString getItemName() const;
    QString getItemBrand() const;
};

#endif // ORDERITEM_H
