#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "person.h"
#include "ui_supplierform.h"
#include "ui_setsupplierform.h"
#include "stafflist.h"

class Supplier : public Person
{
public:
    Supplier();
    Supplier(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid);
    Supplier(const Supplier &supplier);
    Supplier &operator=(const Supplier &other);
    friend void operator<<(Ui::SetSupplierForm *ui, const Supplier &supplier);
    friend void operator>>(Ui::SetSupplierForm *ui, Supplier &supplier);
    friend void operator<<(Ui::SupplierForm *ui, const Supplier &supplier);
};

#endif // SUPPLIER_H
