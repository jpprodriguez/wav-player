#include "microsd_explorer.h"
#include "ui_microsd_explorer.h"



MicroSD_explorer::MicroSD_explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MicroSD_explorer)
{
    ui->setupUi(this);

    ui->pushButton_agregar->setDisabled(true);

    connect(ui->listWidget_canciones,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(EnableButton_agregar()));

    connect(ui->pushButton_agregar,SIGNAL(released()),this,SLOT(DisableButton_agregar()));

    connect(ui->pushButton_ActualizarLista,SIGNAL(released()),this,SLOT(DisableButton_actualizar()));

    connect(this,SIGNAL(CargaLista_Done()),this,SLOT(EnableButton_actualizar()));




}

MicroSD_explorer::~MicroSD_explorer()
{
    delete ui;
}

/*Borra todos los elementos de la lista*/
void MicroSD_explorer::LimpiarLista()
{
    if(ui->listWidget_canciones->count()!=0)
    {
        int nro=ui->listWidget_canciones->count();

        QListWidgetItem* item;
        for(int i=0;i<nro;i++)
        {
            item=new QListWidgetItem;
            ui->listWidget_canciones->takeItem(0);
            delete item;

        }
    }
}
/*Carga la lista con los elementos de la QStringList dada como parametro*/
void MicroSD_explorer::CargarLista(QStringList data)
{
    int cant;

    LimpiarLista();

    if(data.at(0)!="VACIO")
{
    QString aux;

    if(data.size()>3)

        cant=data.size();
    else
        cant=1;

    for(int i=0; i < cant; i+=3)
    {

        aux=data.at(i);
        aux.append("-");
        aux.append(data.at(i+1));
        aux.append(" ");
        aux.append(SegToMin(data.at(i+2).toInt()));
        ui->listWidget_canciones->addItem(aux);
    }
}
    emit CargaLista_Done();
}

/*Devuelve el item seleccionado de la lista*/
QListWidgetItem* MicroSD_explorer::ListCurrentItem()
{
return(ui->listWidget_canciones->currentItem());
}

/*Emite una señal avisando que se solto el click del boton de agregar*/
void MicroSD_explorer::on_pushButton_agregar_released()
{
    emit pushButton_agregar_released();
}

/*Devuelve un string que contiene el tiempo en min:seg tomando el tiempo en segundos como parametro*/
QString MicroSD_explorer::SegToMin(int segs)
{
     int aux = segs / 60; //minutos
     QString minSeg('0');
     minSeg.append(QString::number(aux));
     aux= segs % 60; //segundos
     minSeg.append(':');
     if(aux<10) minSeg.append('0');
     minSeg.append(QString::number(aux));
     return minSeg;
}

/*Deshabilita el boton agregar del widget*/
void MicroSD_explorer::DisableButton_agregar()
{

    ui->pushButton_agregar->setDisabled(true);

}

/*Habilita el boton agregar del widget*/
void MicroSD_explorer::EnableButton_agregar()
{

        ui->pushButton_agregar->setEnabled(true);

}
/*Habilita el boton ActualizarLista del widget*/
void MicroSD_explorer::EnableButton_actualizar()
{

        ui->pushButton_ActualizarLista->setEnabled(true);

}
/*Deshabilita el boton ActualizarLista del widget*/
void MicroSD_explorer::DisableButton_actualizar()
{

        ui->pushButton_ActualizarLista->setDisabled(true);

}

/*Emite una señal avisando que se solto el click del boton de actualizar lista*/
void MicroSD_explorer::on_pushButton_ActualizarLista_released()
{
    emit ReadyToUpdate();
}
