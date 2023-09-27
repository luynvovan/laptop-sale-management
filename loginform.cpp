#include "loginform.h"
#include "./ui_loginform.h"

LoginForm::LoginForm(StaffList *staffList, QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginForm),
    staffList(staffList)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginForm::btnLogin_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &LoginForm::btnCancel_clicked);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::btnLogin_clicked()
{
    staffList->login(ui->lnUserName->text().trimmed(), ui->lnPassword->text().trimmed());
    if(StaffList::getNowLogin() != nullptr)
    {
        ui->lnPassword->clear();
        this->accept();
    }
    else
    {
        QMessageBox::warning(this, "Login info invalid!", "User name or password is incorrect");
    }
}


void LoginForm::btnCancel_clicked()
{
    this->close();
}
