#include "customer.h"

Gender Customer::getGender() const
{
    return gender;
}

void Customer::setGender(Gender newGender)
{
    gender = newGender;
}

int Customer::getAge() const
{
    return age;
}

void Customer::setAge(int newAge)
{
    age = newAge;
}

const QString &Customer::getAddress() const
{
    return address;
}

void Customer::setAddress(const QString &newAddress)
{
    address = newAddress;
}

int Customer::getPoint() const
{
    return point;
}

void Customer::setPoint(int newPoint)
{
    point = newPoint;
}

Customer::Customer(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid, Gender gender, int age, const QString &address, int point) :
    Person(id, name, phoneNumber, completedOrder, totalPaid),
    gender(gender),
    age(age),
    address(address),
    point(point)
{}

Customer::Customer(const Customer &customer) :
    Person(customer),
    gender(customer.gender),
    age(customer.age),
    address(customer.address),
    point(customer.point)
{}

Customer::Customer() :
    Person(),
    gender(female),
    age(0),
    address(""),
    point(0)
{}

Customer &Customer::operator=(const Customer &other)
{
    this->Person::operator=(other);
    this->gender = other.gender;
    this->age = other.age;
    this->address = other.address;
    this->point = other.point;
    return *this;
}

void operator<<(Ui::SetCustomerForm *ui, const Customer &customer)
{
    ui->groupBox->setTitle(QString("Infomation - ") + "ID(" + QVariant(customer.getId()).toString() + ")");
    ui->lnName->setText(customer.getName());
    ui->cbBoxGender->setCurrentIndex(customer.gender);
    ui->spinBoxAge->setValue(customer.age);
    ui->lnPhone->setText(customer.getPhoneNumber());
    ui->lnAddress->setText(customer.address);
    ui->spinBoxCompleted->setValue(customer.getCompletedOrder());
    ui->lnTotalPaid->setText(QVariant(customer.getTotalPaid()).toString());
    ui->spinBoxPoint->setValue(customer.point);
    if(StaffList::getNowLogin()->getType() == admin)
    {
        ui->spinBoxCompleted->setDisabled(false);
        ui->lnTotalPaid->setDisabled(false);
        ui->spinBoxPoint->setDisabled(false);
    }
    else
    {
        ui->spinBoxCompleted->setDisabled(true);
        ui->lnTotalPaid->setDisabled(true);
        ui->spinBoxPoint->setDisabled(true);
    }
}
void operator>>(Ui::SetCustomerForm *ui, Customer &customer)
{
    customer.setName(ui->lnName->text());
    customer.setGender(ui->cbBoxGender->currentText() == "Male" ? male : female);
    customer.setAge(ui->spinBoxAge->value());
    customer.setPhoneNumber(ui->lnPhone->text());
    customer.setAddress(ui->lnAddress->text());
    customer.setCompletedOrder(ui->spinBoxCompleted->value());
    customer.setTotalPaid(ui->lnTotalPaid->text().toDouble());
    customer.setPoint(ui->spinBoxPoint->value());
}
void operator<<(Ui::CustomerForm *ui, const Customer &customer)
{
    ui->name->setText(customer.getName());
    ui->gender->setText(customer.gender == male ? "Male" : "Female");
    ui->age->setText(QVariant(customer.age).toString());
    ui->phone->setText(customer.getPhoneNumber());
    ui->address->setText(customer.address);
    ui->completed->setText(QVariant(customer.getCompletedOrder()).toString());
    ui->totalPaid->setText(QVariant(customer.getTotalPaid()).toString());
    ui->point->setText(QVariant(customer.point).toString());
}
