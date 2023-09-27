#include "setcustomerform.h"
#include "ui_setcustomerform.h"

SetCustomerForm::SetCustomerForm(CustomerList *customerList, QWidget *parent) :
    QDialog(parent), ui(new Ui::SetCustomerForm),
    customerList(customerList)
{
    ui->setupUi(this);
    customerList->setUiSetCustomerForm(ui);
    setValidInput();
    ui->pushButton->setDefault(true);
    connect(ui->pushButton, &QPushButton::clicked, this, &SetCustomerForm::btnOk_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &SetCustomerForm::btnCancel_clicked);
}

SetCustomerForm::~SetCustomerForm()
{
    delete ui;
}

void SetCustomerForm::setValidInput()
{
    ui->lnTotalPaid->setValidator(new QDoubleValidator(0, 100, 2, this));
}

bool SetCustomerForm::isValidInput()
{
    if(
       ui->lnName->text().isEmpty() ||
       ui->lnPhone->text().isEmpty() ||
       ui->lnAddress->text().isEmpty()
            )
        return false;
    return true;
}

void SetCustomerForm::btnOk_clicked()
{
    if(isValidInput())
        this->accept();
    else
    {
        QMessageBox::warning(this, "Invalid Input", "Please fill all the right way");
    }
}


void SetCustomerForm::btnCancel_clicked()
{
    this->close();
}

