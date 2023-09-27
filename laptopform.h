#ifndef LAPTOPFORM_H
#define LAPTOPFORM_H

#include <QDialog>
#include "setlaptopform.h"

namespace Ui {
class LaptopForm;
}

class LaptopForm : public QDialog
{
    Q_OBJECT

public:
    explicit LaptopForm(LaptopList *laptopList, QWidget *parent = nullptr);
    ~LaptopForm();
    void showThis();
private slots:
    void btnAdd_clicked();
    void btnEdit_clicked();
    void btnSearch_clicked();
    void btnDelete_clicked();

    void listLaptop_cellClicked(int row, int column);

private:
    Ui::LaptopForm *ui;
    SetLaptopForm *setLaptopForm;
    LaptopList *laptopList;
    void clearDetail();
signals:
    void sendLaptopId(int id, int type = 3);
public slots:
    void goDelete(int id, bool stat);
};

#endif // LAPTOPFORM_H
