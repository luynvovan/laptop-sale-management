#include "holdexist.h"

HoldExist::HoldExist(OrderList *orderList, QObject *parent)
    : QObject{parent}, orderList{orderList}
{

}

void HoldExist::recieveId(int id, int type)
{
    switch (type) {
    case 0:
        emit sendCustomerExist(id, orderList->isExist(id, type));
        break;
    case 1:
        emit sendSupplierExist(id, orderList->isExist(id, type));
        break;
    case 2:
        emit sendStaffExist(id, orderList->isExist(id, type));
        break;
    default:
        emit sendItemExist(id, orderList->isExist(id, type));
        break;
    }
}
