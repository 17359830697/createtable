QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    create_area.cpp \
    create_batgraph.cpp \
    create_curve.cpp \
    create_donut.cpp \
    create_pie.cpp \
    create_polyline.cpp \
    create_scatter.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    create_area.h \
    create_batgraph.h \
    create_curve.h \
    create_donut.h \
    create_pie.h \
    create_polyline.h \
    create_scatter.h \
    mainwindow.h

FORMS += \
    create_area.ui \
    create_batgraph.ui \
    create_curve.ui \
    create_donut.ui \
    create_pie.ui \
    create_polyline.ui \
    create_scatter.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
RC_ICONS = create.ico
