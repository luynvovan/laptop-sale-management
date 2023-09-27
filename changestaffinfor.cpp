#include "changestaffinfor.h"
#include "qmessagebox.h"
#include "ui_changestaffinfor.h"
#include "stafflist.h"

ChangeStaffInfor::ChangeStaffInfor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeStaffInfor)
{
    ui->setupUi(this);
    connect(ui->btnOk, &QPushButton::clicked, this, &ChangeStaffInfor::holdClickedOkBtn);
    connect(ui->btnCancel, &QPushButton::clicked, this, &ChangeStaffInfor::holdClickedCancelBtn);
}

ChangeStaffInfor::~ChangeStaffInfor()
{
    delete ui;
}

int ChangeStaffInfor::exec()
{
    Staff *staff = StaffList::getNowLogin();
    if(staff == nullptr)
        return QDialog::Rejected;
    ui->lnName->setText(staff->getName());
    ui->lnPhone->setText(staff->getPhoneNumber());
    ui->spinBoxCompleted->setValue(staff->getCompletedOrder());
    ui->lnPaid->setText(QVariant(staff->getTotalPaid()).toString());
    ui->lnUsername->setText(staff->getLoginName());
    ui->cbBoxType->setCurrentIndex(staff->getType());
    ui->cbBoxGender->setCurrentIndex(staff->getGender());
    ui->spinBoxAge->setValue(staff->getAge());
    ui->lnAddress->setText(staff->getAddress());
    return QDialog::exec();
}

void ChangeStaffInfor::holdClickedOkBtn()
{
    if(ui->lnName->text().isEmpty() ||
            ui->lnPhone->text().isEmpty() ||
            ui->lnAddress->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid infor", "Please fill in the correct way");
        return;
    }

    Staff *staff = StaffList::getNowLogin();
    staff->setName(ui->lnName->text());
    staff->setPhoneNumber(ui->lnPhone->text());
    staff->setGender(ui->cbBoxGender->currentText() == "Male" ? male : female);
    staff->setAge(ui->spinBoxAge->value());
    staff->setAddress(ui->lnAddress->text());
    this->accept();
}

void ChangeStaffInfor::holdClickedCancelBtn()
{
    this->reject();
}
