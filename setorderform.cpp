#include "setorderform.h"
#include "ui_setorderform.h"

SetOrderForm::SetOrderForm(LaptopList *laptopList, CustomerList *customerList, SupplierList *supplierList, OrderList *orderList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetOrderForm),
    orderList(orderList),
    laptopList(laptopList),
    customerList(customerList),
    supplierList(supplierList)
{
    ui->setupUi(this);
    orderList->setUiSetOrderForm(ui);
    orderList->load();
    laptopList->setUiSetOrderForm(ui);
    customerList->setUiSetOrderForm(ui);
    supplierList->setUiSetOrderForm(ui);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lnPrice->setValidator(new QDoubleValidator(0, 1000, 2, this));
    ui->btnOk->setDefault(true);
//    void btnAdd_clicked();
    connect(ui->btnAdd, &QPushButton::clicked, this, &SetOrderForm::btnAdd_clicked);
//    void cbBoxItem_activated(int index);
    connect(ui->cbBoxItem, &QComboBox::activated, this, &SetOrderForm::cbBoxItem_activated);
//    void btnDelete_clicked();
    connect(ui->btnDelete, &QPushButton::clicked, this, &SetOrderForm::btnDelete_clicked);
//    void cbBoxCustomer_activated(int index);
    connect(ui->cbBoxCustomer, &QComboBox::activated, this, &SetOrderForm::cbBoxCustomer_activated);
//    void cboxUsePoint_stateChanged(int arg1);
    connect(ui->cboxUsePoint, &QCheckBox::stateChanged, this, &SetOrderForm::cboxUsePoint_stateChanged);
//    void btnCancel_clicked();
    connect(ui->btnCancel, &QPushButton::clicked, this, &SetOrderForm::btnCancel_clicked);
//    void btnOk_clicked();
    connect(ui->btnOk, &QPushButton::clicked, this, &SetOrderForm::btnOk_clicked);
//    void spinBoxDiscount_valueChanged(int arg1);
    connect(ui->spinBoxDiscount, &QSpinBox::valueChanged, this, &SetOrderForm::spinBoxDiscount_valueChanged);
}

SetOrderForm::~SetOrderForm()
{
    delete ui;
}

void SetOrderForm::btnAdd_clicked()
{
    if(ui->name->text().isEmpty() || ui->lblCompleted->text().isEmpty())
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose an item and a customer/supplier");
        return;
    }
    bool isAddingSalesOrder{!ui->lnPrice->isVisible()};
    QString item{ui->cbBoxItem->currentText()};
    int id{item.right(item.size() - item.lastIndexOf(' ') - 1).toInt()};
    int quantity{ui->spinBoxQuantity->value()};
    if(quantity < 1)
    {
        return;
    }
    if(isAddingSalesOrder)
    {
        if(!orderList->orderDetail->add(id, quantity))
        {
            QMessageBox::warning(this, "Quantity is over", "Kuso yarou");
            return;
        }
    }
    else
        orderList->orderDetail->add(id, quantity, ui->lnPrice->text().toDouble());

    Node<OrderItem*> *ptr{orderList->orderDetail->getHead()};
    while(ptr->getData()->getItemId() != id)
    {
        ptr = ptr->getNext();
    }
    int rowCount{ui->tableWidget->rowCount()};
    for(int i{}; i != rowCount; ++i)
    {
        if(id == ui->tableWidget->item(i, 0)->text().toInt())
        {
            if(!isAddingSalesOrder)
            {
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(ui->lnPrice->text()));
            }
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QVariant(ptr->getData()->getQuantity()).toString()));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QVariant(ptr->getData()->getTotal()).toString()));
            computeLastPrice();
            return;
        }
    }
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(id).toString()));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(ui->name->text()));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(ui->brand->text()));
    if(isAddingSalesOrder)
    {
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(ui->price->text()));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(ui->discount->text()));
    }
    else
    {
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(ui->lnPrice->text()));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QVariant(0).toString()));
    }
    ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QVariant(quantity).toString()));
    ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(QVariant(ptr->getData()->getTotal()).toString()));
    computeLastPrice();
}

void SetOrderForm::changeToSalesOrder()
{
    clearDetail();
    ui->lblPrice->setVisible(false);
    ui->lnPrice->setVisible(false);
    ui->lblCustomer->setText("Customer");
    ui->lnPhone->setDisabled(false);
    ui->lnAddress->setDisabled(false);
    ui->groupBoxCustomer->setTitle("Customer detail");
    ui->cboxUsePoint->setDisabled(false);
    ui->spinBoxDiscount->setDisabled(false);
    ui->spinBoxDiscount->setValue(0);
    customerList->fillOrderCustomerComboBox();
    laptopList->fillOrderItemComboBox();
}

