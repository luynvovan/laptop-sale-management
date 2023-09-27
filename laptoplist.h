#ifndef LAPTOPLIST_H
#define LAPTOPLIST_H

#include "ilist.h"
#include "laptop.h"
#include "queue.h"
#include <QTableWidgetItem>
#include "ui_setorderform.h"

class LaptopList : public IList
{
private:
    HashTable<Laptop*, 100> list;
    HashTable<QString, 10> brandList;
    Ui::SetLaptopForm *uiSetLaptopForm;
    Ui::LaptopForm *uiLaptopForm;
    Ui::SetOrderForm *uiSetOrderForm;
    Laptop *justForAdd;
    Queue<int> deletedId;

    static int takeKey(Laptop* const &laptop);
    static int takeKeyBrand(const QString &brand);
    static bool isEqual(Laptop* const &l, Laptop* const &r);
    static bool isEqualBrand(const QString &l, const QString &r);
public:
    LaptopList();
    virtual ~LaptopList();
    virtual void add();
    virtual void showList();
    virtual void showDetail(int id);
    virtual void set(int id);
    virtual int getCount();
    virtual void remove(int id);
    void fillEdit(int id);
    void prepareAdd();
    void setSetLaptopForm(Ui::SetLaptopForm *newUiSetLaptopForm);
    void setLaptopForm(Ui::LaptopForm *newUiLaptopForm);
    Laptop *at(int id);
    Laptop *getJustForAdd() const;
    void setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm);
    void fillOrderItemComboBox();
    void fillOrderItemDetail(int id);
    virtual void load();
    virtual void save();
};

#endif // LAPTOPLIST_H
