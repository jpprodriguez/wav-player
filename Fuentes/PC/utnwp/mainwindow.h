#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <microsd_explorer.h>
#include <QMessageBox>
#include <lista.h>
#include <QTextStream>
#include <dialog_conectar.h>
#include <pc_rs232_handler.h>
#include <QIcon>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    
public:


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    
private:
    void closeEvent(QCloseEvent *event);
    static int curr_time;
    QStringList Songs_Names;
    QStringList Songs_Authors;
    QStringList Songs_Durations;
    QTimer* Timer_Seg;
    bool flag_connected;
    bool isPaused;
    bool isPlaying;
    pc_rs232_handler *RS232_handler;
    Dialog_conectar* connect_interface;
    lista *lista_canciones;
    MicroSD_explorer *SD_exp;
    Ui::MainWindow *ui;
    QStringList SD_songsdata(QString&);
    QString getSongNumber();
    void UpdatePlayerSongInfo();
    void resetPlayerSongInfo();
    void resetCurrTime();
    void InitProgressBar();
    void InitSlider();
    QString TimeToCommand(int time);
    int NumberLenght(int nro);





private slots:
    void get_SD_list();
    void SDExp_to_SongList();
    void play_song();
    void PlayNextSong();
    void pause_song();
    void resume_song();
    void stop_song();
    void OnConnect();
    void OnDisconnect();
    void onSDListDataReady();
    void OnGetSDPos();
    void onSongWaiting();
    void change_play_icon();
    void actualizarTiempo();
    void OpenConnectDialog();
    void onPushButtonList();
    void onNewPortReady();

    void on_pushButton_play_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_repeat_mode_clicked();
    void on_pushButton_prev_clicked();
    void onSliderReleased();
    void onSliderPressed();
    void onSyncDone();

    void onSliderVolMoved(int);


signals:
    void curr_time_Changed(int curr_time);

};

#endif // MAINWINDOW_H
