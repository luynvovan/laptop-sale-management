#ifndef SUPPLIERLIST_H
#define SUPPLIERLIST_H

#include "ilist.h"
#include "queue.h"
#include "supplier.h"
#include "ui_setorderform.h"

class SupplierList: public IList
{
private:
    HashTable<Supplier*, 100> list;
    Supplier *justForAdd;
    Queue<int> deletedId;
    Ui::SupplierForm *uiSupplierForm;
    Ui::SetSupplierForm *uiSetSupplierForm;
    Ui::SetOrderForm *uiSetOrderForm;

    static int takeKey(Supplier* const &supplier);
    static bool isEqual(Supplier* const &l, Supplier* const &r);

public:
    SupplierList();
    virtual ~SupplierList();
    void setUiSupplierForm(Ui::SupplierForm *newUiSupplierForm);
    void setUiSetSupplierForm(Ui::SetSupplierForm *newUiSetSupplierForm);
    virtual void add();
    virtual void showList();
    virtual void showDetail(int id);
    virtual void set(int id);
    virtual void remove(int id);
    virtual int getCount();
    Supplier *at(int id);
    void prepareAdd();
    void fillEdit(int id);
    Supplier *getJustForAdd() const;
    void setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm);
    void fillOrderSupplierComboBox();
    void fillOrderSupplierInfo(int id);
    virtual void load();
    virtual void save();
};

#endif // SUPPLIERLIST_H