void SetOrderForm::changeToPurchaseOrder()
{
    clearDetail();
    ui->lblPrice->setVisible(true);
    ui->lnPrice->setVisible(true);
    ui->lnPrice->clear();
    ui->lblCustomer->setText("Supplier");
    ui->lnPhone->setDisabled(true);
    ui->lnAddress->setDisabled(true);
    ui->groupBoxCustomer->setTitle("Supplier detail");
    ui->cboxUsePoint->setDisabled(true);
    ui->spinBoxDiscount->setDisabled(true);
    ui->spinBoxDiscount->setValue(0);
    supplierList->fillOrderSupplierComboBox();
    laptopList->fillOrderItemComboBox();
}

void SetOrderForm::computeLastPrice()
{
    double total{};
    Node<OrderItem*> *ptr{orderList->orderDetail->getHead()};
    while(ptr != nullptr)
    {   total += ptr->getData()->getTotal();
        ptr = ptr->getNext();
    }
    ui->lblTotal->setText(QVariant(total).toString());
    total -= total * ui->spinBoxDiscount->value() / 100.0;
    if(ui->cboxUsePoint->isChecked())
    {
        double point = ui->lblPoint->text().toDouble();
        if(total > point)
            total -= point;
        else
            total = 0;
    }
    ui->lblLastPrice->setText(QVariant(total).toString());
}

void SetOrderForm::clearDetail()
{
    ui->name->clear();
    ui->brand->clear();
    ui->price->clear();
    ui->discount->clear();
    ui->quantity->clear();
    ui->sold->clear();
    ui->screen->clear();
    ui->cpu->clear();
    ui->ram->clear();
    ui->hdd->clear();
    ui->ssd->clear();
    ui->weight->clear();
    ui->lblImage->clear();
    ui->spinBoxQuantity->setValue(0);
    ui->lnPrice->clear();
    ui->lnPhone->clear();
    ui->lnAddress->clear();
    ui->lblCompleted->clear();
    ui->lblPaid->clear();
    ui->lblID->clear();
    ui->lblPoint->clear();
    ui->lblTotal->clear();
    ui->spinBoxDiscount->setValue(0);
    ui->cboxUsePoint->setCheckState(Qt::Unchecked);
    ui->lblLastPrice->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void SetOrderForm::closeEvent(QCloseEvent *event)
{
    if(orderList->orderDetail != nullptr)
        delete orderList->orderDetail;
    orderList->orderDetail = nullptr;
    event->accept();
}

void SetOrderForm::cbBoxItem_activated(int index)
{
    QString item{ui->cbBoxItem->currentText()};
    int id{item.right(item.size() - item.lastIndexOf(' ') - 1).toInt()};
    laptopList->fillOrderItemDetail(id);
}


void SetOrderForm::btnDelete_clicked()
{
    int curRow = ui->tableWidget->currentRow();
    QTableWidgetItem *item = ui->tableWidget->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No item was chosen", "Please choose one item to delete");
        return;
    }
    int id{item->text().toInt()};
    ui->tableWidget->removeRow(curRow);
    orderList->orderDetail->remove(id);
    computeLastPrice();
}


void SetOrderForm::cbBoxCustomer_activated(int index)
{
    QString customer{ui->cbBoxCustomer->currentText()};
    int id{customer.right(customer.size() - customer.lastIndexOf(' ') - 1).toInt()};
    bool isAddingSalesOrder{!ui->lnPrice->isVisible()};
    if(isAddingSalesOrder)
    {
        customerList->fillOrderCustomerInfor(id);
    }
    else
    {
        supplierList->fillOrderSupplierInfo(id);
    }
}

void SetOrderForm::cboxUsePoint_stateChanged(int arg1)
{
    double total{ui->lblTotal->text().toDouble()};
    total -= total * ui->spinBoxDiscount->value() / 100.0;
    if(arg1)
    {
        double point = ui->lblPoint->text().toDouble();
        if(total > point)
            total -= point;
        else
            total = 0;
    }
    ui->lblLastPrice->setText(QVariant(total).toString());
}

void SetOrderForm::btnCancel_clicked()
{
    this->close();
}

void SetOrderForm::btnOk_clicked()
{
    if(ui->tableWidget->rowCount() == 0)
        return;
    orderList->add();
    this->accept();
}

void SetOrderForm::spinBoxDiscount_valueChanged(int arg1)
{
    double total{ui->lblTotal->text().toDouble()};
    total -= total * arg1 / 100.0;
    if(ui->cboxUsePoint->isChecked())
    {
        double point = ui->lblPoint->text().toDouble();
        if(total > point)
            total -= point;
        else
            total = 0;
    }
    ui->lblLastPrice->setText(QVariant(total).toString());
}

