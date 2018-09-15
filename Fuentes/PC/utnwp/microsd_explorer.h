#ifndef MICROSD_EXPLORER_H
#define MICROSD_EXPLORER_H

#include <QWidget>
#include <QStringList>
#include <QListWidgetItem>
#include <QCloseEvent>

namespace Ui {
class MicroSD_explorer;
}

class MicroSD_explorer : public QWidget
{
    Q_OBJECT
    
public:
    QString SegToMin(int segs);
    QListWidgetItem* ListCurrentItem();
    void LimpiarLista();
    void CargarLista(QStringList);
    explicit MicroSD_explorer(QWidget *parent = 0);
    ~MicroSD_explorer();
    
private slots:
    void on_pushButton_agregar_released();
    void DisableButton_agregar();
    void EnableButton_agregar();
    void DisableButton_actualizar();
    void EnableButton_actualizar();


    void on_pushButton_ActualizarLista_released();

private:
    Ui::MicroSD_explorer *ui;

signals:
    void CargaLista_Done();
    void pushButton_agregar_released();
    void ReadyToUpdate();




};

#endif // MICROSD_EXPLORER_H
