#include "orderdetaillist.h"

OrderDetailList::OrderDetailList(LaptopList *laptopList) :
    list(OrderDetailList::takeKey, OrderDetailList::isEqual)
{
    OrderDetail::setLaptopList(laptopList);
    OrderItem::setLaptopList(laptopList);
}

OrderDetailList::~OrderDetailList()
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<OrderDetail*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
}

int OrderDetailList::takeKey(OrderDetail * const &orderDetail)
{
    return orderDetail->getOrderId();
}

bool OrderDetailList::isEqual(OrderDetail * const &l, OrderDetail * const &r)
{
    return l->getOrderId() == r->getOrderId();
}

void OrderDetailList::add(OrderDetail *oD)
{
    list.add(oD);
//    // open file order detail
//    QFile outputFileO("./database/order_detail.txt");
//    outputFileO.open(QIODevice::Text | QIODevice::Append);
//    QTextStream outputO(&outputFileO);
//    // open file order detail

//    OrderItem *orderItem{};
//    Node<OrderItem*> *ptr = oD->getHead();
//    while(ptr != nullptr)
//    {
//        orderItem = ptr->getData();
//        ptr = ptr->getNext();

//        outputO << orderItem->getOrderId()    << ","
//                << orderItem->getItemId()     << ","
//                << orderItem->getQuantity()   << ","
//                << orderItem->getPrice()      << ","
//                << orderItem->getDiscount()   << Qt::endl;
//    }

//    // close file order detail
//    outputO.flush();
//    outputFileO.close();
//    // close file order detail
}

void OrderDetailList::remove(int orderId)
{
    list.remove(orderId);
}

OrderDetail *OrderDetailList::at(int orderId)
{
    return list[orderId];
}

void OrderDetailList::save()
{
    // open file order detail
    QFile outputFileO("./database/order_detail.txt");
    outputFileO.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outputO(&outputFileO);
    // open file order detail

    Node<OrderDetail*> *orderDetail{};
    Node<OrderItem*> *orderItem{};
    OrderItem *ptr;
    for(int i{}; i != list.getLength(); ++i)
    {
        orderDetail = list.getHeadatIdx(i);
        while(orderDetail != nullptr)
        {//int orderId, int itemId, int quantity, double price, int discount
            orderItem = orderDetail->getData()->getHead();
            orderDetail = orderDetail->getNext();
            while(orderItem != nullptr)
            {
                ptr = orderItem->getData();
                orderItem = orderItem->getNext();
                outputO << ptr->getOrderId()    << ","
                        << ptr->getItemId()     << ","
                        << ptr->getQuantity()   << ","
                        << ptr->getPrice()      << ","
                        << ptr->getDiscount()   << Qt::endl;
            }
        }
    }

    // close file order detail
    outputO.flush();
    outputFileO.close();
    // close file order detail
}

void OrderDetailList::load()
{
    QFile inputFileO("./database/order_detail.txt");
    inputFileO.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputO(&inputFileO);

    while(!inputO.atEnd())
    {
        QString line = inputO.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        OrderItem *orderItem = new OrderItem(infor[0].toInt(), infor[1].toInt(), infor[2].toInt(), infor[3].toDouble(), infor[4].toInt());
        if(list[orderItem->getOrderId()] == nullptr)
        {
            list.add(new OrderDetail(orderItem->getOrderId()));
        }
        list[orderItem->getOrderId()]->push(orderItem);
    }

    inputO.flush();
    inputFileO.close();
}

bool OrderDetailList::isContainItem(int id)
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<OrderDetail*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            Node<OrderItem*> *ptr = head->getData()->getHead();
            while(ptr != nullptr)
            {
                if(ptr->getData()->getItemId() == id)
                {
                    return true;
                }
                ptr = ptr->getNext();
            }
            head = head->getNext();
        }
    }
    return false;
}

