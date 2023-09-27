#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QDialog>
#include "stafflist.h"
#include <QCloseEvent>

namespace Ui {
class ChangePasswordForm;
}

class ChangePasswordForm : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordForm(QWidget *parent = nullptr);
    ~ChangePasswordForm();

private:
    Ui::ChangePasswordForm *ui;
private slots:
    void holdBtnOkClicked();
    void holdBtnCancelClicked();
    void closeEvent(QCloseEvent *event) override;
};

#endif // CHANGEPASSWORDFORM_H
