/********************************************************************************
** Form generated from reading UI file 'microsd_explorer.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MICROSD_EXPLORER_H
#define UI_MICROSD_EXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MicroSD_explorer
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget_canciones;
    QPushButton *pushButton_agregar;
    QPushButton *pushButton_ActualizarLista;

    void setupUi(QWidget *MicroSD_explorer)
    {
        if (MicroSD_explorer->objectName().isEmpty())
            MicroSD_explorer->setObjectName(QStringLiteral("MicroSD_explorer"));
        MicroSD_explorer->resize(282, 370);
        MicroSD_explorer->setMinimumSize(QSize(282, 370));
        MicroSD_explorer->setMaximumSize(QSize(282, 370));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icono_microSD.png"), QSize(), QIcon::Normal, QIcon::Off);
        MicroSD_explorer->setWindowIcon(icon);
        layoutWidget = new QWidget(MicroSD_explorer);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 258, 341));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        listWidget_canciones = new QListWidget(layoutWidget);
        listWidget_canciones->setObjectName(QStringLiteral("listWidget_canciones"));

        verticalLayout->addWidget(listWidget_canciones);

        pushButton_agregar = new QPushButton(layoutWidget);
        pushButton_agregar->setObjectName(QStringLiteral("pushButton_agregar"));

        verticalLayout->addWidget(pushButton_agregar);

        pushButton_ActualizarLista = new QPushButton(layoutWidget);
        pushButton_ActualizarLista->setObjectName(QStringLiteral("pushButton_ActualizarLista"));

        verticalLayout->addWidget(pushButton_ActualizarLista);


        retranslateUi(MicroSD_explorer);

        QMetaObject::connectSlotsByName(MicroSD_explorer);
    } // setupUi

    void retranslateUi(QWidget *MicroSD_explorer)
    {
        MicroSD_explorer->setWindowTitle(QApplication::translate("MicroSD_explorer", "MicroSD Card", 0));
        label->setText(QApplication::translate("MicroSD_explorer", "Canciones ubicadas en la MicroSD Card", 0));
        pushButton_agregar->setText(QApplication::translate("MicroSD_explorer", "Agregar a lista actual", 0));
        pushButton_ActualizarLista->setText(QApplication::translate("MicroSD_explorer", "Actualizar Lista", 0));
    } // retranslateUi

};

namespace Ui {
    class MicroSD_explorer: public Ui_MicroSD_explorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MICROSD_EXPLORER_H
