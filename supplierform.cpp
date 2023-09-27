#include "supplierform.h"
#include "ui_supplierform.h"

SupplierForm::SupplierForm(SupplierList *supplierList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupplierForm),
    supplierList(supplierList)
{
    ui->setupUi(this);
    setSupplierForm = new SetSupplierForm(supplierList, this);
    supplierList->setUiSupplierForm(ui);
    supplierList->load();
    ui->listSupplier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->btnAdd->setDefault(true);

    connect(ui->btnSearch, &QPushButton::clicked, this, &SupplierForm::btnSearch_clicked);
    connect(ui->btnAdd, &QPushButton::clicked, this, &SupplierForm::btnAdd_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &SupplierForm::btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &SupplierForm::btnDelete_clicked);
    connect(ui->listSupplier, &QTableWidget::cellClicked, this, &SupplierForm::listSupplier_cellClicked);
}

SupplierForm::~SupplierForm()
{
    delete ui;
}

void SupplierForm::showThis()
{
    ui->lnSearch->clear();
    btnSearch_clicked();
    this->exec();
}

void SupplierForm::btnSearch_clicked()
{
    ui->btnSearch->setDisabled(true);
    ui->btnAdd->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnEdit->setDisabled(true);

    clearDetail();
    supplierList->showList();

    ui->btnSearch->setDisabled(false);
    ui->btnAdd->setDisabled(false);
    if(StaffList::getNowLogin()->getType() == admin)
        ui->btnDelete->setDisabled(false);
    ui->btnEdit->setDisabled(false);
}


void SupplierForm::btnAdd_clicked()
{
    supplierList->prepareAdd();
    if(QDialog::Accepted == setSupplierForm->exec())
    {
        supplierList->add();
    }
}


void SupplierForm::btnEdit_clicked()
{
    int curRow = ui->listSupplier->currentRow();
    QTableWidgetItem *item = ui->listSupplier->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    int id = item->text().toInt();
    supplierList->fillEdit(id);
    if(QDialog::Accepted == setSupplierForm->exec())
    {
        bool turnedOfSort{false};
        if(ui->listSupplier->isSortingEnabled())
        {
            turnedOfSort = true;
            ui->listSupplier->setSortingEnabled(false);
        }

        supplierList->set(id);
        ui->listSupplier->item(curRow, 1)->setText(supplierList->at(id)->getName());
        supplierList->showDetail(id);

        if(turnedOfSort)
            ui->listSupplier->setSortingEnabled(true);
    }
}


void SupplierForm::btnDelete_clicked()
{
    int curRow = ui->listSupplier->currentRow();
    QTableWidgetItem *item = ui->listSupplier->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    emit sendSupplierId(item->text().toInt());
}

void SupplierForm::clearDetail()
{
    ui->name->clear();
    ui->phone->clear();
    ui->completed->clear();
    ui->paid->clear();
}

void SupplierForm::goDelete(int id, bool stat)
{
    if(stat == false)
    {
        supplierList->remove(id);
        ui->listSupplier->removeRow(ui->listSupplier->currentRow());
        clearDetail();
    }
    else
    {
        QMessageBox::warning(this, "Can't delete", "Exist order that contain this");
    }
}


void SupplierForm::listSupplier_cellClicked(int row, int column)
{
    int id = ui->listSupplier->item(row, 0)->text().toInt();
    supplierList->showDetail(id);
}

