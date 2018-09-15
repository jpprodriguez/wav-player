#ifndef DIALOG_CONECTAR_H
#define DIALOG_CONECTAR_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Dialog_conectar;
}

class Dialog_conectar : public QDialog
{
    Q_OBJECT
    
public:
    void GetPort(QString &);
    explicit Dialog_conectar(QWidget *parent = 0);
    ~Dialog_conectar();
    
private slots:
    void on_pushButton_connect_released();
    void EnumerarPuertos();

private:
    Ui::Dialog_conectar *ui;
    void closeEvent(QCloseEvent *event);

signals:
    void NewPortReady(void);
};

#endif // DIALOG_CONECTAR_H
