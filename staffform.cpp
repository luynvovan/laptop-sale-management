#include "staffform.h"
#include "ui_staffform.h"

StaffForm::StaffForm(StaffList *staffList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaffForm),
    staffList(staffList)
{
    ui->setupUi(this);
    setStaffForm = new SetStaffForm(staffList, this);
    staffList->setUiStaffForm(ui);
    staffList->load();
    ui->listStaff->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->btnSearch, &QPushButton::clicked, this, &StaffForm::btnSearch_clicked);
    connect(ui->btnAdd, &QPushButton::clicked, this, &StaffForm::btnAdd_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &StaffForm::btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &StaffForm::btnDelete_clicked);
    connect(ui->listStaff, &QTableWidget::cellClicked, this, &StaffForm::listStaff_cellClicked);
}

StaffForm::~StaffForm()
{
    delete ui;
}

void StaffForm::showThis()
{
    ui->lnSearch->clear();
    btnSearch_clicked();
    this->exec();
}

void StaffForm::btnSearch_clicked()
{
    ui->btnAdd->setDisabled(true);
    ui->btnEdit->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnSearch->setDisabled(true);

    clearDetail();
    staffList->showList();

    if(StaffList::getNowLogin()->getType() == admin)
    {
        ui->btnAdd->setDisabled(false);
        ui->btnEdit->setDisabled(false);
        ui->btnDelete->setDisabled(false);
    }
    ui->btnSearch->setDisabled(false);
}


void StaffForm::btnAdd_clicked()
{
    staffList->prepareAdd();
    setStaffForm->prepareAdd();
    if(QDialog::Accepted == setStaffForm->exec())
    {
        staffList->add();
    }
}


void StaffForm::btnEdit_clicked()
{
    int curRow = ui->listStaff->currentRow();
    QTableWidgetItem *item = ui->listStaff->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    int id = item->text().toInt();
    staffList->fillEdit(id);
    setStaffForm->prepareEdit();
    if(QDialog::Accepted == setStaffForm->exec())
    {
        bool turnedOfSort{false};
        if(ui->listStaff->isSortingEnabled())
        {
            ui->listStaff->setSortingEnabled(false);
            turnedOfSort = true;
        }
        staffList->set(id);
        staffList->showDetail(id);
        Staff *st = staffList->at(id);
        ui->listStaff->item(curRow, 1)->setText(st->getName());
        if(turnedOfSort)
            ui->listStaff->setSortingEnabled(true);
        if(staffList->at(id)->getType() == admin)
        {
            ui->btnDelete->setDisabled(true);
            ui->btnEdit->setDisabled(true);
        }
        else
        {
            ui->btnDelete->setDisabled(false);
            ui->btnEdit->setDisabled(false);
        }
    }
}


void StaffForm::btnDelete_clicked()
{
    int curRow = ui->listStaff->currentRow();
    QTableWidgetItem *item = ui->listStaff->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    emit sendStaffId(item->text().toInt());
}

void StaffForm::clearDetail()
{
    ui->name->clear();
    ui->phone->clear();
    ui->completed->clear();
    ui->paid->clear();
    ui->username->clear();
    ui->usertype->clear();
    ui->gender->clear();
    ui->age->clear();
    ui->address->clear();
}

void StaffForm::goDelete(int id, bool stat)
{
    if(stat == false)
    {
        staffList->remove(id);
        ui->listStaff->removeRow(ui->listStaff->currentRow());
        clearDetail();
    }
    else
    {
        QMessageBox::warning(this, "Can't delete", "Exist order that contain this");
    }
}

void StaffForm::listStaff_cellClicked(int row, int column)
{
    int id = ui->listStaff->item(row, 0)->text().toInt();
    if(StaffList::getNowLogin()->getType() == admin)
    {
        if(staffList->at(id)->getType() == admin)
        {
            ui->btnDelete->setDisabled(true);
            ui->btnEdit->setDisabled(true);
        }
        else
        {
            ui->btnDelete->setDisabled(false);
            ui->btnEdit->setDisabled(false);
        }
    }
    staffList->showDetail(id);
    staffList->showDetail(ui->listStaff->item(row, 0)->text().toInt());
}

