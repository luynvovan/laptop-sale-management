#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include "stafflist.h"
#include <QMessageBox>

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(StaffList *staffList, QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void btnLogin_clicked();
    void btnCancel_clicked();
private:
    Ui::LoginForm *ui;
    StaffList *staffList;
};

#endif // LOGINFORM_H
