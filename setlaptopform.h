#ifndef SETLAPTOPFORM_H
#define SETLAPTOPFORM_H

#include <QDialog>
#include "laptoplist.h"
#include "stafflist.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class SetLaptopForm;
}

class SetLaptopForm : public QDialog
{
    Q_OBJECT

public:
    explicit SetLaptopForm(LaptopList *laptopList, QWidget *parent = nullptr);
    ~SetLaptopForm();
private slots:
    void btnOk_clicked();
    void btnCancel_clicked();
    void btnAddImage_clicked();

private:
    Ui::SetLaptopForm *ui;
    LaptopList *laptopList;
    void setValidInput();
    bool isValidInput();
    void closeEvent(QCloseEvent *event) override;
};

#endif // SETLAPTOPFORM_H
