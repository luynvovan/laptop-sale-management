#ifndef STAFFLIST_H
#define STAFFLIST_H

#include "ilist.h"
#include "staff.h"
#include "queue.h"

class StaffList : public IList
{
private:
    HashTable<Staff*, 100> list;
    HashTable<QString, 20> userNameList;
    static Staff* nowLogin;
    Queue<int> deletedId;
    Staff *justForAdd;
    Ui::SetStaffForm *uiSetStaffForm;
    Ui::StaffForm *uiStaffForm;

    static int takeKey(Staff* const &staff);
    static int takeKeyUserName(const QString &userName);
    static bool isEqual(Staff* const &l, Staff* const &r);
    static bool isEqualUN(const QString &l, const QString &r);
public:
    static Staff *getNowLogin();
    static bool changePassword(const QString &password, const QString &newPassword, const QString &reNewPassword);
    void login(const QString &userName, const QString &password);
    void logout();
    StaffList();
    virtual ~StaffList();
    virtual void add();
    virtual void showList();
    virtual void showDetail(int id);
    virtual void set(int id);
    virtual int getCount();
    virtual void remove(int id);
    void add(Staff *staff);
    bool isUsedUserName(const QString &userName);
    void prepareAdd();
    void fillEdit(int id);
    Staff *at(int id);
    void setUiSetStaffForm(Ui::SetStaffForm *newUiSetStaffForm);
    void setUiStaffForm(Ui::StaffForm *newUiStaffForm);
    Staff *getJustForAdd() const;
    virtual void load();
    virtual void save();
};

#endif // STAFFLIST_H
