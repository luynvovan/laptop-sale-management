#include "stafflist.h"

int StaffList::takeKey(Staff* const &staff)
{
    return staff->getId();
}

int StaffList::takeKeyUserName(const QString &userName)
{
    int key{};
    for(int i{}; i != userName.size(); ++i)
    {
        key += userName.at(i).toLatin1() * (i + 1);
    }
    return key;
}

bool StaffList::isEqual(Staff * const &l, Staff * const &r)
{
    return l->getId() == r->getId();
}

bool StaffList::isEqualUN(const QString &l, const QString &r)
{
    return l == r;
}

void StaffList::prepareAdd()
{
    if(justForAdd == nullptr)
        justForAdd = new Staff();
    if(deletedId.getLength() != 0)
    {
        justForAdd->setId(deletedId.front());
    }
    else
    {
        justForAdd->setId(list.getCount());
    }
    uiSetStaffForm << *justForAdd;
}

void StaffList::fillEdit(int id)
{
    uiSetStaffForm << *list[id];
}

Staff *StaffList::at(int id)
{
    return list[id];
}

Staff *StaffList::nowLogin = nullptr;

Staff *StaffList::getNowLogin()
{
    return nowLogin;
}

bool StaffList::changePassword(const QString &password, const QString &newPassword, const QString &reNewPassword)
{
    if(nowLogin->getPassword() == password && newPassword == reNewPassword)
    {
        nowLogin->setPassword(newPassword);
        return true;
    }
    return false;
}

void StaffList::login(const QString &userName, const QString &password)
{
    Node<Staff*> *ptr{nullptr};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            if(ptr->getData()->getLoginName() == userName &&
               ptr->getData()->getPassword() == password)
            {
                nowLogin = ptr->getData();
                return;
            }
            ptr = ptr->getNext();
        }
    }
}

void StaffList::logout()
{
    nowLogin = nullptr;
}

void StaffList::setUiSetStaffForm(Ui::SetStaffForm *newUiSetStaffForm)
{
    uiSetStaffForm = newUiSetStaffForm;
}

void StaffList::setUiStaffForm(Ui::StaffForm *newUiStaffForm)
{
    uiStaffForm = newUiStaffForm;
}

Staff *StaffList::getJustForAdd() const
{
    return justForAdd;
}

void StaffList::load()
{
    {
        QFile inputFile("./database/deleted_id/staff.txt");
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

    QFile inputFile("./database/staff.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream input(&inputFile);

    while(!input.atEnd())
    {
        QString line = input.readLine();
        //QStringList infor = line.split(',');
        MyStringList infor;
        infor.setString(line);
        Staff *staff = new Staff(infor[0].toInt(), infor[1], infor[2], infor[3].toInt(), infor[4].toDouble(), infor[5], infor[6], infor[7] == "0" ? UserType::admin : UserType::staff, infor[8] == "0" ? male : female, infor[9].toInt(), infor[10]);
        list.add(staff);
        int rowCount = uiStaffForm->listStaff->rowCount();
        uiStaffForm->listStaff->insertRow(rowCount);
        uiStaffForm->listStaff->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(staff->getId()).toString()));
        uiStaffForm->listStaff->setItem(rowCount, 1, new QTableWidgetItem(staff->getName()));
        userNameList.add(staff->getLoginName());
    }

    input.flush();
    inputFile.close();
}

