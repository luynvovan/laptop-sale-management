#include "orderlist.h"

void OrderList::setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm)
{
    uiSetOrderForm = newUiSetOrderForm;
}

void OrderList::prepareAdd()
{
    if(orderDetail != nullptr)
        delete orderDetail;
    orderDetail = new OrderDetail;
    if(deletedId.isEmpty())
        orderDetail->setOrderId(list.getCount());
    else
    {
        orderDetail->setOrderId(deletedId.front());
    }
}

bool OrderList::setDelivering(int id)
{
    Order *order{list[id]};
    if(order == nullptr || order->getStatus() != preparing)
    {
        return false;
    }
    order->setDelivering();
    return true;
}

bool OrderList::setCompleted(int id)
{
    Order *order{list[id]};
    if(order == nullptr || order->getStatus() != delivering)
    {
        return false;
    }
    order->setCompleted();
    return true;
}

bool OrderList::setCanceled(int id)
{
    Order *order{list[id]};
    if(order == nullptr || !(order->getStatus() == delivering || order->getStatus() == preparing))
    {
        return false;
    }
    order->setCanceled();
    return true;
}

void OrderList::load()
{
    {
        QFile inputFile("./database/deleted_id/order.txt");
        inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream input(&inputFile);
        QString line = input.readLine();
        input.flush();
        inputFile.close();
        if(!line.isEmpty())
        {
            MyStringList infor;
            infor.setString(line);
            for(int i{}; i != infor.getSize(); ++i)
            {
                deletedId.push(infor[i].toInt());
            }
        }
    }

    QFile inputFileS("./database/sales_order.txt");
    inputFileS.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputS(&inputFileS);

    while(!inputS.atEnd())
    {
        QString line = inputS.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        //int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address
        list.add(new SalesOrder(infor[0].toInt(), infor[1] == "0" ? OrderType::salesOrder : OrderType::purchaseOrder, infor[2].toInt(), infor[3].toInt(), infor[4].toDouble(), infor[5], infor[6], infor[7] == "0" ? preparing : infor[7] == "1" ? delivering : infor[7] == "2" ? completed : canceled, infor[8], infor[9].toInt(), infor[10].toInt(), infor[11].toInt(), infor[12]));
    }

    inputS.flush();
    inputFileS.close();

    QFile inputFileP("./database/purchase_order.txt");
    inputFileP.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputP(&inputFileP);

    while(!inputP.atEnd())
    {
        QString line = inputP.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        list.add(new PurchaseOrder(infor[0].toInt(), infor[1] == "0" ? OrderType::salesOrder : OrderType::purchaseOrder, infor[2].toInt(), infor[3].toInt(), infor[4].toDouble(), infor[5], infor[6], infor[7] == "0" ? preparing : infor[7] == "1" ? delivering : infor[7] == "2" ? completed : canceled, infor[8]));
    }

    inputP.flush();
    inputFileP.close();
    orderDetailList->load();
}

