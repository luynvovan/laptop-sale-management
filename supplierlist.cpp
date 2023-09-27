#include "supplierlist.h"

void SupplierList::setUiSupplierForm(Ui::SupplierForm *newUiSupplierForm)
{
    uiSupplierForm = newUiSupplierForm;
}

void SupplierList::setUiSetSupplierForm(Ui::SetSupplierForm *newUiSetSupplierForm)
{
    uiSetSupplierForm = newUiSetSupplierForm;
}

void SupplierList::add()
{
    if(justForAdd != nullptr)
    {
        if(deletedId.getLength() != 0)
        {
            deletedId.pop();
        }

        uiSetSupplierForm >> *justForAdd;
        list.add(justForAdd);

        int rowCount = uiSupplierForm->listSupplier->rowCount();
        uiSupplierForm->listSupplier->insertRow(rowCount);
        uiSupplierForm->listSupplier->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(justForAdd->getId()).toString()));
        uiSupplierForm->listSupplier->setItem(rowCount, 1, new QTableWidgetItem(justForAdd->getName()));

//        QFile outputFile("./database/supplier.txt");
//        outputFile.open(QIODevice::Text | QIODevice::Append);
//        QTextStream output(&outputFile);
//        output << justForAdd->getId()             << ","
//               << justForAdd->getName()           << ","
//               << justForAdd->getPhoneNumber()    << ","
//               << justForAdd->getCompletedOrder() << ","
//               << justForAdd->getTotalPaid()      << Qt::endl;
//        output.flush();
//        outputFile.close();

        justForAdd = nullptr;
    }
}

void SupplierList::showList()
{
    QString search = uiSupplierForm->lnSearch->text().trimmed().toLower();
    bool emptySearch = search.isEmpty();
    int rowCount = uiSupplierForm->listSupplier->rowCount();
    for(int i{}; i < rowCount; ++i)
    {
        if(emptySearch || uiSupplierForm->listSupplier->item(i, 1)->text().toLower().contains(search))
        {
            uiSupplierForm->listSupplier->setRowHidden(i, false);
        }
        else
        {
            uiSupplierForm->listSupplier->setRowHidden(i, true);
        }
    }
}

void SupplierList::showDetail(int id)
{
    uiSupplierForm << *list[id];
}

void SupplierList::set(int id)
{
    uiSetSupplierForm >> *list[id];
}

void SupplierList::remove(int id)
{
    if(!(deletedId.isEmpty() && id == list.getCount() - 1))
        deletedId.push(id);
    list.remove(id);
}

int SupplierList::getCount()
{
    return list.getCount();
}

Supplier *SupplierList::at(int id)
{
    return list[id];
}

void SupplierList::prepareAdd()
{
    if(justForAdd == nullptr)
        justForAdd = new Supplier();
    if(deletedId.getLength() != 0)
    {
        justForAdd->setId(deletedId.front());
    }
    else
    {
        justForAdd->setId(list.getCount());
    }
    uiSetSupplierForm << *justForAdd;
}

void SupplierList::fillEdit(int id)
{
    uiSetSupplierForm << *list[id];
}

SupplierList::SupplierList() :
    list(SupplierList::takeKey, SupplierList::isEqual), justForAdd(nullptr), deletedId()
{}

Supplier *SupplierList::getJustForAdd() const
{
    return justForAdd;
}

void SupplierList::setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm)
{
    uiSetOrderForm = newUiSetOrderForm;
}

void SupplierList::fillOrderSupplierComboBox()
{
    Node<Supplier*> *ptr{nullptr};
    uiSetOrderForm->cbBoxCustomer->clear();
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            uiSetOrderForm->cbBoxCustomer->addItem(ptr->getData()->getName() + " - " + QVariant(ptr->getData()->getId()).toString());
            ptr = ptr->getNext();
        }
    }
}

void SupplierList::fillOrderSupplierInfo(int id)
{
    Supplier *slier = list[id];
    uiSetOrderForm->lnPhone->setText(slier->getPhoneNumber());
    uiSetOrderForm->lnAddress->setText("---");
    uiSetOrderForm->lblID->setText(QVariant(id).toString());
    uiSetOrderForm->lblCompleted->setText(QVariant(slier->getCompletedOrder()).toString());
    uiSetOrderForm->lblPaid->setText(QVariant(slier->getTotalPaid()).toString());
    uiSetOrderForm->lblPoint->setText("---");
}

void SupplierList::load()
{
    {
        QFile inputFile("./database/deleted_id/supplier.txt");
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

    QFile inputFile("./database/supplier.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream input(&inputFile);

    while(!input.atEnd())
    {
        QString line = input.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        Supplier *supplier = new Supplier(infor[0].toInt(), infor[1], infor[2], infor[3].toInt(), infor[4].toDouble());
        list.add(supplier);

        int rowCount = uiSupplierForm->listSupplier->rowCount();
        uiSupplierForm->listSupplier->insertRow(rowCount);
        uiSupplierForm->listSupplier->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(supplier->getId()).toString()));
        uiSupplierForm->listSupplier->setItem(rowCount, 1, new QTableWidgetItem(supplier->getName()));
    }

    input.flush();
    inputFile.close();
}

void SupplierList::save()
{
    {
        QFile outputFile("./database/deleted_id/supplier.txt");
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

    QFile outputFile("./database/supplier.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(&outputFile);

    Node<Supplier*> *ptr{};
    Supplier *supplier{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            supplier = ptr->getData();
            ptr = ptr->getNext();
//int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid
            output << supplier->getId()             << ","
                   << supplier->getName()           << ","
                   << supplier->getPhoneNumber()    << ","
                   << supplier->getCompletedOrder() << ","
                   << supplier->getTotalPaid()      << Qt::endl;
        }
    }

    output.flush();
    outputFile.close();
}

int SupplierList::takeKey(Supplier* const &supplier)
{
    return supplier->getId();
}

bool SupplierList::isEqual(Supplier * const &l, Supplier * const &r)
{
    return l->getId() == r->getId();
}

SupplierList::~SupplierList()
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<Supplier*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
    if(justForAdd != nullptr)
        delete justForAdd;
}
