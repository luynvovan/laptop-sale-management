#include "person.h"

int Person::getId() const
{
    return id;
}

void Person::setId(int newId)
{
    id = newId;
}

const QString &Person::getName() const
{
    return name;
}

void Person::setName(const QString &newName)
{
    name = newName;
}

const QString &Person::getPhoneNumber() const
{
    return phoneNumber;
}

void Person::setPhoneNumber(const QString &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

int Person::getCompletedOrder() const
{
    return completedOrder;
}

void Person::setCompletedOrder(int newCompletedOrder)
{
    completedOrder = newCompletedOrder;
}

double Person::getTotalPaid() const
{
    return totalPaid;
}

void Person::setTotalPaid(double newTotalPaid)
{
    totalPaid = newTotalPaid;
}

Person::Person() :
    Person(-1, "", "", 0, 0)
{}

Person::Person(const Person &person) :
    Person(person.id, person.name, person.phoneNumber, person.completedOrder, person.totalPaid)
{}

Person::Person(int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid) :
    id(id),
    name(name),
    phoneNumber(phoneNumber),
    completedOrder(completedOrder),
    totalPaid(totalPaid)
{}

Person &Person::operator=(const Person &other)
{
    this->id = other.id;
    this->name = other.name;
    this->phoneNumber = other.phoneNumber;
    this->completedOrder = other.completedOrder;
    this->totalPaid = other.totalPaid;
    return *this;
}
