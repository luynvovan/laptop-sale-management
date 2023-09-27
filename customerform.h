#ifndef CUSTOMERFORM_H
#define CUSTOMERFORM_H

#include <QDialog>
#include "setcustomerform.h"

namespace Ui {
class CustomerForm;
}

class CustomerForm : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerForm(CustomerList *customerList, QWidget *parent = nullptr);
    ~CustomerForm();
    void showThis();
private slots:
    void btnAdd_clicked();

    void btnEdit_clicked();

    void btnSearch_clicked();

    void btnDelete_clicked();

    void listCustomer_cellClicked(int row, int column);

private:
    Ui::CustomerForm *ui;
    CustomerList *customerList;
    SetCustomerForm *setCustomerForm;
    void clearDetail();
    bool temp;
signals:
    void sendCustomerId(int id, int type = 0);
public slots:
    void goDelete(int id, bool stat);
};

#endif // CUSTOMERFORM_H
