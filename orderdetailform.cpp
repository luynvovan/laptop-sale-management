#include "orderdetailform.h"
#include "salesorder.h"
#include "ui_orderdetailform.h"

OrderDetailForm::OrderDetailForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderDetailForm)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

OrderDetailForm::~OrderDetailForm()
{
    delete ui;
}

void OrderDetailForm::showOrderDetail(Order *order)
{
    if(order == nullptr)
        return;
    int discount{};
    int point{};
    if(order->getType() == salesOrder)
    {
        SalesOrder *sOrder = static_cast<SalesOrder*>(order);
        ui->address->setText(sOrder->getAddress());
        point = sOrder->getUsedPoint();
        ui->usePoint->setText(QVariant(point).toString());
        discount = sOrder->getDiscount();
        ui->discount->setText(QVariant(discount).toString());
        ui->lblCustomerID->setText("Customer ID:");
        ui->lblCustomer->setText("Customer:");
    }
    else
    {
        ui->address->setText("---");
        ui->usePoint->setText("0");
        ui->discount->setText("0");
        ui->lblCustomerID->setText("Supplier ID:");
        ui->lblCustomer->setText("Supplier:");
    }
    ui->customerID->setText(QVariant(order->getCustomerId()).toString());
    ui->customer->setText(order->getCustomerName());
    ui->phone->setText(order->getPhone());
    ui->staffID->setText(QVariant(order->getStaffId()).toString());
    ui->staff->setText(order->getStaffName());
    ui->orderDate->setText(order->getOrderDay());
    ui->completedDate->setText(order->getCompletedDay());
    ui->status->setText(order->getStatus() == preparing ? "Preparing" : order->getStatus() == delivering ? "Delivering" : order->getStatus() == completed ? "Completed" : "Canceled");
    ui->total->setText(QVariant(order->getTotalBef()).toString());
    ui->lastPrice->setText(QVariant(order->getTotalPrice()).toString());

    ui->tableWidget->clearContents();
    int rowCount{order->getOrderDetail()->getLength()};
    ui->tableWidget->setRowCount(rowCount);
    Node<OrderItem *> *ptr{order->getOrderDetail()->getHead()};
    OrderItem *orderItem{};
    for(int i{}; i != rowCount; ++i)
    {
        orderItem = ptr->getData();
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QVariant(orderItem->getItemId()).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(orderItem->getItemName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(orderItem->getItemBrand()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QVariant(orderItem->getPrice()).toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QVariant(orderItem->getQuantity()).toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QVariant(orderItem->getDiscount()).toString()));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QVariant(orderItem->getTotal()).toString()));
        ptr = ptr->getNext();
    }

    this->exec();
}
