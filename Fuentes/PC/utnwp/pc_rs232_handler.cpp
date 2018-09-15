#include "pc_rs232_handler.h"
#include <mainwindow.h>


pc_rs232_handler::pc_rs232_handler(QObject *parent) :
    QObject(parent)
{
    rs232 = new QextSerialPort;

    Timer_devices= new QTimer(this);
    Timer_devices->setSingleShot(true);

    Timer_Tx= new QTimer(this);
    Timer_Tx->setSingleShot(true);

    connect(Timer_Tx,SIGNAL(timeout()),this,SLOT(OnTimerTxTimeout()));

    flag_connected=false;
    modo=NADA;


    QextSerialEnumerator *enumerator = new QextSerialEnumerator();

    /*Se habilitan notificaciones para que el programa se entere cuando se desconecta o conecta algun dispositivo de la pc*/
    enumerator->setUpNotifications();

    connect(enumerator, SIGNAL(deviceDiscovered(const QextPortInfo &)),
            this, SLOT(onDeviceConnected(const QextPortInfo &)));

    connect(enumerator, SIGNAL(deviceRemoved(const QextPortInfo &)),
            this, SLOT(onDeviceRemoved(const QextPortInfo &)));

}

QString pc_rs232_handler::puerto=0;

/*Se abre el puerto de rs232 y se lo conecta con la placa */
void pc_rs232_handler::Connect()
{

    if(puerto.isEmpty())
    {
        emit ConnectionFailed();
    }else{
        if(rs232->isOpen())
                rs232->close();
    delete rs232;
    rs232 = new QextSerialPort(puerto, QextSerialPort::EventDriven);

    rs232->setDataBits(DATA_8);
    rs232->setStopBits(STOP_1);
    rs232->setParity(PAR_NONE);
    rs232->setFlowControl(FLOW_OFF);
    rs232->setBaudRate(BAUD9600);


    if (rs232->open(QIODevice::ReadWrite))
    {

        connect(rs232, SIGNAL(readyRead()),this, SLOT(RecibirDatos()));

        emit ConnectionSuccess();

        EnviarComando("STOP00"); //Resetea la placa


    }else
        emit ConnectionFailed();
}
}

/*Funcion que se ejectua cada vez que se emite la señal readyRead() avisando que llegaron datos al puerto.
  Guarda los datos recibidos en un buffer*/
void pc_rs232_handler::RecibirDatos()
{
    QByteArray bytes;

    int cant = rs232->bytesAvailable();



    bytes.resize(cant);

    rs232->read(bytes.data(), bytes.size());

    rs232->flush();


        Buff_received.append(bytes.data());


        if(Buff_received=="$#RESET")
        {
            emit SinConexion();
            EmptyBuffer();
        }


}
/*Crea un Qstring del formato "<cmd>" donde cmd se da como parametro y se lo envia por el puerto*/
void pc_rs232_handler::EnviarComando(QString cmd)
{
    if(flag_connected==true)
    {
    QString aux("<");
    aux.append(cmd);
    aux.append(">");

    rs232->write(aux.toLocal8Bit());

    if(Timer_Tx->isActive())
        Timer_Tx->setInterval(400);
    else
        Timer_Tx->start(400);
    }

}

/*Borra el buffer donde se guarda lo que se recibio*/
void pc_rs232_handler::EmptyBuffer() {Buff_received="";}

/*Funcion que se ejecuta para ver si ya se recibio toda la informacion de la SD.Si ya se recibio todo devuelve true,sino devuelve false*/
bool pc_rs232_handler::SDListUploadFinished()
{
    if(Buff_received.contains("$@"))
    {
        isSDListEmpty=false;
        Buff_received.remove(Buff_received.indexOf(QString("$@")),Buff_received.length());
        Buff_received.remove(0,Buff_received.indexOf(QString("@$"))+2);

        modo=NADA;
        return true;
    }else
    {
        isSDListEmpty=true;
        return false;
    }
}

/*Devuelve el buffer que contiene la informacion que se recibio*/
QString& pc_rs232_handler::getDataBuff(){ return Buff_received;}

/*Slot que se ejecuta cuando se desconecta un dispositivo de la PC*/
void pc_rs232_handler::onDeviceRemoved(const QextPortInfo &info)
{
    if(Timer_devices->remainingTime()==0 || Timer_devices->isActive()==false)
    {
    if (info.portName==puerto) //si el cable que se desconecto es el que estaba usandose,se avisa que se corto la conexion
        emit SinConexion();
    }
}

/*Slot que se ejecuta cuando se conecta un dispositivo a la PC*/
void pc_rs232_handler::onDeviceConnected(const QextPortInfo &info)
{
    if (info.portName==puerto && flag_connected==false) //si el cable que se conecto es el que estaba usandose y estaba desconectado,se conecta automaticamente
        this->Connect();

    Timer_devices->start(2000); //Pongo un delay porque hay un error en la señal,ni bien conecto el cable lo toma como que se desconecto al instante,por eso esperando ese tiempo no llega a desconectarse ni bien lo conecto

}

/*Cambia el estado del la variable flag_connected por la que se da como parametro*/
void pc_rs232_handler::SetFlagConnected(bool estado)
{
   flag_connected=estado;
}
/*Funcion que se ejecuta cuando timertx llega a 0. Se escribe en el puerto y se vuelve a empezar el timer*/
void pc_rs232_handler::OnTimerTxTimeout()
{
    if(flag_connected==true)
    {
    rs232->write("-",1);
    Timer_Tx->start(400);
    }
}
