#ifndef LAPTOP_H
#define LAPTOP_H

#include "item.h"
#include "ui_setlaptopform.h"
#include "ui_laptopform.h"
#include <QFile>
#include "stafflist.h"

class Laptop : public Item
{
private:
    QString screenSize;
    QString cpu;
    QString ram;
    QString ssd;
    QString hdd;
    QString weight;
public:
    Laptop();
    Laptop(const Laptop &laptop);
    Laptop(int itemId, const QString &name, QString brand, double price, int discount, int quantity, int sold, const QString &imagePath, const QString &screenSize, const QString &cpu, const QString &ram, const QString &ssd, const QString &hdd, const QString &weight);
    Laptop &operator=(const Laptop &other);
    const QString &getScreenSize() const;
    void setScreenSize(const QString &newScreenSize);
    const QString &getCpu() const;
    void setCpu(const QString &newCpu);
    const QString &getRam() const;
    void setRam(const QString &newRam);
    const QString &getSsd() const;
    void setSsd(const QString &newSsd);
    const QString &getHdd() const;
    void setHdd(const QString &newHdd);
    const QString &getWeight() const;
    void setWeight(const QString &newWeight);
    friend void operator<<(Ui::SetLaptopForm *ui, const Laptop &laptop);
    friend void operator>>(Ui::SetLaptopForm *ui, Laptop &laptop);
    friend void operator<<(Ui::LaptopForm *ui, const Laptop &laptop);
};

#endif // LAPTOP_H
