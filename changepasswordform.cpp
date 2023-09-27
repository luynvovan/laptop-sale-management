#include "changepasswordform.h"
#include "ui_changepasswordform.h"
#include <QMessageBox>

ChangePasswordForm::ChangePasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordForm)
{
    ui->setupUi(this);
    connect(ui->btnOk, &QPushButton::clicked, this, &ChangePasswordForm::holdBtnOkClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &ChangePasswordForm::holdBtnCancelClicked);
}

ChangePasswordForm::~ChangePasswordForm()
{
    delete ui;
}

void ChangePasswordForm::holdBtnOkClicked()
{
    if(StaffList::changePassword(ui->lnPassword->text(), ui->lnNewPassword->text(), ui->lnReNewPassword->text()))
    {
        ui->lnPassword->clear();
        ui->lnNewPassword->clear();
        ui->lnReNewPassword->clear();
        this->accept();
    }
    else
    {
        QMessageBox::warning(this, "Can't change password!", "Incorrect information, please try again");
    }
}

void ChangePasswordForm::holdBtnCancelClicked()
{
    ui->lnPassword->clear();
    ui->lnNewPassword->clear();
    ui->lnReNewPassword->clear();
    this->close();
}

void ChangePasswordForm::closeEvent(QCloseEvent *event)
{
    holdBtnCancelClicked();
    event->accept();
}
