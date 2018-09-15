#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qextserialport.h>
#include <QTimer>
#include <QShortcut>
#include <sstream>

using namespace std;

/*Diseño de la QProgressBar */
#define QProgressBar_BAR "QProgressBar:horizontal {border: 1px solid gray;border-radius: 3px;background: white;padding: 1px;}"
#define QProgressBar_CHUNK "QProgressBar::chunk {background-color: #00BBDD;width: 1px;}"

/*Diseño del QSlider*/
#define QProgressSlider_GROOVE "QSlider::groove:horizontal { border: 0px; background: ; height: 0px; margin: 0 0 0 0;}"
#define QProgressSlider_HANDLE "QSlider::handle:horizontal {background: #31B404; border: 1px solid #5c5c5c; width: 20px; margin: -5px 0 -5px 0; border-radius: 3px;}"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Inicializo widgets,dialogos y objects */
    RS232_handler=new pc_rs232_handler;
    SD_exp=new MicroSD_explorer;
    lista_canciones=new lista;

    /*Inicializo Timer*/
    Timer_Seg=new QTimer;
    Timer_Seg->setInterval(1000);

    /* Inicializo estilo de la progressbar */
    ui->progressBar->setStyleSheet(QProgressBar_BAR QProgressBar_CHUNK);

    /*Inicializo estilo y ubicacion del QSlider*/
    ui->horizontalSlider->setStyleSheet( QProgressSlider_GROOVE QProgressSlider_HANDLE);
    ui->horizontalSlider->move(40,84);

    /* Inicializo los botones deshabilitados */
    resetPlayerSongInfo();
    OnDisconnect();

    /* Inicializo los flags */
    isPlaying=false;
    isPaused=false;

    /* Inicializo atajos de teclado */
    QShortcut* shortcut_SongList = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L),this);




    /* Conexiones con los atajos */


    connect(shortcut_SongList,SIGNAL(activated()),this,SLOT(onPushButtonList()));


    /* Conexiones con los botones */
    connect(ui->pushButton_stop,SIGNAL(pressed()),this,SLOT(stop_song()));
    connect(ui->pushButton_list,SIGNAL(released()),this,SLOT(onPushButtonList()));

    /* Conexiones con el SD_exp */
    connect(ui->actionMicroSD,SIGNAL(triggered()),SD_exp,SLOT(show()));
    connect(ui->actionMicroSD,SIGNAL(triggered()),this,SLOT(get_SD_list()));
    connect(SD_exp,SIGNAL(ReadyToUpdate()),this,SLOT(get_SD_list()));


    /* Conexiones con el dialogo de conectar */
    connect(ui->actionConectar,SIGNAL(triggered()),this,SLOT(OpenConnectDialog()));

    /* Conexiones con lista_canciones */
    connect(ui->actionLista,SIGNAL(triggered()),lista_canciones,SLOT(show()));
    connect(SD_exp,SIGNAL(pushButton_agregar_released()),this,SLOT(SDExp_to_SongList()));
    connect(lista_canciones,SIGNAL(SongWaiting()),this,SLOT(onSongWaiting()));
    connect(lista_canciones,SIGNAL(GetSDSongPos()),this,SLOT(OnGetSDPos()));


    /* Conexiones con el RS232 */
    connect(RS232_handler,SIGNAL(ConnectionSuccess()),this,SLOT(OnConnect()));
    connect(RS232_handler,SIGNAL(ConnectionFailed()),this,SLOT(OnDisconnect()));
    connect(RS232_handler,SIGNAL(SinConexion()),this,SLOT(OnDisconnect()));

    /* Conexiones con el timer del tiempo de la cancion,la progress bar y el QSlider */
    connect(Timer_Seg,SIGNAL(timeout()),this,SLOT(actualizarTiempo()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),ui->progressBar,SLOT(setValue(int)));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),ui->horizontalSlider,SLOT(setValue(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(this,SIGNAL(curr_time_Changed(int)),ui->horizontalSlider,SLOT(setValue(int)));
    connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(onSliderPressed()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(onSliderReleased()));

    /* Conexiones con el slider y el label del volumen*/
    connect(ui->horizontalSlider_volumen,SIGNAL(valueChanged(int)),this,SLOT(onSliderVolMoved(int)));


    OpenConnectDialog();

}
/*Inicializo variables static */
int MainWindow::curr_time=0;

MainWindow::~MainWindow()
{
    delete ui;
}

/*Sobrecargo closeEvent para que cuando aprete la X para cerrar el programa,
 *antes de cerrar borre toda la memoria dinamica utilizada y cierre la conexion
 *con el Puerto Serie */
void MainWindow::closeEvent(QCloseEvent *event)
{

    delete RS232_handler;

    delete SD_exp;

    delete lista_canciones;

    event->accept();

}


/*---------------------------------------------*
 *                                             *
 *                                             *
 *     FUNCIONES RELACIONADAS CON SD_EXPLORER  *
 *                                             *
 *                                             *
 *---------------------------------------------*/


/*Paso la info de las canciones que traigo del micro a una qstringlist*/
QStringList MainWindow::SD_songsdata(QString& string)
{


    if(string.isEmpty())
        return QStringList("VACIO");
    else
    {

        QStringList raw_data;

            /*Separo raw_data para insertar todos los datos separados en una nueva lista*/

        if(string.contains("|"))
        {
            raw_data << string.split("|",QString::SkipEmptyParts);
        }else
            raw_data << string;

            int list_size=raw_data.size();
            QStringList aux,info;

            for(int i=0;i<list_size;i++)
            {
            aux=raw_data.at(i).split("/",QString::SkipEmptyParts);
            info << aux;
            }

            char estado=0;

            /*Guardo los datos en 3 StringList distintos qe almacenan Nombre,Autor y Duracion */
            Songs_Authors.clear();Songs_Names.clear();Songs_Durations.clear();

            for(int i=0;i<info.size();i++)
            {
                switch(estado)
                {
                case 0:
                    Songs_Authors << info[i];
                    estado=1;
                    break;
                case 1:
                    Songs_Names << info[i];
                    estado=2;

                    break;
                case 2:
                    Songs_Durations << info[i];
                    estado=0;
                    break;

                }
            }

        return info;
}

}
/*Agrego la cancion seleccionada en SDexp a la lista de reproduccion*/
void MainWindow::SDExp_to_SongList()
{
    QString aux(SD_exp->ListCurrentItem()->text());

    lista_canciones->stringList_canciones->append(aux.split("-",QString::SkipEmptyParts));

    lista_canciones->AddItem(SD_exp->ListCurrentItem()->text());
}

/*Me comunico con el rs232 para recibir la lista de canciones del micro*/
void MainWindow::get_SD_list()
{

        RS232_handler->EnviarComando(QString("SDLIST"));

        RS232_handler->modo=SD;


        /*Doy tiempo para recibir toda la lista*/

         QTimer::singleShot(1000, this, SLOT(onSDListDataReady()));

    }



/*Cuando termina el timer chequeo si ya llego todo y lo cargo en la lista*/
void MainWindow::onSDListDataReady()
{
    /*La lista de canciones enviada por el lpc termina con "<>", si no llego eso al buffer,significa que no termino de pasarse la informacion*/
    if(RS232_handler->SDListUploadFinished())
    {
        /*Cargo en el SD_exp la lista que recibi*/
        SD_exp->CargarLista(SD_songsdata(RS232_handler->getDataBuff()));

        /*Vacio el buffer del rs232*/
        RS232_handler->EmptyBuffer();
    }

    else
        QTimer::singleShot(500, this, SLOT(onSDListDataReady()));       /* Si todavia no terminor de llegar la lista,
                                                                        reseteo el timer para dar mas tiempo*/



}

/*---------------------------------------------*
 *                                             *
 *                                             *
 *     FUNCIONES RELACIONADAS CON RS232        *
 *                                             *
 *                                             *
 *---------------------------------------------*/

/*Crea un nuevo dialog para conectarse con el rs232*/
void MainWindow::OpenConnectDialog() {

    connect_interface=new Dialog_conectar(this);

    connect(connect_interface,SIGNAL(NewPortReady()),this,SLOT(onNewPortReady()));

    connect_interface->exec();
}

void MainWindow::onNewPortReady()
{
    connect_interface->GetPort(pc_rs232_handler::puerto);

    RS232_handler->Connect();

}




/*Habilita los botones del reproductor y cambia a "true" el flag de conexion*/
void MainWindow::OnConnect()
{
    ui->pushButton_list->setEnabled(1);

    ui->pushButton_next->setEnabled(1);

    ui->pushButton_prev->setEnabled(1);

    ui->pushButton_stop->setEnabled(1);

    ui->pushButton_play->setEnabled(1);

    ui->pushButton_repeat_mode->setEnabled(1);

    ui->horizontalSlider_volumen->setValue(90);

    ui->horizontalSlider_volumen->setEnabled(1);

    RS232_handler->SetFlagConnected(true);

    if(isPlaying || isPaused)
        stop_song();

}

/*Deshabilita los botones del reproductor , cambia a "false" el flag de conexion y borra la info del reproductor */
void MainWindow::OnDisconnect()
{
    ui->pushButton_list->setEnabled(0);

    ui->pushButton_next->setEnabled(0);

    ui->pushButton_play->setEnabled(0);

    ui->pushButton_prev->setEnabled(0);

    ui->pushButton_stop->setEnabled(0);

    ui->pushButton_repeat_mode->setEnabled(0);

    isPlaying=false;

    isPaused=false;

    ui->pushButton_play->setIcon(QIcon(":/icons/icono_play.png"));

    RS232_handler->SetFlagConnected(false);

    Timer_Seg->stop();

    resetPlayerSongInfo();

    SD_exp->LimpiarLista();

    lista_canciones->LimpiarLista();

    ui->horizontalSlider_volumen->setValue(90);

    ui->horizontalSlider_volumen->setEnabled(0);

}

 /*---------------------------------------------------------*
 *                                                          *
 *                                                          *
 *       FUNCIONES RELACIONADAS CON LISTA DE CANCIONES      *
 *                                                          *
 *                                                          *
 *----------------------------------------------------------*/
/*Muestra/Oculta la lista de reproduccion */
void MainWindow::onPushButtonList()
{
    if(lista_canciones->isVisible())
        lista_canciones->hide();
    else
        lista_canciones->show();

}

/*Obtiene el codigo identificador de la cancion y la guarda en song_number(variable de la clase lista)*/
void MainWindow::OnGetSDPos()
{
    QStringList cancion(lista_canciones->song_ready_to_be_played.split("-",QString::SkipEmptyParts));

    for(int i=0;i<Songs_Names.size();i++)
    {
        if(cancion[0]==Songs_Authors[i] && cancion[1]==Songs_Names[i])
            lista_canciones->song_number=i;
    }
}

/*SLOT ejecutado cuando se hace doble click en una cancion de la lista de reproduccion.
 *Carga la informacion de la cancion seleccionada y la reproduce*/
void MainWindow::onSongWaiting()
{
    UpdatePlayerSongInfo();

    if(isPaused || isPlaying)
    {
          play_song();
    }else

       play_song();
}

/*Transforma el numero almacenado en song_number(variable de clase lista) y lo devuelve en un QString de la siguiente forma:
 *song_number=9 ==> QString devuelto=009*/
QString MainWindow::getSongNumber()
{
    QString aux;

    if(lista_canciones->song_number>=10 && lista_canciones->song_number<99)
    {
        aux.append('0');

        aux.append(QString::number(lista_canciones->song_number));

    }else if(lista_canciones->song_number<10)
    {
        aux.append("00");

        aux.append(QString::number(lista_canciones->song_number));
    }
        else aux.append(QString::number(lista_canciones->song_number));

        return aux;
}
/*---------------------------------------------------------*
*                                                          *
*                                                          *
*    FUNCIONES RELACIONADAS CON REPRODUCTOR DE MUSICA      *
*                                                          *
*                                                          *
*----------------------------------------------------------*/

/*Actualiza la informacion del reproductor y del titulo de la ventana con la de la cancion asignada por song_number*/
void MainWindow::UpdatePlayerSongInfo()
{

    ui->label_author->setText(Songs_Authors[lista_canciones->song_number]);

    ui->label_title->setText(Songs_Names[lista_canciones->song_number]);

    ui->label_max_time->setText(SD_exp->SegToMin(Songs_Durations[lista_canciones->song_number].toInt()));

    QString window_title(ui->label_author->text());

    window_title+= "-";

    window_title+= ui->label_title->text();

    window_title+=" - UTN WAV Player";

    this->setWindowTitle(window_title);

}

/*Borra la informacion del reproductor y la devuelve a su estado por defecto*/
void MainWindow::resetPlayerSongInfo()
{
    ui->label_author->setText("-");

    ui->label_title->setText("-");

    ui->label_max_time->setText("--:--");

    ui->label_curr_time->setText("--:--");

    ui->progressBar->setValue(0);

    this->setWindowTitle("UTN WAV Player");

    ui->horizontalSlider->setValue(0);

    ui->horizontalSlider->setMaximum(0);

    ui->horizontalSlider->setMinimum(0);
}

/*Envia el comando "PLAxxx" al micro ,inicializa la informacion del reproductor con la de la cancion y empieza a reproducir la cancion*/
void MainWindow::play_song()
{
    if(lista_canciones->song_number<=Songs_Names.size() && lista_canciones->song_number>=0)
    {

        QString cmd;

        cmd.append("PLA");

        cmd.append(getSongNumber());

        InitSlider();

        InitProgressBar();

        RS232_handler->EnviarComando(cmd);

        resetCurrTime();

        QString aux=TimeToCommand(curr_time);



        RS232_handler->EnviarComando(aux);

        isPlaying=true;

        isPaused=false;

        change_play_icon();

    }

}

/*Corre el indice de la lista de reproduccion a la proxima cancion y la reproduce*/
void MainWindow::PlayNextSong()
{
    bool aux=lista_canciones->GoToNextSong(); /*si la lista esta en la ultima cancion aux=1,sino aux=0*/

    if(!aux)
    {   UpdatePlayerSongInfo();

        play_song();
    }
    else if(ui->pushButton_repeat_mode->isChecked() && aux) /*si esta en la ultima cancion y esta en modo repeticion vuelve a la primera cancion*/
    {
        lista_canciones->GoToIndex();

        UpdatePlayerSongInfo();

        play_song();
    }else
    {
        stop_song();

    }
}

/*Envia el comando "PAUSAR" al micro y pausa el tiempo de la cancion en reproduccion*/
void MainWindow::pause_song()
{
    RS232_handler->EnviarComando("PAUSAR");

    isPaused=true;

    isPlaying=false;

    Timer_Seg->stop();

}

/*Envia el comando "RESUMER" al micro y resume el tiempo de la cancion en reproduccion*/
void MainWindow::resume_song()
{
    RS232_handler->EnviarComando("RESUME");

    isPaused=false;

    isPlaying=true;

    RS232_handler->EnviarComando("RESUME");

    QString aux=TimeToCommand(curr_time);

    RS232_handler->EnviarComando(aux);

    Timer_Seg->start();


}

/*Envia el comando "STOP00" al micro y resetea la info del reproductor*/
void MainWindow::stop_song()
{

    RS232_handler->EnviarComando("STOP00");

    isPaused=false;

    isPlaying=false;

    change_play_icon();

    Timer_Seg->stop();

    curr_time=0;

    resetPlayerSongInfo();


}

/*Cambia el icono del boton de play/pausa*/
void MainWindow::change_play_icon()
{
    QIcon play(":/icons/icono_play.png");

    QIcon paused(":/icons/icono_pause.png");

    if(isPlaying)
    {
        ui->pushButton_play->setIcon(paused);

    }
    else
    {
       ui->pushButton_play->setIcon(play);

    }
}

/*Pausa la cancion si ya se estaba reproduciendo,la reanuda si estaba pausada o la reproduce si no estaba ni pausada ni reproduciendose*/
void MainWindow::on_pushButton_play_clicked()
{
    if(lista_canciones->IsItemSelected())
    {
    if(isPlaying)
        pause_song();
    else if(isPaused)
        resume_song();
    else
    {   UpdatePlayerSongInfo();

        play_song();
    }

    change_play_icon();

    }
}

/*Pasa a la proxima cancion y la reproduce.Si estaba en la ultima cancion de la lista,pasa a reproducir la primera*/
void MainWindow::on_pushButton_next_clicked()
{
    if(lista_canciones->IsItemSelected())
    {
        if(isPlaying || isPaused)
        {
            int aux=lista_canciones->GoToNextSong();


            if(!aux)
            {
             UpdatePlayerSongInfo();

             play_song();
            }
         else
            {
             lista_canciones->GoToIndex();

             UpdatePlayerSongInfo();

             play_song();
            }
        }
    }
}

/*Activa/desactiva el modo repeticion*/
void MainWindow::on_pushButton_repeat_mode_clicked()
{
    if(!ui->pushButton_repeat_mode->isChecked())
    {
        ui->pushButton_repeat_mode->setChecked(false);
    }
    else
        ui->pushButton_repeat_mode->setChecked(true);

}

/*Pasa a la anterior cancion y la reproduce.Si estaba en la primera cancion de la lista,pasa a reproducir la ultima*/
void MainWindow::on_pushButton_prev_clicked()
{
    if(lista_canciones->IsItemSelected())
    {
        if(isPlaying || isPaused)
        {
            int aux=lista_canciones->GoToPrevSong();


            if(!aux)
            {
                UpdatePlayerSongInfo();

                play_song();
             }
             else
            {
                lista_canciones->GoToEnd();

                UpdatePlayerSongInfo();

                play_song();
            }
        }
    }

}
/*---------------------------------------------------------*
*                                                          *
*                                                          *
*    FUNCIONES RELACIONADAS CON EL TIEMPO DE LA CANCION    *
*                       TIMER  Y PROGRESS BAR              *
*                                                          *
*----------------------------------------------------------*/

/*En el timeout del timer(1 segundo) se activa ActualizarTiempo() y actualiza el valor de curr_time*/

void MainWindow::actualizarTiempo()
{


    if(curr_time==Songs_Durations[lista_canciones->song_number].toInt())
    {
        Timer_Seg->stop();

        curr_time=0;

        PlayNextSong();
    }else
    {
        curr_time++;       

        ui->label_curr_time->setText(SD_exp->SegToMin(curr_time));

        ui->progressBar->update();

        ui->horizontalSlider->update();

        emit curr_time_Changed(curr_time);

    }
}

/*Resetea el timer y el valor de curr_time*/
void MainWindow::resetCurrTime()
{
    curr_time=0;

    ui->label_curr_time->setText(SD_exp->SegToMin(0));

    Timer_Seg->stop();

    Timer_Seg->start();

}
/*Inicializa la QProgressBar con el valor maximo y minimo de la misma */
void MainWindow::InitProgressBar()
{
    ui->progressBar->setMinimum(0);

    ui->progressBar->setMaximum(Songs_Durations[lista_canciones->song_number].toInt());

    ui->progressBar->repaint();

    ui->progressBar->setValue(0);


}
/*Inicializa la QSlider del tiempo con el valor maximo y minimo de la misma */
void MainWindow::InitSlider()
{

    ui->horizontalSlider->setMinimum(0);

    ui->horizontalSlider->setMaximum(Songs_Durations[lista_canciones->song_number].toInt());

    ui->horizontalSlider->repaint();

    ui->horizontalSlider->setValue(0);


}
/*Desconecta la señal para que mientras el tiempo avance el slider no se mueva ya que esta el mouse presionandolo*/
void MainWindow::onSliderPressed()
{
    disconnect(this,SIGNAL(curr_time_Changed(int)),ui->horizontalSlider,SLOT(setValue(int)));
}

/*Cambia el tiempo de la cancion a donde quedo parado el slider cuando se solto el mouse*/
void MainWindow::onSliderReleased()
{
    connect(this,SIGNAL(curr_time_Changed(int)),ui->horizontalSlider,SLOT(setValue(int)));

    curr_time=ui->horizontalSlider->value();

    Timer_Seg->stop();

    if(curr_time==Songs_Durations[lista_canciones->song_number].toInt()) //Si se dejo el slider al final de la cancion,se pasa a la proxima
    {
        Timer_Seg->stop();

        curr_time=0;

        PlayNextSong();

    }else if(curr_time==0) //Si se dejo el slider al principio de la cancion,se la reproduce devuelta

        play_song();
    else
    {
    ui->label_curr_time->setText(SD_exp->SegToMin(curr_time));

    QString aux=TimeToCommand(curr_time);

    RS232_handler->EnviarComando(aux);

    Timer_Seg->start();
    }

}
/*Resetea el timer del tiempo*/
void MainWindow::onSyncDone()
{
    Timer_Seg->stop();

    Timer_Seg->start();
}
/*Transforma un entero dado como parametro que representa un tiempo en segundos en un QString con el formato del comando "t=xxxx"*/
QString MainWindow::TimeToCommand(int time)
{

/*Convierto el tiempo dado como parametro en un string*/
string Result;

ostringstream convert;

convert << time;

Result = convert.str();

QString aux("t=");


for(int i=0;i<4-NumberLenght(time);i++)
    aux.append('0');

aux.append(Result.data());




return aux;
}
/*Calcula longitud de digitos de un numero*/
int MainWindow::NumberLenght(int nro)
{
    int ctr=0;

    while(nro)
    {
        nro/=10;
        ctr++;
    }
    return ctr;
}
/*---------------------------------------------------------*
*                                                          *                                     *
*    FUNCIONES RELACIONADAS CON EL VOLUMEN DE LA CANCION   *
*----------------------------------------------------------*/

/*Cambio el volumen del reproductor enviando por UART el comando correspondiente al micro*/
void MainWindow::onSliderVolMoved(int vol)
{

    /*Paso el entero vol a un string*/
    QString vol_string;

    string Result;

    ostringstream convert;

    convert << vol;

    Result = convert.str();

    /*Queda el comando VOLxxx donde xxx es el valor vol pasado a string*/
    QString aux("VOL");

    /*Agrego ceros si hace falta para que el comando tenga 6 caracteres siempre y asi cumplir con la trama*/
    if(vol<10)
        aux.append("00");
    else if(vol<100)
        aux.append('0');

    aux.append(Result.data());

    RS232_handler->EnviarComando(aux);

    /*Muestro el valor del volumen en porcentaje*/
    vol_string=QString::number(vol*100/180);

    vol_string.append("%");

    ui->label_valor_volumen->setText(vol_string);


}
