#ifndef SETSUPPLIERFORM_H
#define SETSUPPLIERFORM_H

#include <QDialog>
#include "supplierlist.h"
#include <QMessageBox>

namespace Ui {
class SetSupplierForm;
}

class SetSupplierForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetSupplierForm(SupplierList *supplierList, QWidget *parent = nullptr);
    ~SetSupplierForm();

private slots:
    void btnOk_clicked();

    void btnCancel_clicked();

private:
    Ui::SetSupplierForm *ui;
    SupplierList *supplierList;
    void setValidInput();
    bool isValidInput();
};

#endif // SETSUPPLIERFORM_H
