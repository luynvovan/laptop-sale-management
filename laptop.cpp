#include "laptop.h"

const QString &Laptop::getScreenSize() const
{
    return screenSize;
}

void Laptop::setScreenSize(const QString &newScreenSize)
{
    screenSize = newScreenSize;
}

const QString &Laptop::getCpu() const
{
    return cpu;
}

void Laptop::setCpu(const QString &newCpu)
{
    cpu = newCpu;
}

const QString &Laptop::getRam() const
{
    return ram;
}

void Laptop::setRam(const QString &newRam)
{
    ram = newRam;
}

const QString &Laptop::getSsd() const
{
    return ssd;
}

void Laptop::setSsd(const QString &newSsd)
{
    ssd = newSsd;
}

const QString &Laptop::getHdd() const
{
    return hdd;
}

void Laptop::setHdd(const QString &newHdd)
{
    hdd = newHdd;
}

const QString &Laptop::getWeight() const
{
    return weight;
}

void Laptop::setWeight(const QString &newWeight)
{
    weight = newWeight;
}

Laptop::Laptop() :
    Item(),
    cpu(""),
    ram(""),
    ssd(""),
    hdd(""),
    weight("")
{}

Laptop::Laptop(const Laptop &laptop) :
    Item(laptop),
    screenSize(laptop.screenSize),
    cpu(laptop.cpu),
    ram(laptop.ram),
    ssd(laptop.ssd),
    hdd(laptop.hdd),
    weight(laptop.weight)
{}

Laptop::Laptop(int itemId, const QString &name, QString brand, double price, int discount, int quantity, int sold, const QString &imagePath, const QString &screenSize, const QString &cpu, const QString &ram, const QString &ssd, const QString &hdd, const QString &weight) :
    Item(itemId, name, brand, price, discount, quantity, sold, imagePath),
    screenSize(screenSize),
    cpu(cpu),
    ram(ram),
    ssd(ssd),
    hdd(hdd),
    weight(weight)
{}

Laptop &Laptop::operator=(const Laptop &other)
{
    this->Item::operator=(other);
    this->screenSize = other.screenSize;
    this->cpu = other.cpu;
    this->ram = other.ram;
    this->ssd = other.ssd;
    this->hdd = other.hdd;
    this->weight = other.weight;
    return *this;
}

void operator<<(Ui::SetLaptopForm *ui, const Laptop &laptop)
{
    ui->groupBox->setTitle(QString("Infomation - ") + "ID(" + QVariant(laptop.getItemId()).toString() + ")");
    ui->lnName->setText(laptop.getName());
    ui->cbBoxBrand->setCurrentText(laptop.getBrand());
    ui->lnPrice->setText(QVariant(laptop.getPrice()).toString());
    ui->lnDiscount->setValue(laptop.getDiscount());
    ui->spinBoxQuantity->setValue(laptop.getQuantity());
    ui->spinBoxSold->setValue(laptop.getSold());
    if(StaffList::getNowLogin()->getType() == admin)
    {
        ui->spinBoxQuantity->setDisabled(false);
        ui->spinBoxSold->setDisabled(false);
    }
    else
    {
        ui->spinBoxQuantity->setDisabled(true);
        ui->spinBoxSold->setDisabled(true);
    }
    ui->lnScreen->setText(laptop.screenSize.left(laptop.screenSize.size() - 5));
    ui->lnCpu->setText(laptop.cpu);
    ui->lnRam->setText(laptop.ram.left(laptop.ram.size() - 2));
    ui->lnSsd->setText(laptop.ssd.left(laptop.ssd.size() - 2));
    ui->lnHdd->setText(laptop.hdd.left(laptop.hdd.size() - 2));
    ui->lnWeight->setText(laptop.weight.left(laptop.weight.size() - 3));
    if(!laptop.getImagePath().isEmpty())
    {
        QPixmap pixMap(laptop.getImagePath());
        ui->lblImage->setPixmap(pixMap);
        ui->lblImage->setScaledContents(true);
    }
    else
    {
        ui->lblImagePath->clear();
        ui->lblImage->clear();
    }
}
void operator>>(Ui::SetLaptopForm *ui, Laptop &laptop)
{
    laptop.setName(ui->lnName->text());
    laptop.setBrand(ui->cbBoxBrand->currentText());
    laptop.setPrice(QVariant(ui->lnPrice->text()).toDouble());
    laptop.setDiscount(ui->lnDiscount->value());
    laptop.setQuantity(ui->spinBoxQuantity->value());
    laptop.setSold(ui->spinBoxSold->value());
    laptop.setScreenSize(ui->lnScreen->text() + " Inch");
    laptop.setCpu(ui->lnCpu->text());
    laptop.setRam(ui->lnRam->text() + "GB");
    laptop.setSsd(ui->lnSsd->text() + "GB");
    laptop.setHdd(ui->lnHdd->text() + "GB");
    laptop.setWeight(ui->lnWeight->text() + " Kg");
    QString lblImgPth = ui->lblImagePath->text();
    if(!lblImgPth.isEmpty())
    {
        QString newImagePath = QString("./images/") + "img_" + QVariant(laptop.getItemId()).toString() + lblImgPth.right(lblImgPth.size() - lblImgPth.lastIndexOf("."));
        if(!laptop.getImagePath().isEmpty())
        {
            if(QFile::exists(laptop.getImagePath()))
                QFile::remove(laptop.getImagePath());
        }
        QFile::copy(lblImgPth, newImagePath);
        laptop.setImagePath(newImagePath);
        ui->lblImagePath->clear();
    }
}

void operator<<(Ui::LaptopForm *ui, const Laptop &laptop)
{
    ui->name->setText(laptop.getName());
    ui->brand->setText(laptop.getBrand());
    ui->price->setText(QVariant(laptop.getPrice()).toString());
    ui->discount->setText(QVariant(laptop.getDiscount()).toString());
    ui->quantity->setText(QVariant(laptop.getQuantity()).toString());
    ui->sold->setText(QVariant(laptop.getSold()).toString());
    ui->screen->setText(laptop.screenSize);
    ui->cpu->setText(laptop.cpu);
    ui->ram->setText(laptop.ram);
    ui->ssd->setText(laptop.ssd);
    ui->hdd->setText(laptop.hdd);
    ui->weight->setText(laptop.weight);
    ui->lblImage->clear();
    if(!laptop.getImagePath().isEmpty())
    {
        QPixmap pixMap(laptop.getImagePath());
        ui->lblImage->setPixmap(pixMap);
        ui->lblImage->setScaledContents(true);
    }
}
