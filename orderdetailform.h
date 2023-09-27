#ifndef ORDERDETAILFORM_H
#define ORDERDETAILFORM_H

#include <QDialog>
#include "order.h"

namespace Ui {
class OrderDetailForm;
}

class OrderDetailForm : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDetailForm(QWidget *parent = nullptr);
    ~OrderDetailForm();

private:
    Ui::OrderDetailForm *ui;
public slots:
    void showOrderDetail(Order *order);
};

#endif // ORDERDETAILFORM_H
