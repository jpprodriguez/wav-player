#ifndef PC_RS232_HANDLER_H
#define PC_RS232_HANDLER_H

#include "qextserialport.h"
#include <QTimer>
#include "qextserialenumerator.h"

#define TIEMPO 0
#define COMANDO 1
#define SD 2
#define NADA 3

class pc_rs232_handler : public QObject
{
    Q_OBJECT

    //friend class MainWindow;

public:   

    explicit pc_rs232_handler(QObject *parent = 0);
    static QString puerto;
    int tiempo_infotronic;
    char modo;
    void Connect();
    void EnviarComando(QString);
    int GetSongdurationInsecs();
    bool PlaySong(char*);
    bool StopSong();
    bool PauseSong();
    void EmptyBuffer();
    bool SDListUploadFinished();
    void SetFlagConnected(bool);
    QString& getDataBuff();


private:
    QString Buff_received;
    QTimer* timer_flow_data;
    QTimer* Timer_devices;
    QTimer* Timer_Tx;
    QextSerialPort* rs232;
    bool isSDListEmpty;
    bool flag_connected;

public slots:
        void RecibirDatos();

private slots:
        void onDeviceRemoved(const QextPortInfo &);
        void onDeviceConnected(const QextPortInfo &);
        void OnTimerTxTimeout();

signals:
        void ConnectionFailed(void);
        void ConnectionSuccess(void);
        void SinConexion(void);
};

#endif // PC_RS232_HANDLER_H
