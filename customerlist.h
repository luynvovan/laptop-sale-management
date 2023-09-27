#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include "ilist.h"
#include "queue.h"
#include "customer.h"
#include "ui_setorderform.h"

class CustomerList : public IList
{
private:
    HashTable<Customer*, 100> list;
    Ui::CustomerForm *uiCustomerForm;
    Ui::SetCustomerForm *uiSetCustomerForm;
    Ui::SetOrderForm *uiSetOrderForm;
    Customer *justForAdd;
    Queue<int> deletedId;

    static int takeKey(Customer* const &customer);
    static bool isEqual(Customer* const &l, Customer* const &r);
public:
    CustomerList();
    virtual ~CustomerList();
    virtual void add();
    virtual void showList();
    virtual void showDetail(int id);
    virtual void set(int id);
    virtual int getCount();
    virtual void remove(int id);
    Customer *at(int id);
    void fillEdit(int id);
    void prepareAdd();
    void setUiCustomerForm(Ui::CustomerForm *newUiCustomerForm);
    void setUiSetCustomerForm(Ui::SetCustomerForm *newUiSetCustomerForm);
    Customer *getJustForAdd() const;
    void setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm);
    void fillOrderCustomerComboBox();
    void fillOrderCustomerInfor(int id);
    virtual void load();
    virtual void save();
};

#endif // CUSTOMERLIST_H
