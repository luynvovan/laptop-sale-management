#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
private:
    int id;
    QString name;
    QString phoneNumber;
    int completedOrder;
    double totalPaid;
public:
    Person();
    Person(const Person &person);
    Person(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid);
    Person &operator=(const Person &other);
    int getId() const;
    void setId(int newId);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getPhoneNumber() const;
    void setPhoneNumber(const QString &newPhoneNumber);
    int getCompletedOrder() const;
    void setCompletedOrder(int newCompletedOrder);
    double getTotalPaid() const;
    void setTotalPaid(double newTotalPaid);
};

enum Gender
{
    male, female
};

#endif // PERSON_H
