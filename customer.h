#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include "ui_setcustomerform.h"
#include "ui_customerform.h"
#include "stafflist.h"

class Customer : public Person
{
private:
    Gender gender;
    int age;
    QString address;
    int point;
public:
    Customer(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid, Gender gender, int age, const QString &address, int point);
    Customer(const Customer &customer);
    Customer();
    Customer &operator=(const Customer &other);
    Gender getGender() const;
    void setGender(Gender newGender);
    int getAge() const;
    void setAge(int newAge);
    const QString &getAddress() const;
    void setAddress(const QString &newAddress);
    int getPoint() const;
    void setPoint(int newPoint);
    friend void operator<<(Ui::SetCustomerForm *ui, const Customer &customer);
    friend void operator>>(Ui::SetCustomerForm *ui, Customer &customer);
    friend void operator<<(Ui::CustomerForm *ui, const Customer &customer);
};

#endif // CUSTOMER_H