void OrderList::save()
{
    {
        QFile outputFile("./database/deleted_id/order.txt");
        outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream output(&outputFile);
        if(!deletedId.isEmpty())
        {
            output << deletedId.front();
            deletedId.pop();
        }
        while(!deletedId.isEmpty())
        {
            output << "," << deletedId.front();
            deletedId.pop();
        }
        output.flush();
        outputFile.close();
    }

    // open file sales order
    QFile outputFileS("./database/sales_order.txt");
    outputFileS.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outputS(&outputFileS);
    // open file sales order

    // open file purchase order
    QFile outputFileP("./database/purchase_order.txt");
    outputFileP.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outputP(&outputFileP);
    // open file purchase order

    Order *order{};
    SalesOrder *salesOrder{};

    Node<Order*> *ptr{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            order = ptr->getData();
            ptr = ptr->getNext();
            if(order->getType() == OrderType::salesOrder)
            {
                salesOrder = static_cast<SalesOrder*>(order);
                //int id, OrderType type, int staffId, int customerId, double totalPrice, const QString &orderDay, const QString &completedDay, OrderStatus status, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address
                outputS << salesOrder->getId()              << ","
                        << salesOrder->getType()            << ","
                        << salesOrder->getStaffId()         << ","
                        << salesOrder->getCustomerId()      << ","
                        << salesOrder->getTotalPrice()      << ","
                        << salesOrder->getOrderDay()        << ","
                        << salesOrder->getCompletedDay()    << ","
                        << salesOrder->getStatus()          << ","
                        << salesOrder->getPhone()           << ","
                        << salesOrder->getDiscount()        << ","
                        << salesOrder->getUsedPoint()       << ","
                        << salesOrder->getUsePoint()        << ","
                        << salesOrder->getAddress()         << Qt::endl;

            }
            else
            {
                //int id, int staffId, int customerId, const QString &phone
                outputP << order->getId()              << ","
                        << order->getType()            << ","
                        << order->getStaffId()         << ","
                        << order->getCustomerId()      << ","
                        << order->getTotalPrice()      << ","
                        << order->getOrderDay()        << ","
                        << order->getCompletedDay()    << ","
                        << order->getStatus()          << ","
                        << order->getPhone()           << Qt::endl;
            }
        }
    }

    // close file sales order
    outputS.flush();
    outputFileS.close();
    // close file sales order

    // close file purchase order
    outputP.flush();
    outputFileP.close();
    // close file purchase order
    orderDetailList->save();
}

Node<Order *> *OrderList::getHeadAtIdx(int id)
{
    return list.getHeadatIdx(id);
}

int OrderList::getLength()
{
    return list.getLength();
}

bool OrderList::isExist(int id, int type)//0 - customer, 1 - supplier, 2 - staff, 3 - laptop
{
    switch (type) {
    case 0:
        for(int i{}; i != list.getLength(); ++i)
        {
            Node<Order*> *ptr = list.getHeadatIdx(i);
            while(ptr != nullptr)
            {
                if(ptr->getData()->getType() == salesOrder && ptr->getData()->getCustomerId() == id)
                {
                    return true;
                }
                ptr = ptr->getNext();
            }
        }
        break;
    case 1:
        for(int i{}; i != list.getLength(); ++i)
        {
            Node<Order*> *ptr = list.getHeadatIdx(i);
            while(ptr != nullptr)
            {
                if(ptr->getData()->getType() == purchaseOrder && ptr->getData()->getCustomerId() == id)
                {
                    return true;
                }
                ptr = ptr->getNext();
            }
        }
        break;
    case 2:
        for(int i{}; i != list.getLength(); ++i)
        {
            Node<Order*> *ptr = list.getHeadatIdx(i);
            while(ptr != nullptr)
            {
                if(ptr->getData()->getStaffId() == id)
                {
                    return true;
                }
                ptr = ptr->getNext();
            }
        }
        break;
    default:
        return orderDetailList->isContainItem(id);
        break;
    }
    return false;
}

OrderList::OrderList(CustomerList *customerList, StaffList *staffList, LaptopList *laptopList, SupplierList *supplierList):
    list(OrderList::takeKey, OrderList::isEqual),
    orderDetailList(new OrderDetailList(laptopList)),
    orderDetail(nullptr)
{
    Order::setCustomerList(customerList);
    Order::setStaffList(staffList);
    Order::setLaptopList(laptopList);
    Order::setSupplierList(supplierList);
    Order::setOrderDetailList(orderDetailList);
}

OrderList::~OrderList()
{
    Node<Order*> *ptr{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            delete ptr->getData();
            ptr = ptr->getNext();
        }
    }
    delete orderDetailList;
}

