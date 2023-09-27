#include "laptoplist.h"

void LaptopList::setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm)
{
    uiSetOrderForm = newUiSetOrderForm;
}

void LaptopList::fillOrderItemComboBox()
{
    uiSetOrderForm->cbBoxItem->clear();
    Node<Laptop*> *ptr;
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            uiSetOrderForm->cbBoxItem->addItem(ptr->getData()->getName() + " - " + QVariant(ptr->getData()->getItemId()).toString());
            ptr = ptr->getNext();
        }
    }
}

void LaptopList::fillOrderItemDetail(int id)
{
    Laptop *ptr = list[id];
    uiSetOrderForm->name->setText(ptr->getName());
    uiSetOrderForm->brand->setText(ptr->getBrand());
    uiSetOrderForm->price->setText(QVariant(ptr->getPrice()).toString());
    uiSetOrderForm->discount->setText(QVariant(ptr->getDiscount()).toString());
    uiSetOrderForm->quantity->setText(QVariant(ptr->getQuantity()).toString());
    uiSetOrderForm->sold->setText(QVariant(ptr->getSold()).toString());
    uiSetOrderForm->screen->setText(ptr->getScreenSize());
    uiSetOrderForm->cpu->setText(ptr->getCpu());
    uiSetOrderForm->ram->setText(ptr->getRam());
    uiSetOrderForm->hdd->setText(ptr->getHdd());
    uiSetOrderForm->ssd->setText(ptr->getSsd());
    uiSetOrderForm->weight->setText(ptr->getWeight());
    if(ptr->getImagePath().isEmpty())
    {
       uiSetOrderForm->lblImage->clear();
    }
    else
    {
        uiSetOrderForm->lblImage->setPixmap(QPixmap(ptr->getImagePath()));
        uiSetOrderForm->lblImage->setScaledContents(true);
    }
}

void LaptopList::load()
{
    {
        QFile inputFile("./database/deleted_id/laptop.txt");
        inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream input(&inputFile);
        QString line = input.readLine();
        input.flush();
        inputFile.close();
        if(!line.isEmpty())
        {
            MyStringList infor;
            infor.setString(line);
            for(int i{}; i != infor.getSize(); ++i)
            {
                deletedId.push(infor[i].toInt());
            }
        }
    }

    QFile inputFile("./database/laptop.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream input(&inputFile);

    while(!input.atEnd())
    {
        QString line = input.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        Laptop *laptop = new Laptop(infor[0].toInt(), infor[1], infor[2], infor[3].toDouble(), infor[4].toInt(), infor[5].toInt(), infor[6].toInt(), infor[7], infor[8], infor[9], infor[10], infor[11], infor[12], infor[13]);
        list.add(laptop);
        if(!brandList.isExist(laptop->getBrand()))
        {
            brandList.add(laptop->getBrand());;
            uiSetLaptopForm->cbBoxBrand->addItem(laptop->getBrand());
        }
        int rowCount = uiLaptopForm->listLaptop->rowCount();
        uiLaptopForm->listLaptop->insertRow(rowCount);
        uiLaptopForm->listLaptop->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(laptop->getItemId()).toString()));
        uiLaptopForm->listLaptop->setItem(rowCount, 1, new QTableWidgetItem(laptop->getName()));
        uiLaptopForm->listLaptop->setItem(rowCount, 2, new DoubleQTableWidgetItem(QVariant(laptop->getPrice()).toString()));
    }

    input.flush();
    inputFile.close();
}

void LaptopList::save()
{
    {
        QFile outputFile("./database/deleted_id/laptop.txt");
        outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream output(&outputFile);
        if(!deletedId.isEmpty())
        {
            output << deletedId.front();
            deletedId.pop();
        }
        while(!deletedId.isEmpty())
        {
            output << "," << deletedId.front();
            deletedId.pop();
        }
        output.flush();
        outputFile.close();
    }

    QFile outputFile("./database/laptop.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(&outputFile);

    Node<Laptop*> *ptr{};
    Laptop *laptop{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            laptop = ptr->getData();
            ptr = ptr->getNext();
//Laptop(int itemId, const QString &name, QString brand, double price, int discount, int quantity, int sold, const QString &imagePath, const QString &screenSize, const QString &cpu, const QString &ram, const QString &ssd, const QString &hdd, const QString &weight);

            output << laptop->getItemId()       << ","
                   << laptop->getName()         << ","
                   << laptop->getBrand()        << ","
                   << laptop->getPrice()        << ","
                   << laptop->getDiscount()     << ","
                   << laptop->getQuantity()     << ","
                   << laptop->getSold()         << ","
                   << laptop->getImagePath()    << ","
                   << laptop->getScreenSize()   << ","
                   << laptop->getCpu()          << ","
                   << laptop->getRam()          << ","
                   << laptop->getSsd()          << ","
                   << laptop->getHdd()          << ","
                   << laptop->getWeight()       << Qt::endl;
        }
    }

    output.flush();
    outputFile.close();
}

int LaptopList::takeKey(Laptop* const &laptop)
{
    return laptop->getItemId();
}

int LaptopList::takeKeyBrand(const QString &brand)
{
    int key{};
    for(int i{}; i != brand.size(); ++i)
    {
        key += brand.at(i).toLatin1();
    }
    return key;
}

