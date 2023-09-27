#include "customerlist.h"
#include "qdir.h"

void CustomerList::setUiSetOrderForm(Ui::SetOrderForm *newUiSetOrderForm)
{
    uiSetOrderForm = newUiSetOrderForm;
}

void CustomerList::fillOrderCustomerComboBox()
{
    Node<Customer*> *ptr{nullptr};
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

void CustomerList::fillOrderCustomerInfor(int id)
{
    Customer *cmer = list[id];
    uiSetOrderForm->lnPhone->setText(cmer->getPhoneNumber());
    uiSetOrderForm->lnAddress->setText(cmer->getAddress());
    uiSetOrderForm->lblID->setText(QVariant(id).toString());
    uiSetOrderForm->lblCompleted->setText(QVariant(cmer->getCompletedOrder()).toString());
    uiSetOrderForm->lblPaid->setText(QVariant(cmer->getTotalPaid()).toString());
    uiSetOrderForm->lblPoint->setText(QVariant(cmer->getPoint()).toString());
}

void CustomerList::load()
{
    {
        QFile inputFile("./database/deleted_id/customer.txt");
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

    QFile inputFile("./database/customer.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream input(&inputFile);

    while(!input.atEnd())
    {
        QString line = input.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        Customer *customer = new Customer(infor[0].toInt(), infor[1], infor[2], infor[3].toInt(), infor[4].toDouble(), infor[5] == "0" ? male : female, infor[6].toInt(), infor[7], infor[8].toInt());
        list.add(customer);
        int curRow = uiCustomerForm->listCustomer->rowCount();
        uiCustomerForm->listCustomer->insertRow(curRow);
        uiCustomerForm->listCustomer->setItem(curRow, 0, new IntQTableWidgetItem(QVariant(customer->getId()).toString()));
        uiCustomerForm->listCustomer->setItem(curRow, 1, new QTableWidgetItem(customer->getName()));
    }

    input.flush();
    inputFile.close();
}

void CustomerList::save()
{
    {
        QFile outputFile("./database/deleted_id/customer.txt");
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


    QFile outputFile("./database/customer.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(&outputFile);

    Node<Customer*> *ptr{};
    Customer *customer{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            customer = ptr->getData();
            ptr = ptr->getNext();
            output << customer->getId()             << ","
                   << customer->getName()           << ","
                   << customer->getPhoneNumber()    << ","
                   << customer->getCompletedOrder() << ","
                   << customer->getTotalPaid()      << ","
                   << customer->getGender()         << ","
                   << customer->getAge()            << ","
                   << customer->getAddress()        << ","
                   << customer->getPoint()          << Qt::endl;
        }
    }
    output.flush();
    outputFile.close();
}

int CustomerList::takeKey(Customer* const &customer)
{
    return customer->getId();
}

bool CustomerList::isEqual(Customer * const &l, Customer * const &r)
{
    return l->getId() == r->getId();
}

void CustomerList::setUiCustomerForm(Ui::CustomerForm *newUiCustomerForm)
{
    uiCustomerForm = newUiCustomerForm;
}

void CustomerList::setUiSetCustomerForm(Ui::SetCustomerForm *newUiSetCustomerForm)
{
    uiSetCustomerForm = newUiSetCustomerForm;
}

Customer *CustomerList::getJustForAdd() const
{
    return justForAdd;
}

CustomerList::CustomerList() :
    list(CustomerList::takeKey, CustomerList::isEqual), justForAdd(nullptr), deletedId()
{}

CustomerList::~CustomerList()
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<Customer*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
    if(justForAdd != nullptr)
        delete justForAdd;
}

void CustomerList::add()
{
    if(justForAdd != nullptr)
    {
        if(!deletedId.isEmpty())
        {
            deletedId.pop();
        }
        uiSetCustomerForm >> *justForAdd;
        list.add(justForAdd);

        bool turnedOfSort{false};
        if(uiCustomerForm->listCustomer->isSortingEnabled())
        {
            uiCustomerForm->listCustomer->setSortingEnabled(false);
            turnedOfSort = true;
        }

        int curRow = uiCustomerForm->listCustomer->rowCount();
        uiCustomerForm->listCustomer->insertRow(curRow);
        uiCustomerForm->listCustomer->setItem(curRow, 0, new IntQTableWidgetItem(QVariant(justForAdd->getId()).toString()));
        uiCustomerForm->listCustomer->setItem(curRow, 1, new QTableWidgetItem(justForAdd->getName()));
        if(turnedOfSort)
            uiCustomerForm->listCustomer->setSortingEnabled(true);

//        QFile outputFile("./database/customer.txt");
//        outputFile.open(QIODevice::Text | QIODevice::Append);
//        QTextStream output(&outputFile);
//        output << justForAdd->getId()             << ","
//               << justForAdd->getName()           << ","
//               << justForAdd->getPhoneNumber()    << ","
//               << justForAdd->getCompletedOrder() << ","
//               << justForAdd->getTotalPaid()      << ","
//               << justForAdd->getGender()         << ","
//               << justForAdd->getAge()            << ","
//               << justForAdd->getAddress()        << ","
//               << justForAdd->getPoint()          << Qt::endl;
//        output.flush();
//        outputFile.close();

        justForAdd = nullptr;
    }
}

void CustomerList::showList()
{
    QString search = uiCustomerForm->lnSearch->text().trimmed().toLower();
    int rowCount = uiCustomerForm->listCustomer->rowCount();
    for(int i{}; i != rowCount; ++i)
    {
        if(search.isEmpty() || uiCustomerForm->listCustomer->item(i, 1)->text().toLower().contains(search))
        {
            uiCustomerForm->listCustomer->setRowHidden(i, false);
        }
        else
        {
            uiCustomerForm->listCustomer->setRowHidden(i, true);
        }
    }
}

void CustomerList::showDetail(int id)
{
    uiCustomerForm << *list[id];
}

void CustomerList::set(int id)
{
    uiSetCustomerForm >> *list[id];
}

int CustomerList::getCount()
{
    return list.getCount();
}

void CustomerList::remove(int id)
{
    if(!(deletedId.isEmpty() && id == list.getCount() - 1))
        deletedId.push(id);
    list.remove(id);
}

Customer *CustomerList::at(int id)
{
    return list[id];
}

void CustomerList::fillEdit(int id)
{
    uiSetCustomerForm << *list[id];
}

void CustomerList::prepareAdd()
{
    if(justForAdd == nullptr)
    {
        justForAdd = new Customer();
    }
    if(deletedId.getLength() != 0)
    {
        justForAdd->setId(deletedId.front());
    }
    else
    {
        justForAdd->setId(list.getCount());
    }
    uiSetCustomerForm << *justForAdd;
}
