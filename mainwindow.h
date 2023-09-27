#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginform.h"
#include "laptopform.h"
#include "customerform.h"
#include "supplierform.h"
#include "staffform.h"
#include "setorderform.h"
#include "salesorpurchaseorder.h"
#include "orderdetailform.h"
#include "changepasswordform.h"
#include "holdexist.h"
#include "changestaffinfor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginForm *loginForm;
    LaptopForm *laptopForm;
    LaptopList *laptopList;
    CustomerForm *customerForm;
    CustomerList *customerList;
    SupplierForm *supplierForm;
    SupplierList *supplierList;
    StaffForm *staffForm;
    StaffList *staffList;
    SetOrderForm *setOrderForm;
    OrderList *orderList;
    SalesOrPurchaseOrder *saleOrPurchaseOrder;
    OrderDetailForm *orderDetailForm;
    ChangePasswordForm *changePasswordForm;
    void setGui(const UserType &usertype);
    OrderType tempOrderType;
    bool waitToAddOrder;
    HoldExist *holdExist;
    ChangeStaffInfor *changeStaffInfor;
    void closeEvent(QCloseEvent *event) override;
private slots:
    void accountMenu_clicked(QAction *action);
    void manegementMenu_clicked(QAction *action);
    void btnAddOrder_clicked();
    void setSignalAddOrder(bool waitingToAddOrder, OrderType orderType);

    void btnDeliver_clicked();

    void btnComplete_clicked();

    void btnCancel_clicked();

    void btnDelete_clicked();

    void listOrder_cellClicked(int row, int column);

    void btnSearch_clicked();

    void btnDetail_clicked();

signals:
    void showOrderDetail(Order *order);
};
#endif // MAINWINDOW_H
