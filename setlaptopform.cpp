#include "setlaptopform.h"
#include "ui_setlaptopform.h"

SetLaptopForm::SetLaptopForm(LaptopList *laptopList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetLaptopForm),
    laptopList(laptopList)
{
    ui->setupUi(this);
    ui->lblImagePath->setVisible(false);
    ui->lblImagePath->clear();
    laptopList->setSetLaptopForm(ui);
    setValidInput();
    QDir imgDir("./images");
    if(!imgDir.exists())
    {
        QDir().mkdir("./images");
    }
    laptopList->load();
    ui->btnOk->setDefault(true);

    connect(ui->btnOk, &QPushButton::clicked, this, &SetLaptopForm::btnOk_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &SetLaptopForm::btnCancel_clicked);
    connect(ui->btnAddImage, &QPushButton::clicked, this, &SetLaptopForm::btnAddImage_clicked);
}

SetLaptopForm::~SetLaptopForm()
{
    delete ui;
}

void SetLaptopForm::btnOk_clicked()
{
    if(isValidInput())
        this->accept();
    else
        QMessageBox::warning(this, "Invalid input", "Please fill all in the right way");
}

void SetLaptopForm::btnCancel_clicked()
{
    this->close();
}

void SetLaptopForm::btnAddImage_clicked()
{
    QString tmp = QFileDialog::getOpenFileName(this, "Open Image", "./", "Image Files (*.png *.jpg)");
    if(!tmp.isEmpty())
    {
        ui->lblImagePath->setText(tmp);
        QPixmap pixMap(tmp);
        ui->lblImage->setPixmap(pixMap);
        ui->lblImage->setScaledContents(true);
    }
}

void SetLaptopForm::setValidInput()
{
    ui->lnPrice->setValidator(new QDoubleValidator(0, 1000, 2, this));
    ui->lnScreen->setValidator(ui->lnPrice->validator());
    ui->lnRam->setValidator(new QIntValidator(0, 1000, this));
    ui->lnSsd->setValidator(ui->lnRam->validator());
    ui->lnHdd->setValidator(ui->lnRam->validator());
    ui->lnWeight->setValidator(ui->lnPrice->validator());
}

bool SetLaptopForm::isValidInput()
{
    if(ui->lnName->text().isEmpty() ||
       ui->cbBoxBrand->currentText().isEmpty() ||
       ui->lnScreen->text().isEmpty() ||
       ui->lnScreen->text().isEmpty() ||
       ui->lnCpu->text().isEmpty() ||
       ui->lnRam->text().isEmpty() ||
       ui->lnSsd->text().isEmpty() ||
       ui->lnHdd->text().isEmpty() ||
       ui->lnWeight->text().isEmpty()
            )
       return false;
    return true;
}

void SetLaptopForm::closeEvent(QCloseEvent *event)
{
    ui->lblImagePath->clear();
}

