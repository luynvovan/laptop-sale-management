#include "orderitem.h"

LaptopList *OrderItem::laptopList{nullptr};

int OrderItem::getOrderId() const
{
    return orderId;
}

void OrderItem::setOrderId(int newOrderId)
{
    orderId = newOrderId;
}

int OrderItem::getItemId() const
{
    return itemId;
}

void OrderItem::setItemId(int newItemId)
{
    itemId = newItemId;
}

int OrderItem::getQuantity() const
{
    return quantity;
}

void OrderItem::setQuantity(int newQuantity)
{
    quantity = newQuantity;
    computeTotal();
}

double OrderItem::getPrice() const
{
    return price;
}

void OrderItem::setPrice(double newPrice)
{
    price = newPrice;
    computeTotal();
}

int OrderItem::getDiscount() const
{
    return discount;
}

void OrderItem::setDiscount(int newDiscount)
{
    discount = newDiscount;
    computeTotal();
}

double OrderItem::getTotal() const
{
    return total;
}

void OrderItem::computeTotal()
{
    total = price * double(quantity) - price * double(quantity) * discount / 100.0;
}

void OrderItem::setLaptopList(LaptopList *newLaptopList)
{
    laptopList = newLaptopList;
}

QString OrderItem::getItemName() const
{
    return laptopList->at(itemId)->getName();
}

QString OrderItem::getItemBrand() const
{
    return laptopList->at(itemId)->getBrand();
}

OrderItem::OrderItem() :
    OrderItem(-1, -1, 0, 0.0, 0)
{
    computeTotal();
}

OrderItem::OrderItem(int orderId, int itemId, int quantity, double price, int discount) :
    orderId(orderId),
    itemId(itemId),
    quantity(quantity),
    price(price),
    discount(discount),
    total()
{
    computeTotal();
}
