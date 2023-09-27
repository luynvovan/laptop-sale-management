#ifndef ORDERLIST_H
#define ORDERLIST_H

#include "ilist.h"
#include "purchaseorder.h"
#include "salesorder.h"
#include "ui_setorderform.h"

class OrderList: public IList
{
private:
    HashTable<Order*, 97> list;
    OrderDetailList *orderDetailList;
    Queue<int> deletedId;
    static int takeKey(Order* const &order);
    static bool isEqual(Order* const &l, Order* const &r);

    Ui::SetOrderForm *uiSetOrderForm;
public:
    OrderDetail *orderDetail;
    OrderList(CustomerList *customerList, StaffList *staffList, LaptopList *laptopList, SupplierList *supplierList);
    virtual ~OrderList();
    virtual void add();
    virtual void showList();
    virtual void showDetail(int id);
    virtual void set(int id);
    virtual int getCount();
    virtual void remove(int id);
    Order *at(int id);
    void setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm);
    void prepareAdd();
    bool setDelivering(int id);
    bool setCompleted(int id);
    bool setCanceled(int id);
    virtual void load();
    virtual void save();
    Node<Order*> *getHeadAtIdx(int id);
    int getLength();
    bool isExist(int id, int type);//0 - customer, 1 - supplier, 2 - staff, 3 - laptop
};

#endif // ORDERLIST_H
