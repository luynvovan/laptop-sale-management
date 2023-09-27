QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepasswordform.cpp \
    changestaffinfor.cpp \
    customer.cpp \
    customerform.cpp \
    customerlist.cpp \
    holdexist.cpp \
    item.cpp \
    laptop.cpp \
    laptopform.cpp \
    laptoplist.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    orderdetail.cpp \
    orderdetailform.cpp \
    orderdetaillist.cpp \
    orderitem.cpp \
    orderlist.cpp \
    person.cpp \
    purchaseorder.cpp \
    salesorder.cpp \
    salesorpurchaseorder.cpp \
    setcustomerform.cpp \
    setlaptopform.cpp \
    setorderform.cpp \
    setstaffform.cpp \
    setsupplierform.cpp \
    staff.cpp \
    staffform.cpp \
    stafflist.cpp \
    supplier.cpp \
    supplierform.cpp \
    supplierlist.cpp

HEADERS += \
    changepasswordform.h \
    changestaffinfor.h \
    customer.h \
    customerform.h \
    customerlist.h \
    date.h \
    hashtable.h \
    holdexist.h \
    ilist.h \
    item.h \
    laptop.h \
    laptopform.h \
    laptoplist.h \
    linkedlist.h \
    loginform.h \
    mainwindow.h \
    mystringlist.h \
    node.h \
    order.h \
    orderdetail.h \
    orderdetailform.h \
    orderdetaillist.h \
    orderitem.h \
    orderlist.h \
    person.h \
    purchaseorder.h \
    queue.h \
    salesorder.h \
    salesorpurchaseorder.h \
    setcustomerform.h \
    setlaptopform.h \
    setorderform.h \
    setstaffform.h \
    setsupplierform.h \
    staff.h \
    staffform.h \
    stafflist.h \
    supplier.h \
    supplierform.h \
    supplierlist.h

FORMS += \
    changepasswordform.ui \
    changestaffinfor.ui \
    customerform.ui \
    laptopform.ui \
    loginform.ui \
    mainwindow.ui \
    orderdetailform.ui \
    salesorpurchaseorder.ui \
    setcustomerform.ui \
    setlaptopform.ui \
    setorderform.ui \
    setstaffform.ui \
    setsupplierform.ui \
    staffform.ui \
    supplierform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
