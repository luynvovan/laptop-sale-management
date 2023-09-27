#ifndef SETSTAFFFORM_H
#define SETSTAFFFORM_H

#include <QDialog>
#include <QMessageBox>
#include "stafflist.h"

namespace Ui {
class SetStaffForm;
}

class SetStaffForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetStaffForm(StaffList *staffList, QWidget *parent = nullptr);
    ~SetStaffForm();
    void prepareAdd();
    void prepareEdit();
private slots:
    void btnOk_clicked();

    void btnCancel_clicked();

private:
    Ui::SetStaffForm *ui;
    void setValidInput();
    bool isValidInput();
    StaffList *staffList;
    bool isAdding;
};

#endif // SETSTAFFFORM_H
