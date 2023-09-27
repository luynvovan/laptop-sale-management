#include "setstaffform.h"
#include "ui_setstaffform.h"

SetStaffForm::SetStaffForm(StaffList *staffList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetStaffForm),
    staffList(staffList),
    isAdding(false)
{
    ui->setupUi(this);
    setValidInput();
    staffList->setUiSetStaffForm(ui);
    ui->btnOk->setDefault(true);
    connect(ui->btnOk, &QPushButton::clicked, this, &SetStaffForm::btnOk_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &SetStaffForm::btnCancel_clicked);
}

SetStaffForm::~SetStaffForm()
{
    delete ui;
}

void SetStaffForm::prepareAdd()
{
    isAdding = true;
    ui->lnUsername->setDisabled(false);
}

void SetStaffForm::prepareEdit()
{
    isAdding = false;
    ui->lnUsername->setDisabled(true);
}

void SetStaffForm::setValidInput()
{
    ui->lnPaid->setValidator(new QDoubleValidator(0, 100, 2, this));
}

bool SetStaffForm::isValidInput()
{
    if( ui->lnName->text().isEmpty() ||
        ui->lnPhone->text().isEmpty() ||
        ui->lnPaid->text().isEmpty() ||
        ui->lnUsername->text().isEmpty() ||
        ui->lnPassword->text().isEmpty() ||
        ui->lnAddress->text().isEmpty())
        return false;
    return true;
}

void SetStaffForm::btnOk_clicked()
{
    if((isAdding && staffList->isUsedUserName(ui->lnUsername->text())))
    {
        QMessageBox::warning(this, "Used user name", "Please use another user name");
    }
    else if(isValidInput())
    {
        this->accept();
    }
    else
    {
        QMessageBox::warning(this, "Invalid input", "Please fill all in the right way");
    }
}


void SetStaffForm::btnCancel_clicked()
{
    this->close();
}

