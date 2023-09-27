#ifndef STAFFFORM_H
#define STAFFFORM_H

#include <QDialog>
#include "setstaffform.h"

namespace Ui {
class StaffForm;
}

class StaffForm : public QDialog
{
    Q_OBJECT

public:
    explicit StaffForm(StaffList *staffList, QWidget *parent = nullptr);
    ~StaffForm();
    void showThis();
private slots:
    void btnSearch_clicked();
    void btnAdd_clicked();
    void btnEdit_clicked();
    void btnDelete_clicked();

    void listStaff_cellClicked(int row, int column);

private:
    Ui::StaffForm *ui;
    SetStaffForm *setStaffForm;
    StaffList *staffList;
    void clearDetail();
signals:
    void sendStaffId(int id, int type = 2);
public slots:
    void goDelete(int id, bool stat);
};

#endif // STAFFFORM_H
