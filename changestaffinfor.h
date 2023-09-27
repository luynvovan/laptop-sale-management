#ifndef CHANGESTAFFINFOR_H
#define CHANGESTAFFINFOR_H

#include <QDialog>

namespace Ui {
class ChangeStaffInfor;
}

class ChangeStaffInfor : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeStaffInfor(QWidget *parent = nullptr);
    ~ChangeStaffInfor();
    int exec() override;

private:
    Ui::ChangeStaffInfor *ui;
private slots:
    void holdClickedOkBtn();
    void holdClickedCancelBtn();
};

#endif // CHANGESTAFFINFOR_H
