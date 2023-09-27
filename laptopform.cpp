#include "laptopform.h"
#include "./ui_laptopform.h"

LaptopForm::LaptopForm(LaptopList *laptopList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LaptopForm),
    laptopList(laptopList)
{
    ui->setupUi(this);
    ui->listLaptop->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    laptopList->setLaptopForm(ui);
    setLaptopForm = new SetLaptopForm(laptopList, this);
    ui->btnSearch->setDefault(true);

    connect(ui->btnSearch, &QPushButton::clicked, this, &LaptopForm::btnSearch_clicked);
    connect(ui->btnAdd, &QPushButton::clicked, this, &LaptopForm::btnAdd_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &LaptopForm::btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &LaptopForm::btnDelete_clicked);
    connect(ui->listLaptop, &QTableWidget::cellClicked, this, &LaptopForm::listLaptop_cellClicked);
}

LaptopForm::~LaptopForm()
{
    delete ui;
}

void LaptopForm::btnAdd_clicked()
{
    laptopList->prepareAdd();
    if(QDialog::Accepted == setLaptopForm->exec())
    {
        laptopList->add();
    }
}


void LaptopForm::btnEdit_clicked()
{
    int curRow = ui->listLaptop->currentRow();
    QTableWidgetItem *item = ui->listLaptop->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    int id = item->text().toInt();
    laptopList->fillEdit(id);
    if(QDialog::Accepted == setLaptopForm->exec())
    {
        bool turnedOfSort{false};
        if(ui->listLaptop->isSortingEnabled())
        {
            ui->listLaptop->setSortingEnabled(false);
            turnedOfSort = true;
        }
        laptopList->set(id);
        laptopList->showDetail(id);
        Laptop *lt = laptopList->at(id);
        ui->listLaptop->item(curRow, 1)->setText(lt->getName());
        ui->listLaptop->item(curRow, 2)->setText(QVariant(lt->getPrice()).toString());
        if(turnedOfSort)
            ui->listLaptop->setSortingEnabled(true);
    }
}
void LaptopForm::showThis()
{
    ui->lnSearch->clear();
    ui->cbBoxSearchBy->setCurrentIndex(0);

    btnSearch_clicked();

    this->exec();
}

void LaptopForm::btnSearch_clicked()
{
    ui->btnSearch->setDisabled(true);
    ui->btnAdd->setDisabled(true);
    ui->btnDelete->setDisabled(true);
    ui->btnEdit->setDisabled(true);

    clearDetail();
    laptopList->showList();

    ui->btnSearch->setDisabled(false);
    ui->btnAdd->setDisabled(false);
    if(StaffList::getNowLogin()->getType() == admin)
        ui->btnDelete->setDisabled(false);
    ui->btnEdit->setDisabled(false);
}


void LaptopForm::btnDelete_clicked()
{
    int curRow = ui->listLaptop->currentRow();
    QTableWidgetItem *item = ui->listLaptop->item(curRow, 0);
    if(item == nullptr)
    {
        QMessageBox::warning(this, "No one was chosen", "Please choose one");
        return;
    }
    emit sendLaptopId(item->text().toInt());
}

void LaptopForm::clearDetail()
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
    ui->ssd->clear();
    ui->hdd->clear();
    ui->weight->clear();
    ui->lblImage->clear();
}

void LaptopForm::goDelete(int id, bool stat)
{
    if(stat == false)
    {
        laptopList->remove(id);
        ui->listLaptop->removeRow(ui->listLaptop->currentRow());
        clearDetail();
    }
    else
    {
        QMessageBox::warning(this, "Can't delete", "Exist order that contain this");
    }
}


void LaptopForm::listLaptop_cellClicked(int row, int column)
{
    laptopList->showDetail(ui->listLaptop->item(row, 0)->text().toInt());
}

