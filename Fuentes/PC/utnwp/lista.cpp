#include "lista.h"
#include "ui_lista.h"

lista::lista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lista)
{
    ui->setupUi(this);

    stringList_canciones=new QStringList;

    connect(ui->listWidget_lista_canciones,SIGNAL(currentRowChanged(int)),this,SLOT(OnCurrentRowChanged()));

}

void lista::AddItem(QString item)
{
    ui->listWidget_lista_canciones->addItem(item);
}
/*Mueve la cancion seleccionada a la anterior,si esta en la primera cancion borra la seleccion y devuelve 1,sino devuelve 0*/
int lista::GoToPrevSong()
{
    int aux=ui->listWidget_lista_canciones->currentRow()-1;

    if(aux <0)
    {
       ui->listWidget_lista_canciones->clearSelection();

       return 1;

    }else
    {
     ui->listWidget_lista_canciones->setCurrentRow(ui->listWidget_lista_canciones->currentRow()-1);

     song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();

     song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

     emit GetSDSongPos();

     return 0;
    }
}

/*Mueve la cancion seleccionada a la proxima,si esta en la ultima cancion borra la seleccion y devuelve 1,sino devuelve 0*/
bool lista::GoToNextSong() {

    int aux=ui->listWidget_lista_canciones->currentRow()+1;

    if(aux >= ui->listWidget_lista_canciones->count())
    {
       ui->listWidget_lista_canciones->clearSelection();

       return true;

    }else
    {
     ui->listWidget_lista_canciones->setCurrentRow(ui->listWidget_lista_canciones->currentRow()+1);

     song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();

     song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

     emit GetSDSongPos();

     return false;
    }

}

/*Mueve la cancion seleccionada a la primera*/
void lista::GoToIndex()
{

    ui->listWidget_lista_canciones->setCurrentRow(0);

    song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();

    song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

    emit GetSDSongPos();

}

/*Mueve la cancion seleccionada a la ultima*/
void lista::GoToEnd()
{
    ui->listWidget_lista_canciones->setCurrentRow(ui->listWidget_lista_canciones->count()-1);

    song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();

    song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

    emit GetSDSongPos();
}
/*Devuelve true si hay algun elemento seleccionado en la lista*/
bool lista::IsItemSelected()
{
    if(ui->listWidget_lista_canciones->selectedItems().count()==0)
        return false;
    else
        return true;
}

lista::~lista()
{
    delete stringList_canciones;

    delete ui;
}

/*Slot que se ejecuta cuando se emite la señal de que hubo un doble click en un item de la lista*/

void lista::on_listWidget_lista_canciones_itemDoubleClicked()
{

    last_song_played=song_ready_to_be_played;

    song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();



    /*Le saco los digitos de la duracion*/
    song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

    emit GetSDSongPos();


    emit SongWaiting();

}

/*Devuelve la cancion a ser reproducida en una QStringList que contiene el nombre de la cancion y el autor*/
QStringList lista::GetSongToPlay()
{

    return (QStringList(song_ready_to_be_played.split("-",QString::SkipEmptyParts)));
}

/*Slot que se ejecuta cuando se emite la señal de que cambio el item seleccionado de la lista*/
void lista::OnCurrentRowChanged()
{
    last_song_played=song_ready_to_be_played;

    song_ready_to_be_played=ui->listWidget_lista_canciones->item(ui->listWidget_lista_canciones->currentRow())->text();



    /*Le saco los digitos de la duracion*/
    song_ready_to_be_played.remove(song_ready_to_be_played.size()-6,6);

    emit GetSDSongPos();

}
/*Borra todos los elementos de la lista*/
void lista::LimpiarLista()
{

    if(ui->listWidget_lista_canciones->count()!=0)
    {
        disconnect(ui->listWidget_lista_canciones,SIGNAL(currentRowChanged(int)),this,SLOT(OnCurrentRowChanged()));

        int nro=ui->listWidget_lista_canciones->count();

        QListWidgetItem* item;

        for(int i=0;i<nro;i++)
        {

            item=new QListWidgetItem;

            ui->listWidget_lista_canciones->takeItem(0);

            delete item;

        }

        connect(ui->listWidget_lista_canciones,SIGNAL(currentRowChanged(int)),this,SLOT(OnCurrentRowChanged()));

    }
}
