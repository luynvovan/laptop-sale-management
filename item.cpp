#include "item.h"

int Item::getItemId() const
{
    return itemId;
}

void Item::setItemId(int newItemId)
{
    itemId = newItemId;
}

const QString &Item::getName() const
{
    return name;
}

void Item::setName(const QString &newName)
{
    name = newName;
}

const QString &Item::getBrand() const
{
    return brand;
}

void Item::setBrand(const QString &newBrand)
{
    brand = newBrand;
}

double Item::getPrice() const
{
    return price;
}

void Item::setPrice(double newPrice)
{
    price = newPrice;
}

double Item::getDiscount() const
{
    return discount;
}

void Item::setDiscount(double newDiscount)
{
    discount = newDiscount;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::setQuantity(int newQuantity)
{
    quantity = newQuantity;
}

int Item::getSold() const
{
    return sold;
}

void Item::setSold(int newSold)
{
    sold = newSold;
}

const QString &Item::getImagePath() const
{
    return imagePath;
}

void Item::setImagePath(const QString &newImagePath)
{
    imagePath = newImagePath;
}

Item::Item(int itemId, const QString &name, QString brand, double price, int discount, int quantity, int sold, const QString &imagePath) :
    itemId(itemId),
    name(name),
    brand(brand),
    price(price),
    discount(discount),
    quantity(quantity),
    sold(sold),
    imagePath(imagePath)
{}

Item::Item() :
    Item(-1, "", "", 0.0, 0, 0, 0, "")
{}

Item::Item(const Item &item) :
    Item(item.itemId, item.name, item.brand, item.price, item.discount, item.quantity, item.sold, item.imagePath)
{}

Item &Item::operator=(const Item &other)
{
    this->itemId = other.itemId;
    this->name = other.name;
    this->brand = other.brand;
    this->price = other.price;
    this->discount = other.discount;
    this->quantity = other.quantity;
    this->sold = other.sold;
    this->imagePath = other.imagePath;
    return *this;
}
