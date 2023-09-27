#include "setsupplierform.h"
#include "ui_setsupplierform.h"

SetSupplierForm::SetSupplierForm(SupplierList *supplierList, QWidget *parent) :
    QDialog(parent), ui(new Ui::SetSupplierForm),
    supplierList(supplierList)
{
    ui->setupUi(this);
    supplierList->setUiSetSupplierForm(ui);
    setValidInput();

    connect(ui->btnOk, &QPushButton::clicked, this, &SetSupplierForm::btnOk_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &SetSupplierForm::btnCancel_clicked);
}

SetSupplierForm::~SetSupplierForm()
{
    delete ui;
}

void SetSupplierForm::btnOk_clicked()
{
    if(isValidInput())
        this->accept();
    else
        QMessageBox::warning(this, "Invalid input", "Please fill in all the right way");
}


void SetSupplierForm::btnCancel_clicked()
{
    this->close();
}

void SetSupplierForm::setValidInput()
{
    ui->lnTotalPaid->setValidator(new QDoubleValidator(0, 100, 2, this));
}

bool SetSupplierForm::isValidInput()
{
    if(
        ui->lnName->text().isEmpty() ||
        ui->lnPhone->text().isEmpty() ||
        ui->lnTotalPaid->text().isEmpty()
            )
        return false;
    return true;
}

