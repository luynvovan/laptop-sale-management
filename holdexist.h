#ifndef HOLDEXIST_H
#define HOLDEXIST_H

#include <QObject>
#include "orderlist.h"

class HoldExist : public QObject
{
    Q_OBJECT
public:
    explicit HoldExist(OrderList *orderList, QObject *parent = nullptr);
private:
    OrderList *orderList;
signals:
    void sendCustomerExist(int id, bool stat);
    void sendSupplierExist(int id, bool stat);
    void sendStaffExist(int id, bool stat);
    void sendItemExist(int id, bool stat);
public slots:
    void recieveId(int id, int type);
};

#endif // HOLDEXIST_H
