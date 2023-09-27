#include "staff.h"

const QString &Staff::getLoginName() const
{
    return loginName;
}

void Staff::setLoginName(const QString &newLoginName)
{
    loginName = newLoginName;
}

const QString &Staff::getPassword() const
{
    return password;
}

void Staff::setPassword(const QString &newPassword)
{
    password = newPassword;
}

UserType Staff::getType() const
{
    return type;
}

void Staff::setType(UserType newType)
{
    type = newType;
}

Gender Staff::getGender() const
{
    return gender;
}

void Staff::setGender(Gender newGender)
{
    gender = newGender;
}

int Staff::getAge() const
{
    return age;
}

void Staff::setAge(int newAge)
{
    age = newAge;
}

const QString &Staff::getAddress() const
{
    return address;
}

void Staff::setAddress(const QString &newAddress)
{
    address = newAddress;
}

Staff::Staff() :
    Person(),
    loginName(""),
    password(""),
    type(staff),
    gender(female),
    age(-1),
    address("")
{}

Staff::Staff(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid, const QString &loginName, const QString &password, UserType type, Gender gender, int age, const QString &address) :
    Person(id, name, phoneNumber, completedOrder, totalPaid),
    loginName(loginName),
    password(password),
    type(type),
    gender(gender),
    age(age),
    address(address)
{}

Staff::Staff(const Staff &staff) :
    Person(staff),
    loginName(staff.loginName),
    password(staff.password),
    type(staff.type),
    gender(staff.gender),
    age(staff.age),
    address(staff.address)
{}

Staff &Staff::operator=(const Staff &other)
{
    this->Person::operator=(other);
    this->loginName = other.loginName;
    this->password = other.password;
    this->type = other.type;
    this->gender = other.gender;
    this->age = other.age;
    this->address = other.address;
    return *this;
}

void operator<<(Ui::SetStaffForm *ui, const Staff &staff)
{
    ui->groupBox->setTitle(QString("Infomation - ") + "ID(" + QVariant(staff.getId()).toString() + ")");
    ui->lnName->setText(staff.getName());
    ui->lnPhone->setText(staff.getPhoneNumber());
    ui->spinBoxCompleted->setValue(staff.getCompletedOrder());
    ui->lnPaid->setText(QVariant(staff.getTotalPaid()).toString());
    ui->lnUsername->setText(staff.loginName);
    ui->lnPassword->setText(staff.password);
    ui->cbBoxType->setCurrentIndex(staff.type);
    ui->cbBoxGender->setCurrentIndex(staff.gender);
    ui->spinBoxAge->setValue(staff.age);
    ui->lnAddress->setText(staff.address);
}
void operator>>(Ui::SetStaffForm *ui, Staff &staff)
{
    staff.setName(ui->lnName->text());
    staff.setPhoneNumber(ui->lnPhone->text());
    staff.setCompletedOrder(ui->spinBoxCompleted->value());
    staff.setTotalPaid(ui->lnPaid->text().toDouble());
    staff.loginName = ui->lnUsername->text();
    staff.password = ui->lnPassword->text();
    staff.type = ui->cbBoxType->currentText() == "Admin" ? UserType::admin : UserType::staff;
    staff.gender = ui->cbBoxGender->currentText() == "Male" ? male : female;
    staff.age = ui->spinBoxAge->value();
    staff.address = ui->lnAddress->text();
}
void operator<<(Ui::StaffForm *ui, const Staff &staff)
{
    ui->name->setText(staff.getName());
    ui->phone->setText(staff.getPhoneNumber());
    ui->completed->setText(QVariant(staff.getCompletedOrder()).toString());
    ui->paid->setText(QVariant(staff.getTotalPaid()).toString());
    ui->username->setText(staff.loginName);
    ui->usertype->setText(staff.type == admin ? "Admin" : "Staff");
    ui->gender->setText(staff.gender == male ? "Male" : "Female");
    ui->age->setText(QVariant(staff.age).toString());
    ui->address->setText(staff.address);
}
