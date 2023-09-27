#ifndef SUPPLIERFORM_H
#define SUPPLIERFORM_H

#include <QDialog>
#include "setsupplierform.h"

namespace Ui {
class SupplierForm;
}

class SupplierForm : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierForm(SupplierList *supplierList, QWidget *parent = nullptr);
    ~SupplierForm();
    void showThis();
private slots:
    void btnSearch_clicked();

    void btnAdd_clicked();

    void btnEdit_clicked();

    void btnDelete_clicked();

    void listSupplier_cellClicked(int row, int column);

private:
    Ui::SupplierForm *ui;
    SupplierList *supplierList;
    SetSupplierForm *setSupplierForm;
    void clearDetail();
signals:
    void sendSupplierId(int id, int type = 1);
public slots:
    void goDelete(int id, bool stat);
};

#endif // SUPPLIERFORM_H
