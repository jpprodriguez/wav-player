/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMicroSD;
    QAction *actionLista;
    QAction *actionCreador;
    QAction *actionConectar;
    QWidget *centralWidget;
    QLabel *label_title;
    QLabel *label_2;
    QProgressBar *progressBar;
    QLabel *label_author;
    QLabel *label_curr_time;
    QLabel *label_max_time;
    QLabel *label_5;
    QLabel *label_author_2;
    QLabel *label_title_2;
    QSlider *horizontalSlider;
    QLabel *label_valor_volumen;
    QSlider *horizontalSlider_volumen;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_prev;
    QPushButton *pushButton_next;
    QPushButton *pushButton_play;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_repeat_mode;
    QPushButton *pushButton_list;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(373, 240);
        MainWindow->setMinimumSize(QSize(373, 240));
        MainWindow->setMaximumSize(QSize(373, 240));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icon_utn.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionMicroSD = new QAction(MainWindow);
        actionMicroSD->setObjectName(QStringLiteral("actionMicroSD"));
        actionLista = new QAction(MainWindow);
        actionLista->setObjectName(QStringLiteral("actionLista"));
        actionCreador = new QAction(MainWindow);
        actionCreador->setObjectName(QStringLiteral("actionCreador"));
        actionConectar = new QAction(MainWindow);
        actionConectar->setObjectName(QStringLiteral("actionConectar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(90, 20, 251, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 10, 301, 111));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/fondo_info_cancion.png")));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(40, 90, 301, 8));
        progressBar->setMaximum(35);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        label_author = new QLabel(centralWidget);
        label_author->setObjectName(QStringLiteral("label_author"));
        label_author->setGeometry(QRect(90, 50, 231, 20));
        label_curr_time = new QLabel(centralWidget);
        label_curr_time->setObjectName(QStringLiteral("label_curr_time"));
        label_curr_time->setGeometry(QRect(271, 101, 31, 16));
        label_max_time = new QLabel(centralWidget);
        label_max_time->setObjectName(QStringLiteral("label_max_time"));
        label_max_time->setGeometry(QRect(312, 101, 31, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(299, 101, 16, 16));
        label_author_2 = new QLabel(centralWidget);
        label_author_2->setObjectName(QStringLiteral("label_author_2"));
        label_author_2->setGeometry(QRect(50, 50, 31, 20));
        label_title_2 = new QLabel(centralWidget);
        label_title_2->setObjectName(QStringLiteral("label_title_2"));
        label_title_2->setGeometry(QRect(50, 20, 31, 20));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(40, 80, 301, 21));
        horizontalSlider->setTracking(false);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_valor_volumen = new QLabel(centralWidget);
        label_valor_volumen->setObjectName(QStringLiteral("label_valor_volumen"));
        label_valor_volumen->setGeometry(QRect(340, 180, 31, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(30);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_valor_volumen->sizePolicy().hasHeightForWidth());
        label_valor_volumen->setSizePolicy(sizePolicy);
        horizontalSlider_volumen = new QSlider(centralWidget);
        horizontalSlider_volumen->setObjectName(QStringLiteral("horizontalSlider_volumen"));
        horizontalSlider_volumen->setGeometry(QRect(260, 180, 67, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalSlider_volumen->sizePolicy().hasHeightForWidth());
        horizontalSlider_volumen->setSizePolicy(sizePolicy1);
        horizontalSlider_volumen->setMaximum(180);
        horizontalSlider_volumen->setValue(100);
        horizontalSlider_volumen->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(234, 173, 20, 31));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/icono_volumen.png")));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 140, 301, 31));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        pushButton_prev = new QPushButton(widget);
        pushButton_prev->setObjectName(QStringLiteral("pushButton_prev"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icono_prev.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_prev->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_prev);

        pushButton_next = new QPushButton(widget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icono_next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_next->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_next);

        pushButton_play = new QPushButton(widget);
        pushButton_play->setObjectName(QStringLiteral("pushButton_play"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/icono_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_play);

        pushButton_stop = new QPushButton(widget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/icono_stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_stop->setIcon(icon4);

        horizontalLayout->addWidget(pushButton_stop);

        pushButton_repeat_mode = new QPushButton(widget);
        pushButton_repeat_mode->setObjectName(QStringLiteral("pushButton_repeat_mode"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/icono_repeat.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_repeat_mode->setIcon(icon5);
        pushButton_repeat_mode->setCheckable(true);
        pushButton_repeat_mode->setChecked(false);

        horizontalLayout->addWidget(pushButton_repeat_mode);

        pushButton_list = new QPushButton(widget);
        pushButton_list->setObjectName(QStringLiteral("pushButton_list"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/icono_lista.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_list->setIcon(icon6);

        horizontalLayout->addWidget(pushButton_list);


        horizontalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        label_2->raise();
        label_title->raise();
        progressBar->raise();
        label_author->raise();
        label_curr_time->raise();
        label_max_time->raise();
        label_5->raise();
        label_author_2->raise();
        label_title_2->raise();
        horizontalSlider->raise();
        label_valor_volumen->raise();
        label->raise();
        horizontalSlider_volumen->raise();
        label->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 373, 20));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionConectar);
        menuMenu->addSeparator();
        menuMenu->addAction(actionMicroSD);
        menuMenu->addSeparator();
        menuMenu->addAction(actionLista);
        menuMenu->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "UTN WAV Player", 0));
        actionMicroSD->setText(QApplication::translate("MainWindow", "Explorar MicroSD", 0));
        actionLista->setText(QApplication::translate("MainWindow", "Lista de reproduccion actual", 0));
        actionCreador->setText(QApplication::translate("MainWindow", "Creador de listas de reproduccion", 0));
        actionConectar->setText(QApplication::translate("MainWindow", "Conectar", 0));
        label_title->setText(QApplication::translate("MainWindow", "-", 0));
        label_2->setText(QString());
        label_author->setText(QApplication::translate("MainWindow", "-", 0));
        label_curr_time->setText(QApplication::translate("MainWindow", "1:04", 0));
        label_max_time->setText(QApplication::translate("MainWindow", "1:04", 0));
        label_5->setText(QApplication::translate("MainWindow", " /", 0));
        label_author_2->setText(QApplication::translate("MainWindow", "Autor:", 0));
        label_title_2->setText(QApplication::translate("MainWindow", "Titulo:", 0));
        label_valor_volumen->setText(QApplication::translate("MainWindow", "50%", 0));
        label->setText(QString());
        pushButton_prev->setText(QString());
        pushButton_next->setText(QString());
        pushButton_play->setText(QString());
        pushButton_stop->setText(QString());
        pushButton_repeat_mode->setText(QString());
        pushButton_list->setText(QString());
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
