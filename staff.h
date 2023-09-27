#ifndef STAFF_H
#define STAFF_H

#include "person.h"
#include "ui_staffform.h"
#include "ui_setstaffform.h"

enum UserType
{
    admin, staff, none
};

class Staff : public Person
{
private:
    QString loginName;
    QString password;
    UserType type;
    Gender gender;
    int age;
    QString address;
public:
    Staff();
    Staff(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid, const QString &loginName, const QString &password, UserType type, Gender gender, int age, const QString &address);
    Staff(const Staff &staff);
    Staff &operator=(const Staff &other);
    const QString &getLoginName() const;
    void setLoginName(const QString &newLoginName);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    UserType getType() const;
    void setType(UserType newType);
    Gender getGender() const;
    void setGender(Gender newGender);
    int getAge() const;
    void setAge(int newAge);
    const QString &getAddress() const;
    void setAddress(const QString &newAddress);
    friend void operator<<(Ui::SetStaffForm *ui, const Staff &staff);
    friend void operator>>(Ui::SetStaffForm *ui, Staff &staff);
    friend void operator<<(Ui::StaffForm *ui, const Staff &staff);
};

#endif // STAFF_H
