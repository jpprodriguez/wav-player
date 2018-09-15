/********************************************************************************
** Form generated from reading UI file 'dialog_conectar.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CONECTAR_H
#define UI_DIALOG_CONECTAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_conectar
{
public:
    QComboBox *comboBox_ports;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_RefreshPorts;

    void setupUi(QDialog *Dialog_conectar)
    {
        if (Dialog_conectar->objectName().isEmpty())
            Dialog_conectar->setObjectName(QStringLiteral("Dialog_conectar"));
        Dialog_conectar->resize(276, 156);
        Dialog_conectar->setMinimumSize(QSize(276, 156));
        Dialog_conectar->setMaximumSize(QSize(276, 156));
        comboBox_ports = new QComboBox(Dialog_conectar);
        comboBox_ports->setObjectName(QStringLiteral("comboBox_ports"));
        comboBox_ports->setGeometry(QRect(40, 40, 191, 22));
        widget = new QWidget(Dialog_conectar);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 80, 97, 54));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_connect = new QPushButton(widget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));

        verticalLayout->addWidget(pushButton_connect);

        pushButton_RefreshPorts = new QPushButton(widget);
        pushButton_RefreshPorts->setObjectName(QStringLiteral("pushButton_RefreshPorts"));

        verticalLayout->addWidget(pushButton_RefreshPorts);

        comboBox_ports->raise();
        pushButton_connect->raise();
        pushButton_RefreshPorts->raise();

        retranslateUi(Dialog_conectar);

        QMetaObject::connectSlotsByName(Dialog_conectar);
    } // setupUi

    void retranslateUi(QDialog *Dialog_conectar)
    {
        Dialog_conectar->setWindowTitle(QApplication::translate("Dialog_conectar", "Dialog", 0));
        pushButton_connect->setText(QApplication::translate("Dialog_conectar", "Conectar", 0));
        pushButton_RefreshPorts->setText(QApplication::translate("Dialog_conectar", "Actualizar Puertos", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_conectar: public Ui_Dialog_conectar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CONECTAR_H
