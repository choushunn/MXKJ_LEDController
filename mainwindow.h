#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateSerialPortList();
    QSerialPort serial;
private slots:


    void on_m_btn_connect_clicked();
    void readSerialData();
    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();
    void checkSerialPortStatus();
private:
    Ui::MainWindow *ui;
    void iniUI();
    void iniSignalSlots();
    bool ledState=false; // LED状态变量
    void handleSerialError(QSerialPort::SerialPortError);
    QTimer checkTimer;

};
#endif // MAINWINDOW_H
