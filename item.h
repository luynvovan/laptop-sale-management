#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
private:
    int itemId;
    QString name;
    QString brand;
    double price;
    int discount;
    int quantity;
    int sold;
    QString imagePath;
public:
    Item(int itemId, const QString &name, QString brand, double price, int discount, int quantity, int sold, const QString &imagePath);
    Item();
    Item(const Item &item);
    Item &operator=(const Item &other);
    int getItemId() const;
    void setItemId(int newItemId);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getBrand() const;
    void setBrand(const QString &newBrand);
    double getPrice() const;
    void setPrice(double newPrice);
    double getDiscount() const;
    void setDiscount(double newDiscount);
    int getQuantity() const;
    void setQuantity(int newQuantity);
    int getSold() const;
    void setSold(int newSold);
    const QString &getImagePath() const;
    void setImagePath(const QString &newImagePath);
};

#endif // ITEM_H