void StaffList::save()
{
    {
        QFile outputFile("./database/deleted_id/staff.txt");
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

    QFile outputFile("./database/staff.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(&outputFile);

    Node<Staff*> *ptr{};
    Staff *staff{};
    for(int i{}; i != list.getLength(); ++i)
    {
        ptr = list.getHeadatIdx(i);
        while(ptr != nullptr)
        {
            staff = ptr->getData();
            ptr = ptr->getNext();
//int id, const QString &name, const QString &phoneNumber, int completedOrder, double totalPaid, const QString &loginName, const QString &password, UserType type, Gender gender, int age, const QString &address
            output << staff->getId()                << ","
                   << staff->getName()              << ","
                   << staff->getPhoneNumber()       << ","
                   << staff->getCompletedOrder()    << ","
                   << staff->getTotalPaid()         << ","
                   << staff->getLoginName()         << ","
                   << staff->getPassword()          << ","
                   << staff->getType()              << ","
                   << staff->getGender()            << ","
                   << staff->getAge()               << ","
                   << staff->getAddress()           << Qt::endl;
        }
    }

    output.flush();
    outputFile.close();
}

StaffList::StaffList() :
    list(StaffList::takeKey, StaffList::isEqual),
    userNameList(StaffList::takeKeyUserName, StaffList::isEqualUN),
    deletedId(),
    justForAdd(nullptr)
{}

StaffList::~StaffList()
{
    for(int i{}; i != list.getLength(); ++i)
    {
        Node<Staff*> *head = list.getHeadatIdx(i);
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
    if(justForAdd != nullptr)
        delete justForAdd;
}

void StaffList::add(Staff *staff)
{
    list.add(staff);
    userNameList.add(staff->getLoginName());
    bool turnedOfSort{false};
    if(uiStaffForm->listStaff->isSortingEnabled())
    {
        turnedOfSort = true;
        uiStaffForm->listStaff->setSortingEnabled(false);
    }

    int rowCount = uiStaffForm->listStaff->rowCount();
    uiStaffForm->listStaff->insertRow(rowCount);
    uiStaffForm->listStaff->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(staff->getId()).toString()));
    uiStaffForm->listStaff->setItem(rowCount, 1, new QTableWidgetItem(staff->getName()));

    if(turnedOfSort)
        uiStaffForm->listStaff->setSortingEnabled(true);
}

bool StaffList::isUsedUserName(const QString &userName)
{
    return userNameList.isExist(userName);
}
void StaffList::add()
{
    if(justForAdd != nullptr)
    {
        if(!deletedId.isEmpty())
        {
            deletedId.pop();
        }
        uiSetStaffForm >> *justForAdd;
        list.add(justForAdd);
        userNameList.add(justForAdd->getLoginName());

        bool turnOfSort{false};
        if(uiStaffForm->listStaff->isSortingEnabled())
        {
            turnOfSort = true;
            uiStaffForm->listStaff->setSortingEnabled(false);
        }

        int rowCount = uiStaffForm->listStaff->rowCount();
        uiStaffForm->listStaff->insertRow(rowCount);
        uiStaffForm->listStaff->setItem(rowCount, 0, new IntQTableWidgetItem(QVariant(justForAdd->getId()).toString()));
        uiStaffForm->listStaff->setItem(rowCount, 1, new QTableWidgetItem(justForAdd->getName()));

        if(turnOfSort)
            uiStaffForm->listStaff->setSortingEnabled(true);

        QFile outputFile("./database/staff.txt");
        outputFile.open(QIODevice::Text | QIODevice::Append);
        QTextStream output(&outputFile);
        output << justForAdd->getId()                << ","
               << justForAdd->getName()              << ","
               << justForAdd->getPhoneNumber()       << ","
               << justForAdd->getCompletedOrder()    << ","
               << justForAdd->getTotalPaid()         << ","
               << justForAdd->getLoginName()         << ","
               << justForAdd->getPassword()          << ","
               << justForAdd->getType()              << ","
               << justForAdd->getGender()            << ","
               << justForAdd->getAge()               << ","
               << justForAdd->getAddress()           << Qt::endl;
        justForAdd = nullptr;
    }
}

void StaffList::showList()
{
    QString search = uiStaffForm->lnSearch->text().trimmed().toLower();
    bool emptySearch = search.isEmpty();
    int rowCount = uiStaffForm->listStaff->rowCount();
    for(int i{}; i < rowCount; ++i)
    {
        if(emptySearch || uiStaffForm->listStaff->item(i, 1)->text().toLower().contains(search))
        {
            uiStaffForm->listStaff->setRowHidden(i, false);
        }
        else
        {
            uiStaffForm->listStaff->setRowHidden(i, true);
        }
    }
}

void StaffList::showDetail(int id)
{
    uiStaffForm << *list[id];
}

void StaffList::set(int id)
{
    uiSetStaffForm >> *list[id];
}

int StaffList::getCount()
{
    return list.getCount();
}

void StaffList::remove(int id)
{
    if(!(deletedId.isEmpty() && id == list.getCount() - 1))
        deletedId.push(id);
    userNameList.remove(list[id]->getLoginName());
    list.remove(id);
}
