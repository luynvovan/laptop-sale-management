#ifndef ILIST_H
#define ILIST_H

#include "hashtable.h"
#include <QTableWidgetItem>
#include <QFile>
#include "mystringlist.h"

class IList
{
public:
    virtual void add() = 0;
    virtual void showList() = 0;
    virtual void showDetail(int id) = 0;
    virtual void set(int id) = 0;
    virtual void remove(int id) = 0;
    virtual int getCount() = 0;
    virtual void load() = 0;
    virtual void save() = 0;
};




















class IntQTableWidgetItem: public QTableWidgetItem
{
public:
    IntQTableWidgetItem(const QString text):
        QTableWidgetItem(text)
    {}
    bool operator<(const QTableWidgetItem &other) const
    {
        return this->text().toInt() < other.text().toInt();
    }
};

class DoubleQTableWidgetItem: public QTableWidgetItem
{
public:
    DoubleQTableWidgetItem(const QString text):
        QTableWidgetItem(text)
    {}
    bool operator<(const QTableWidgetItem &other) const
    {
        return this->text().toDouble() < other.text().toDouble();
    }
};

#endif // ILIST_H
