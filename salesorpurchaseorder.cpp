#include "salesorpurchaseorder.h"
#include "ui_salesorpurchaseorder.h"

SalesOrPurchaseOrder::SalesOrPurchaseOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesOrPurchaseOrder)
{
    ui->setupUi(this);
    connect(ui->commandLinkButton, &QCommandLinkButton::clicked, this, &SalesOrPurchaseOrder::commandLinkButton_clicked);
    connect(ui->commandLinkButton_2, &QCommandLinkButton::clicked, this, &SalesOrPurchaseOrder::commandLinkButton_2_clicked);
    connect(ui->commandLinkButton_3, &QCommandLinkButton::clicked, this, &SalesOrPurchaseOrder::commandLinkButton_3_clicked);
}

SalesOrPurchaseOrder::~SalesOrPurchaseOrder()
{
    delete ui;
}

void SalesOrPurchaseOrder::commandLinkButton_clicked()
{
    emit setSignalAddOrder(true, salesOrder);
    this->accept();
}


void SalesOrPurchaseOrder::commandLinkButton_2_clicked()
{
    emit setSignalAddOrder(true, purchaseOrder);
    this->accept();
}


void SalesOrPurchaseOrder::commandLinkButton_3_clicked()
{
    emit setSignalAddOrder(false);
    this->close();
}

