#include "dialog_conectar.h"
#include "ui_dialog_conectar.h"
#include <qextserialenumerator.h>
#include "pc_rs232_handler.h"
#include <QTimer>
#include "mainwindow.h"

/*!**********************************************************************
 * @brief		Constructor de la clase Dialog_conectar
 ***********************************************************************/
Dialog_conectar::Dialog_conectar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_conectar)
{
    ui->setupUi(this);

    EnumerarPuertos();
    connect(ui->pushButton_RefreshPorts,SIGNAL(released()),this,SLOT(EnumerarPuertos()));

}
/*Sobrecargo closeEvent para que cuando aprete la X para cerrar el programa,
 *destruya el QDialog*/
void Dialog_conectar::closeEvent(QCloseEvent *event)
{

    event->accept();

    this->~QDialog();

}


Dialog_conectar::~Dialog_conectar()
{
    delete ui;
}

/*Al hacer click en el boton de conectar,se envia la señal NewPortReady y se destruye el QDialog*/
void Dialog_conectar::on_pushButton_connect_released()
{

    emit NewPortReady();

    this->~QDialog();
}

/*Obtiene desde el combobox el puerto del rs232 y lo guarda en port*/
void Dialog_conectar::GetPort(QString &port)
{
    int i = ui->comboBox_ports->currentIndex();

    if (i != -1 && ui->comboBox_ports->itemText(i) == ui->comboBox_ports->currentText())
        port = ui->comboBox_ports->itemData(i).toString();
    else
        port = ui->comboBox_ports->currentText();

}

/*Obtiene los puertos conectados a la pc y los coloca en el combobox*/
void Dialog_conectar::EnumerarPuertos()
{
    ui->comboBox_ports->clear();

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts(); //guarda en la QList ports todos los puertos disponibles

    for (int i = 0; i < ports.size(); i++)
    {

    #ifdef Q_OS_WIN //Si el sistema operativo es windows
        ui->comboBox_ports->addItem(ports.at(i).friendName, ports.at(i).portName);
    #elif (defined Q_OS_UNIX)  //Si el sistema operativo es linux
        ui->comboBox_ports->addItem(ports.at(i).friendName, ports.at(i).physName);
    #endif

    }
}

