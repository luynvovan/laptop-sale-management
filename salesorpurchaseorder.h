#ifndef SALESORPURCHASEORDER_H
#define SALESORPURCHASEORDER_H

#include <QDialog>
#include "order.h"

namespace Ui {
class SalesOrPurchaseOrder;
}

class SalesOrPurchaseOrder : public QDialog
{
    Q_OBJECT

public:
    explicit SalesOrPurchaseOrder(QWidget *parent = nullptr);
    ~SalesOrPurchaseOrder();

private slots:
    void commandLinkButton_clicked();

    void commandLinkButton_2_clicked();

    void commandLinkButton_3_clicked();

private:
    Ui::SalesOrPurchaseOrder *ui;
signals:
    void setSignalAddOrder(bool waitingToAddOrder, OrderType orderType = salesOrder);
};

#endif // SALESORPURCHASEORDER_H
