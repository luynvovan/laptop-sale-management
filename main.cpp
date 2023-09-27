#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//#include "date.h"
//#include <QDebug>

//int main()
//{
//    QString x = Date::currentDate();
//    qDebug() << x;
//    return 0;
//}
