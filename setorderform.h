#ifndef SETORDERFORM_H
#define SETORDERFORM_H

#include <QDialog>
#include "orderlist.h"
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class SetOrderForm;
}

class SetOrderForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetOrderForm(LaptopList *laptopList, CustomerList *customerList, SupplierList *supplierList, OrderList *orderList, QWidget *parent = nullptr);
    ~SetOrderForm();
    void changeToSalesOrder();
    void changeToPurchaseOrder();

private slots:

    void btnAdd_clicked();

    void cbBoxItem_activated(int index);

    void btnDelete_clicked();

    void cbBoxCustomer_activated(int index);

    void cboxUsePoint_stateChanged(int arg1);

    void btnCancel_clicked();

    void btnOk_clicked();

    void spinBoxDiscount_valueChanged(int arg1);

private:
    Ui::SetOrderForm *ui;
    OrderList *orderList;
    LaptopList *laptopList;
    CustomerList *customerList;
    SupplierList *supplierList;
    void computeLastPrice();
    void clearDetail();
    void closeEvent(QCloseEvent *event) override;
};

#endif // SETORDERFORM_H
