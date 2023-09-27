#include "supplier.h"

Supplier::Supplier() :
    Person()
{}

Supplier::Supplier(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid) :
    Person(id, name, phoneNumber, completedOrder, totalPaid)
{}

Supplier::Supplier(const Supplier &supplier) :
    Person(supplier)
{}

Supplier &Supplier::operator=(const Supplier &other)
{
    this->Person::operator=(other);
    return *this;
}
void operator<<(Ui::SetSupplierForm *ui, const Supplier &supplier)
{
    ui->groupBox->setTitle(QString("Infomation - ") + "ID(" + QVariant(supplier.getId()).toString() + ")");
    ui->lnName->setText(supplier.getName());
    ui->lnPhone->setText(supplier.getPhoneNumber());
    ui->spinBoxCompleted->setValue(supplier.getCompletedOrder());
    ui->lnTotalPaid->setText(QVariant(supplier.getTotalPaid()).toString());
    if(StaffList::getNowLogin()->getType() == admin)
    {
        ui->spinBoxCompleted->setDisabled(false);
        ui->lnTotalPaid->setDisabled(false);
    }
    else
    {
        ui->spinBoxCompleted->setDisabled(true);
        ui->lnTotalPaid->setDisabled(true);
    }
}
void operator>>(Ui::SetSupplierForm *ui, Supplier &supplier)
{
    supplier.setName(ui->lnName->text());
    supplier.setPhoneNumber(ui->lnPhone->text());
    supplier.setCompletedOrder(ui->spinBoxCompleted->value());
    supplier.setTotalPaid(ui->lnTotalPaid->text().toDouble());
}
void operator<<(Ui::SupplierForm *ui, const Supplier &supplier)
{
    ui->name->setText(supplier.getName());
    ui->phone->setText(supplier.getPhoneNumber());
    ui->completed->setText(QVariant(supplier.getCompletedOrder()).toString());
    ui->paid->setText(QVariant(supplier.getTotalPaid()).toString());
}