void OrderList::add()
{
    if(orderDetail == nullptr)
    {
        return;
    }
    int id{};
    if(deletedId.isEmpty())
        id = list.getCount();
    else
    {
        id = deletedId.front();
        deletedId.pop();
    }
    Order *order;
    QString customer{uiSetOrderForm->cbBoxCustomer->currentText()};
    int customerId{customer.right(customer.size() - customer.lastIndexOf(' ') - 1).toInt()};
    bool isAddingSalesOrder = !uiSetOrderForm->lnPrice->isVisible();
    if(isAddingSalesOrder)
    {
        order = new SalesOrder(id, StaffList::getNowLogin()->getId(), customerId, uiSetOrderForm->lnPhone->text(), uiSetOrderForm->spinBoxDiscount->value(), 0, uiSetOrderForm->cboxUsePoint->checkState(), uiSetOrderForm->lnAddress->text());
    }
    else
    {
        order = new PurchaseOrder(id, StaffList::getNowLogin()->getId(), customerId, uiSetOrderForm->lnPhone->text());
    }
    order->setOrder(orderDetail);
    list.add(order);

//    if(order->getType() == OrderType::salesOrder)
//    {
//        // open file sales order
//        QFile outputFileS("./database/sales_order.txt");
//        outputFileS.open(QIODevice::Text | QIODevice::Append);
//        QTextStream outputS(&outputFileS);
//        // open file sales order

//        SalesOrder *salesOrder = static_cast<SalesOrder*>(order);
//        //int id, int staffId, int customerId, const QString &phone, int discount, int usedPoint, bool usePoint, const QString &address
//        outputS << salesOrder->getId()              << ","
//                << salesOrder->getType()            << ","
//                << salesOrder->getStaffId()         << ","
//                << salesOrder->getCustomerId()      << ","
//                << salesOrder->getTotalPrice()      << ","
//                << salesOrder->getOrderDay()        << ","
//                << salesOrder->getCompletedDay()    << ","
//                << salesOrder->getStatus()          << ","
//                << salesOrder->getPhone()           << ","
//                << salesOrder->getDiscount()        << ","
//                << salesOrder->getUsedPoint()       << ","
//                << salesOrder->getUsePoint()        << ","
//                << salesOrder->getAddress()         << Qt::endl;

//        // close file sales order
//        outputS.flush();
//        outputFileS.close();
//        // close file sales order
//    }
//    else
//    {
//        // open file purchase order
//        QFile outputFileP("./database/purchase_order.txt");
//        outputFileP.open(QIODevice::Text | QIODevice::Append);
//        QTextStream outputP(&outputFileP);
//        // open file purchase order

//        //int id, int staffId, int customerId, const QString &phone
//        outputP << order->getId()              << ","
//                << order->getType()            << ","
//                << order->getStaffId()         << ","
//                << order->getCustomerId()      << ","
//                << order->getTotalPrice()      << ","
//                << order->getOrderDay()        << ","
//                << order->getCompletedDay()    << ","
//                << order->getStatus()          << ","
//                << order->getPhone()           << Qt::endl;

//        // close file purchase order
//        outputP.flush();
//        outputFileP.close();
//        // close file purchase order
//    }

    orderDetail = nullptr;
}

void OrderList::showList()
{
    return;
}

void OrderList::showDetail(int id)
{
    return;
}

void OrderList::set(int id)
{
    return;
}

int OrderList::getCount()
{
    return list.getCount();
}

void OrderList::remove(int id)
{
    if(list[id]->getStatus() == canceled || list[id]->getStatus() == completed)
    {
        if(!(deletedId.isEmpty() && id == list.getCount() - 1))
            deletedId.push(id);
        list.remove(id);
        orderDetailList->remove(id);
    }
}

Order *OrderList::at(int id)
{
    return list[id];
}

int OrderList::takeKey(Order * const &order)
{
    return order->getId();
}

bool OrderList::isEqual(Order * const &l, Order * const &r)
{
    return l->getId() == r->getId();
}

