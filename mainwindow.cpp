#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    {
        QDir dir("./database/");
        if(!dir.exists())
        {
            QDir().mkdir("./database/");
        }
        QDir dirr("./database/deleted_id/");
        if(!dirr.exists())
        {
            QDir().mkdir("./database/deleted_id/");
        }
    }
    staffList = new StaffList();
    staffForm = new StaffForm(staffList, this);
    ui->setupUi(this);
    loginForm = new LoginForm(staffList, this);
    setGui(none);
    connect(ui->menuAccount, &QMenu::triggered, this, &MainWindow::accountMenu_clicked);
    laptopList = new LaptopList();
    laptopForm = new LaptopForm(laptopList, this);
    connect(ui->menuManegement, &QMenu::triggered, this, &MainWindow::manegementMenu_clicked);
    customerList = new CustomerList();
    customerForm = new CustomerForm(customerList, this);
    supplierList = new SupplierList();
    supplierForm = new SupplierForm(supplierList, this);

    orderList = new OrderList(customerList, staffList, laptopList, supplierList);
    setOrderForm = new SetOrderForm(laptopList, customerList, supplierList, orderList, this);

    waitToAddOrder = false;
    tempOrderType = salesOrder;
    saleOrPurchaseOrder = new SalesOrPurchaseOrder();
    connect(saleOrPurchaseOrder, &SalesOrPurchaseOrder::setSignalAddOrder, this, &MainWindow::setSignalAddOrder);
    ui->listOrder->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listDetail->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderDetailForm = new OrderDetailForm(this);
    connect(this, &MainWindow::showOrderDetail, orderDetailForm, &OrderDetailForm::showOrderDetail);

    Order *order{};
    Node<Order*> *ptr{};
    ui->listOrder->setRowCount(orderList->getCount());
    int curRow{};
    for(int i{}; i != orderList->getLength(); ++i)
    {
        ptr = orderList->getHeadAtIdx(i);
        while(ptr != nullptr)
        {
            order = ptr->getData();
            ptr = ptr->getNext();

            ui->listOrder->setItem(curRow, 0, new IntQTableWidgetItem(QVariant(order->getId()).toString()));//id
            ui->listOrder->setItem(curRow, 1, new QTableWidgetItem(order->getType() == salesOrder ? "Sales" : "Purchase")); //order type
            ui->listOrder->setItem(curRow, 2, new QTableWidgetItem(order->getType() == salesOrder ? customerList->at(order->getCustomerId())->getName() : supplierList->at(order->getCustomerId())->getName()));//name
            ui->listOrder->setItem(curRow, 3, new QTableWidgetItem(order->getOrderDay()));//date
            ui->listOrder->setItem(curRow, 4, new QTableWidgetItem(order->getCompletedDay()));//complete
            ui->listOrder->setItem(curRow, 5, new DoubleQTableWidgetItem(QVariant(order->getTotalPrice()).toString()));//total
            ui->listOrder->setItem(curRow, 6, new QTableWidgetItem(order->getStatus() == preparing ? "Preparing" : order->getStatus() == delivering ? "Delivering" : order->getStatus() == completed ? "Completed" : "Canceled"));//status
            ++curRow;
        }
    }
    connect(ui->listOrder, &QTableWidget::cellClicked, this, &MainWindow::listOrder_cellClicked);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::btnSearch_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &MainWindow::btnCancel_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::btnDelete_clicked);
    connect(ui->btnDetail, &QPushButton::clicked, this, &MainWindow::btnDetail_clicked);
    connect(ui->btnDeliver, &QPushButton::clicked, this, &MainWindow::btnDeliver_clicked);
    connect(ui->btnComplete, &QPushButton::clicked, this, &MainWindow::btnComplete_clicked);
    connect(ui->btnAddOrder, &QPushButton::clicked, this, &MainWindow::btnAddOrder_clicked);
    ui->btnSearch->setDefault(true);
    changePasswordForm = new ChangePasswordForm(this);
    ui->listOrder->setSortingEnabled(true);

    holdExist = new HoldExist(orderList, this);
    connect(customerForm, &CustomerForm::sendCustomerId, holdExist, &HoldExist::recieveId);
    connect(holdExist, &HoldExist::sendCustomerExist, customerForm, &CustomerForm::goDelete);

    connect(laptopForm, &LaptopForm::sendLaptopId, holdExist, &HoldExist::recieveId);
    connect(holdExist, &HoldExist::sendItemExist, laptopForm, &LaptopForm::goDelete);

    connect(supplierForm, &SupplierForm::sendSupplierId, holdExist, &HoldExist::recieveId);
    connect(holdExist, &HoldExist::sendSupplierExist, supplierForm, &SupplierForm::goDelete);

    connect(staffForm, &StaffForm::sendStaffId, holdExist, &HoldExist::recieveId);
    connect(holdExist, &HoldExist::sendStaffExist, staffForm, &StaffForm::goDelete);

    changeStaffInfor = new ChangeStaffInfor(this);
    if(staffList->getCount() == 0)
        staffList->add(new Staff(0, "Hikigaya", "17351118", 0, 0.0, "hikki", "88", UserType::admin, Gender::male, 21, "Chiba"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete laptopList;
    delete customerList;
    delete supplierList;
    delete staffList;
    delete orderList;
}

void MainWindow::setGui(const UserType &usertype)
{
    if(usertype == none)
    {
        ui->menuManegement->menuAction()->setVisible(false);
        ui->actionLogin->setText("Login");
        ui->actionInfor->setVisible(false);
        ui->actionPassword->setVisible(false);
        ui->userName->clear();
        ui->userPosition->clear();
        ui->cbBoxSearch->setDisabled(true);
        ui->lnSearch->clear();
        ui->lnSearch->setDisabled(true);
        ui->btnSearch->setDisabled(true);
        ui->cbBoxShow->setDisabled(true);
        ui->cbBoxSearch->setCurrentIndex(0);
        ui->btnDetail->setDisabled(true);
        ui->btnComplete->setDisabled(true);
        ui->btnCancel->setDisabled(true);
        ui->btnDeliver->setDisabled(true);
        ui->btnDelete->setDisabled(true);
        ui->btnAddOrder->setDisabled(true);
        ui->listOrder->setVisible(false);
        ui->listDetail->clearContents();
        ui->listDetail->setRowCount(0);
        ui->listDetail->setVisible(false);
    }
    else
    {
        ui->menuManegement->menuAction()->setVisible(true);
        ui->actionLogin->setText("Logout");
        ui->actionInfor->setVisible(true);
        ui->actionPassword->setVisible(true);
        ui->userName->setText(StaffList::getNowLogin()->getName());
        ui->userPosition->setText((StaffList::getNowLogin()->getType() == staff) ? "Staff" : "Admin");
        ui->cbBoxSearch->setDisabled(false);
        ui->lnSearch->setDisabled(false);
        ui->btnSearch->setDisabled(false);
        ui->cbBoxShow->setDisabled(false);
        ui->btnDetail->setDisabled(false);
        ui->btnComplete->setDisabled(false);
        ui->btnCancel->setDisabled(false);
        ui->btnDeliver->setDisabled(false);
        ui->btnDelete->setDisabled(false);
        ui->btnAddOrder->setDisabled(false);
        ui->listOrder->setVisible(true);
        ui->listDetail->setVisible(true);
        ui->btnDelete->setDisabled(true);
        if(usertype == admin)
        {
            ui->btnDelete->setDisabled(false);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton clickedBtn = QMessageBox::question(this, "You're about going to exit", "Are you sure");
    if(clickedBtn == QMessageBox::Yes)
    {   customerList->save();
        laptopList->save();
        orderList->save();
        staffList->save();
        supplierList->save();
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::accountMenu_clicked(QAction *action)
{
    QString ac = action->text();
    if(ac == "Login")
    {
        if(QDialog::Accepted == loginForm->exec())
        {
            setGui(StaffList::getNowLogin()->getType());
        }
    }
    else if(ac == "Logout")
    {
        staffList->logout();
        setGui(none);
    }
    else if(ac == "Password")
    {
        changePasswordForm->exec();
    }
    else if(ac == "Infor")
    {
        if(changeStaffInfor->exec() == QDialog::Accepted)
        {
            ui->userName->setText(StaffList::getNowLogin()->getName());
        }
    }
}

void MainWindow::manegementMenu_clicked(QAction *action)
{
    QString ac = action->text();
    if(ac == "Laptop")
    {
        laptopForm->showThis();
    }
    else if(ac == "Customer")
    {
        customerForm->showThis();
    }
    else if(ac == "Supplier")
    {
        supplierForm->showThis();
    }
    else if(ac == "Staff")
    {
        staffForm->showThis();
    }
}


void MainWindow::btnAddOrder_clicked()
{
    waitToAddOrder = false;

    if(StaffList::getNowLogin()->getType() == admin)
    {
        saleOrPurchaseOrder->exec();
    }
    else
    {
        waitToAddOrder = true;
        tempOrderType = salesOrder;
    }
    orderList->orderDetail = new OrderDetail();
    if(!waitToAddOrder)
        return;
    if(tempOrderType == salesOrder)
    {
        setOrderForm->changeToSalesOrder();
    }
    else
    {
        setOrderForm->changeToPurchaseOrder();
    }
    orderList->prepareAdd();
    int addingOrderId{orderList->orderDetail->getOrderId()};
    if(QDialog::Accepted == setOrderForm->exec())
    {
        int rowCount{ui->listOrder->rowCount()};
        ui->listOrder->insertRow(rowCount);
        Order *order{orderList->at(addingOrderId)};
        ui->listOrder->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(addingOrderId).toString()));//id
        ui->listOrder->setItem(rowCount, 1, new QTableWidgetItem(order->getType() == salesOrder ? "Sales" : "Purchase")); //order type
        ui->listOrder->setItem(rowCount, 2, new QTableWidgetItem(order->getType() == salesOrder ? customerList->at(order->getCustomerId())->getName() : supplierList->at(order->getCustomerId())->getName()));//name
        ui->listOrder->setItem(rowCount, 3, new QTableWidgetItem(order->getOrderDay()));//date
        ui->listOrder->setItem(rowCount, 4, new QTableWidgetItem("---"));//complete
        ui->listOrder->setItem(rowCount, 5, new DoubleQTableWidgetItem(QVariant(order->getTotalPrice()).toString()));//total
        ui->listOrder->setItem(rowCount, 6, new QTableWidgetItem("Preparing"));//status
    }
}

void MainWindow::setSignalAddOrder(bool waitingToAddOrder, OrderType orderType)
{
    waitToAddOrder = waitingToAddOrder;
    tempOrderType = orderType;
}

void MainWindow::btnDeliver_clicked()
{
    int curRow{ui->listOrder->currentRow()};
    QTableWidgetItem *item{ui->listOrder->item(curRow, 0)};
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one order");
        return;
    }
    int id{item->text().toInt()};
    if(!orderList->setDelivering(id))
    {
        QMessageBox::warning(this, "Some thing go wrong", "Please check the status of this order");
        return;
    }
    ui->listOrder->item(curRow, 6)->setText("Delivering");
}


void MainWindow::btnComplete_clicked()
{
    int curRow{ui->listOrder->currentRow()};
    QTableWidgetItem *item{ui->listOrder->item(curRow, 0)};
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one order");
        return;
    }
    int id{item->text().toInt()};
    if(!orderList->setCompleted(id))
    {
        QMessageBox::warning(this, "Some thing go wrong", "Please check the status of this order");
        return;
    }
    ui->listOrder->item(curRow, 6)->setText("Completed");
    ui->listOrder->item(curRow, 4)->setText(orderList->at(id)->getCompletedDay());
}


void MainWindow::btnCancel_clicked()
{
    int curRow{ui->listOrder->currentRow()};
    QTableWidgetItem *item{ui->listOrder->item(curRow, 0)};
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one order");
        return;
    }
    int id{item->text().toInt()};
    if(!orderList->setCanceled(id))
    {
        QMessageBox::warning(this, "Some thing go wrong", "Please check the status of this order");
        return;
    }
    ui->listOrder->item(curRow, 6)->setText("Canceled");
    ui->listOrder->item(curRow, 4)->setText(orderList->at(id)->getCompletedDay());
}


