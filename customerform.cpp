#include "customerform.h"
#include "ui_customerform.h"

CustomerForm::CustomerForm(CustomerList *customerList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerForm),
    customerList(customerList)
{
    ui->setupUi(this);
    setCustomerForm = new SetCustomerForm(customerList, this);
    customerList->setUiCustomerForm(ui);
    customerList->load();
    ui->listCustomer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->btnSearch->setDefault(true);
    connect(ui->btnSearch, &QPushButton::clicked, this, &CustomerForm::btnSearch_clicked);
    connect(ui->btnAdd, &QPushButton::clicked, this, &CustomerForm::btnAdd_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &CustomerForm::btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &CustomerForm::btnDelete_clicked);
    connect(ui->listCustomer, &QTableWidget::cellClicked, this, &CustomerForm::listCustomer_cellClicked);
}

CustomerForm::~CustomerForm()
{
    delete ui;
}

void CustomerForm::showThis()
{
    ui->lnSearch->clear();
    btnSearch_clicked();
    this->exec();
}

void CustomerForm::btnAdd_clicked()
{
    customerList->prepareAdd();
    if(QDialog::Accepted == setCustomerForm->exec())
    {
        customerList->add();
    }
}


void CustomerForm::btnEdit_clicked()
{
    int curRow = ui->listCustomer->currentRow();
    QTableWidgetItem *item = ui->listCustomer->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    int id = item->text().toInt();
    customerList->fillEdit(id);
    if(QDialog::Accepted == setCustomerForm->exec())
    {
        bool turnedOfSort{false};
        if(ui->listCustomer->isSortingEnabled())
        {
            turnedOfSort = true;
            ui->listCustomer->setSortingEnabled(false);
        }

        customerList->set(id);
        customerList->showDetail(id);
        ui->listCustomer->item(curRow, 1)->setText(customerList->at(id)->getName());

        if(turnedOfSort)
        {
            ui->listCustomer->setSortingEnabled(true);
        }
    }
}


void CustomerForm::btnSearch_clicked()
{
    ui->btnSearch->setDisabled(true);
    ui->btnAdd->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnEdit->setDisabled(true);

    clearDetail();
    customerList->showList();

    ui->btnSearch->setDisabled(false);
    ui->btnAdd->setDisabled(false);
    if(StaffList::getNowLogin()->getType() == admin)
        ui->btnDelete->setDisabled(false);
    ui->btnEdit->setDisabled(false);
}

void CustomerForm::btnDelete_clicked()
{
    int curRow = ui->listCustomer->currentRow();
    QTableWidgetItem *item = ui->listCustomer->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    emit sendCustomerId(item->text().toInt());
}

void CustomerForm::clearDetail()
{
    ui->name->clear();
    ui->gender->clear();
    ui->age->clear();
    ui->phone->clear();
    ui->address->clear();
    ui->completed->clear();
    ui->totalPaid->clear();
    ui->point->clear();
}

void CustomerForm::goDelete(int id, bool stat)
{
    if(stat == false)
    {
        customerList->remove(id);
        ui->listCustomer->removeRow(ui->listCustomer->currentRow());
        clearDetail();
    }
    else
    {
        QMessageBox::warning(this, "Can't delete", "Exist order that contain this");
    }
}


void CustomerForm::listCustomer_cellClicked(int row, int column)
{
    customerList->showDetail(ui->listCustomer->item(row, 0)->text().toInt());
}

