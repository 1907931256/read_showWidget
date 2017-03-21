#-------------------------------------------------
#
# Project created by QtCreator 2017-03-06T08:09:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowWidget
TEMPLATE = app
INCLUDEPATH+=. databaseClass global PLC


SOURCES += main.cpp\
    mainwindow.cpp \
    global/sysGlobal.cpp \
    global/globalFunction.cpp \
    PLC/plc_check_node.cpp \
    PLC/plc_compile_ladder.cpp \
    PLC/plc_count_nodelink_num.cpp \
    PLC/plc_delete_element_node.cpp \
    PLC/plc_editor_dialog.cpp \
    PLC/plc_find_out_in_node.cpp \
    PLC/plc_insert_element.cpp \
    PLC/plc_MDialog.cpp \
    PLC/plc_poise_node.cpp \
    PLC/plc_rebuild_node.cpp \
    PLC/plc_release_node.cpp \
    PLC/plc_shape_ladder.cpp \
    PLC/plc_shape_ladder_test.cpp \
    PLC/plc_stack_plc.cpp \
    PLC/plc_structure.cpp \
    PLC/uiPlcEditor.cpp \
    analysis/analyse.cpp \
    databaseClass/proggrameconstant.cpp \
    databaseClass/machineconst.cpp

HEADERS  += mainwindow.h \
    global/sysGlobal.h \
    global/globalFunction.h \
    global/sqlite3.h \
    PLC/interface_font.h \
    PLC/plc_check_node.h \
    PLC/plc_compile_ladder.h \
    PLC/plc_count_nodelink_num.h \
    PLC/plc_delete_element_node.h \
    PLC/plc_editor_dialog.h \
    PLC/plc_find_out_in_node.h \
    PLC/plc_insert_element.h \
    PLC/plc_ISN.h \
    PLC/plc_MDialog.h \
    PLC/plc_poise_node.h \
    PLC/plc_rebuild_node.h \
    PLC/plc_release_node.h \
    PLC/plc_shape_ladder.h \
    PLC/plc_shape_ladder_test.h \
    PLC/plc_stack_plc.h \
    PLC/plc_structure.h \
    PLC/uiPlcEditor.h \
    global/globalFunction.h \
    global/SysKeyboard.h \
    analysis/analyse.h \
    global/CNCSysData.h \
    databaseClass/proggrameconstant.h \
    databaseClass/ui_proggrameconstant.h \
    databaseClass/machineconst.h

FORMS    += mainwindow.ui \
    PLC/uiPlcEditor.ui \
    analysis/analyse.ui \
    databaseClass/proggrameconstant.ui \
    databaseClass/machineconst.ui

RESOURCES += \
    icon.qrc
LIBS+=-lsqlite3
UI_DIR=./UI
