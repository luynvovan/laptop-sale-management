#ifndef SETCUSTOMERFORM_H
#define SETCUSTOMERFORM_H

#include <QDialog>
#include "customerlist.h"
#include <QMessageBox>

namespace Ui {
class SetCustomerForm;
}

class SetCustomerForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetCustomerForm(CustomerList *customerList, QWidget *parent = nullptr);
    ~SetCustomerForm();

private slots:
    void btnOk_clicked();

    void btnCancel_clicked();

private:
    Ui::SetCustomerForm *ui;
    CustomerList *customerList;
    void setValidInput();
    bool isValidInput();
};

#endif // SETCUSTOMERFORM_H