void MainWindow::btnDelete_clicked()
{
    int curRow{ui->listOrder->currentRow()};
    QTableWidgetItem *item{ui->listOrder->item(curRow, 0)};
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one order");
        return;
    }
    int id{item->text().toInt()};
    orderList->remove(id);
    if(orderList->at(id) == nullptr)
    {
        ui->listOrder->removeRow(curRow);
        ui->listDetail->clearContents();
        ui->listDetail->setRowCount(0);
    }
    else
    {
        QMessageBox::warning(this, "Some thing go wrong", "Please check the status of this order");
    }
}


void MainWindow::listOrder_cellClicked(int row, int column)
{
    int id{ui->listOrder->item(row, 0)->text().toInt()};
    int rowCount = orderList->at(id)->getOrderDetail()->getLength();
    ui->listDetail->clearContents();
    ui->listDetail->setRowCount(rowCount);
    Node<OrderItem*> *ptr{orderList->at(id)->getOrderDetail()->getHead()};
    for(int i{}; i != rowCount; ++i)
    {
        ui->listDetail->setItem(i, 0, new QTableWidgetItem(QVariant(ptr->getData()->getItemId()).toString()));
        ui->listDetail->setItem(i, 1, new QTableWidgetItem(laptopList->at(ptr->getData()->getItemId())->getName()));
        ui->listDetail->setItem(i, 2, new QTableWidgetItem(QVariant(ptr->getData()->getQuantity()).toString()));
        ptr = ptr->getNext();
    }
}


void MainWindow::btnSearch_clicked()
{
    QString search{ui->lnSearch->text().trimmed().toLower()};
    QString show{ui->cbBoxShow->currentText()};
    int n{ui->listOrder->rowCount()};
    for(int i{}; i != n; ++i)
    {
        if(show == "All" || (show == ui->listOrder->item(i, 1)->text() || (show == ui->listOrder->item(i, 6)->text())))
        {
            if(search.isEmpty() || ui->listOrder->item(i, 2)->text().toLower().contains(search))
            {
                ui->listOrder->setRowHidden(i, false);
                continue;
            }
        }
        ui->listOrder->setRowHidden(i, true);
    }
}


void MainWindow::btnDetail_clicked()
{
    int curRow{ui->listOrder->currentRow()};
    QTableWidgetItem *item{ui->listOrder->item(curRow, 0)};
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one order");
        return;
    }
    int id{item->text().toInt()};
    emit showOrderDetail(orderList->at(id));
}