bool LaptopList::isEqual(Laptop * const &l, Laptop * const &r)
{
    return l->getItemId() == r->getItemId();
}

bool LaptopList::isEqualBrand(const QString &l, const QString &r)
{
    return l == r;
}

void LaptopList::setLaptopForm(Ui::LaptopForm *newUiLaptopForm)
{
    uiLaptopForm = newUiLaptopForm;
}

Laptop *LaptopList::at(int id)
{
    return list[id];
}

void LaptopList::setSetLaptopForm(Ui::SetLaptopForm *newUiSetLaptopForm)
{
    uiSetLaptopForm = newUiSetLaptopForm;
}

Laptop *LaptopList::getJustForAdd() const
{
    return justForAdd;
}

LaptopList::LaptopList() :
    list(LaptopList::takeKey, LaptopList::isEqual), brandList(LaptopList::takeKeyBrand, LaptopList::isEqualBrand), justForAdd(nullptr),
    deletedId()
{}

LaptopList::~LaptopList()
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<Laptop*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
    if(justForAdd != nullptr)
        delete justForAdd;
}

void LaptopList::add()
{
    if(justForAdd != nullptr)
    {
        if(!deletedId.isEmpty())
        {
            deletedId.pop();
        }
        uiSetLaptopForm >> *justForAdd;
        list.add(justForAdd);
        if(!brandList.isExist(justForAdd->getBrand()))
        {
            brandList.add(justForAdd->getBrand());
            uiSetLaptopForm->cbBoxBrand->addItem(justForAdd->getBrand());
        }
        bool turnedOfSort{false};
        if(uiLaptopForm->listLaptop->isSortingEnabled())
        {
            uiLaptopForm->listLaptop->setSortingEnabled(false);
            turnedOfSort = true;
        }
        int rowCount = uiLaptopForm->listLaptop->rowCount();
        uiLaptopForm->listLaptop->insertRow(rowCount);
        uiLaptopForm->listLaptop->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(justForAdd->getItemId()).toString()));
        uiLaptopForm->listLaptop->setItem(rowCount, 1, new QTableWidgetItem(justForAdd->getName()));
        uiLaptopForm->listLaptop->setItem(rowCount, 2, new DoubleQTableWidgetItem(QVariant(justForAdd->getPrice()).toString()));
        if(turnedOfSort)
            uiLaptopForm->listLaptop->setSortingEnabled(true);

//        QFile outputFile("./database/laptop.txt");
//        outputFile.open(QIODevice::Text | QIODevice::Append);
//        QTextStream output(&outputFile);
//        output << justForAdd->getItemId()       << ","
//               << justForAdd->getName()         << ","
//               << justForAdd->getBrand()        << ","
//               << justForAdd->getPrice()        << ","
//               << justForAdd->getDiscount()     << ","
//               << justForAdd->getQuantity()     << ","
//               << justForAdd->getSold()         << ","
//               << justForAdd->getImagePath()    << ","
//               << justForAdd->getScreenSize()   << ","
//               << justForAdd->getCpu()          << ","
//               << justForAdd->getRam()          << ","
//               << justForAdd->getSsd()          << ","
//               << justForAdd->getHdd()          << ","
//               << justForAdd->getWeight()       << Qt::endl;
//        output.flush();
//        outputFile.close();

        justForAdd = nullptr;
    }
}

void LaptopList::showList()
{
    QString search = uiLaptopForm->lnSearch->text().trimmed().toLower();
    QString searchBy = uiLaptopForm->cbBoxSearchBy->currentText();
    bool meetSearch{false};
    int row = uiLaptopForm->listLaptop->rowCount();
    int id{-1};
    for(int i{}; i < row; ++i)
    {
        id = uiLaptopForm->listLaptop->item(i, 0)->text().toInt();
        meetSearch = search.isEmpty() ||
                (searchBy == "Name" && list[id]->getName().toLower().contains(search)) ||
                (searchBy == "Brand" && list[id]->getBrand().toLower().contains(search));
        if(meetSearch)
        {
            uiLaptopForm->listLaptop->setRowHidden(i, false);
        }
        else
        {
            uiLaptopForm->listLaptop->setRowHidden(i, true);
        }
    }
}

void LaptopList::showDetail(int id)
{
    uiLaptopForm << *list[id];
}

void LaptopList::set(int id)
{
    uiSetLaptopForm >> *list[id];
    if(!brandList.isExist(list[id]->getBrand()))
    {
        brandList.add(list[id]->getBrand());
        uiSetLaptopForm->cbBoxBrand->addItem(list[id]->getBrand());
    }
}

int LaptopList::getCount()
{
    return list.getCount();
}

void LaptopList::remove(int id)
{
    if(!(deletedId.isEmpty() && id == list.getCount() - 1))
        deletedId.push(id);
    QString delLap{list[id]->getName() + " - " + QVariant(id).toString()};
    list.remove(id);
}

void LaptopList::fillEdit(int id)
{
    uiSetLaptopForm << *list[id];
}

void LaptopList::prepareAdd()
{
    if(justForAdd == nullptr)
    {
        justForAdd = new Laptop();
    }
    if(!deletedId.isEmpty())
    {
        justForAdd->setItemId(deletedId.front());
    }
    else
    {
        justForAdd->setItemId(list.getCount());
    }
    uiSetLaptopForm << *justForAdd;
}

