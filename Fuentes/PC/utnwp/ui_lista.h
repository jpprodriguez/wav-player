/********************************************************************************
** Form generated from reading UI file 'lista.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTA_H
#define UI_LISTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lista
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget_lista_canciones;

    void setupUi(QWidget *lista)
    {
        if (lista->objectName().isEmpty())
            lista->setObjectName(QStringLiteral("lista"));
        lista->resize(264, 300);
        lista->setMinimumSize(QSize(264, 300));
        lista->setMaximumSize(QSize(264, 500));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icono_lista.png"), QSize(), QIcon::Normal, QIcon::Off);
        lista->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(lista);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget_lista_canciones = new QListWidget(lista);
        listWidget_lista_canciones->setObjectName(QStringLiteral("listWidget_lista_canciones"));

        verticalLayout->addWidget(listWidget_lista_canciones);


        retranslateUi(lista);

        QMetaObject::connectSlotsByName(lista);
    } // setupUi

    void retranslateUi(QWidget *lista)
    {
        lista->setWindowTitle(QApplication::translate("lista", "Lista de Reproduccion", 0));
    } // retranslateUi

};

namespace Ui {
    class lista: public Ui_lista {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTA_H
