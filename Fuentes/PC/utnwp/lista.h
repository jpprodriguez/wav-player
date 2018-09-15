#ifndef LISTA_H
#define LISTA_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class lista;
}

class lista : public QWidget
{
    Q_OBJECT

    friend class MainWindow;


    
public:
    void LimpiarLista();
    bool GoToNextSong();
    void GoToIndex();
    int GoToPrevSong();
    void GoToEnd();
    bool IsItemSelected();
    QStringList* stringList_canciones;
    void AddItem(QString);
    QStringList GetSongToPlay();
    explicit lista(QWidget *parent = 0);
    ~lista();
    
private slots:
    void on_listWidget_lista_canciones_itemDoubleClicked();

    void OnCurrentRowChanged();

private:
    Ui::lista *ui;
    int song_number;
    QString song_ready_to_be_played;
    QString last_song_played;

signals:
    void SongWaiting();
    void GetSDSongPos();

};


#endif // LISTA_H
