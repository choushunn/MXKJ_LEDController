#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 初始化串口信息
    updateSerialPortList();
    // 连接串口数据接收信号
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    iniUI();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateSerialPortList()
{
    // 清空之前的串口列表
    ui->comboBox->clear();

    // 查找可用的串口
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        // 添加串口名到下拉框
        ui->comboBox->addItem(info.portName() + ": " + info.description());
    }
    // if(!serial.isOpen()){
    //     ui->horizontalSlider->setDisabled(true);
    // }
}


void MainWindow::on_m_btn_connect_clicked()
{
    // 获取当前选中的串口名
    QString portName = ui->comboBox->currentText().split(":").first().trimmed();

    // 根据串口名创建串口对象
    serial.setPortName(portName);

    // 打开串口
    if (serial.open(QIODevice::ReadWrite)) {
        // 串口打开成功，提示连接成功
        qDebug() << "串口连接成功";
        statusBar()->showMessage("串口连接成功");
        ui->m_btn_connect->setText("断开");
    } else {
        // 串口打开失败，提示连接失败
        serial.close();
        qDebug() << "串口连接失败";
        ui->m_btn_connect->setText("连接");
        statusBar()->showMessage("串口连接失败");
    }
}

void MainWindow::readSerialData()
{
    QByteArray data = serial.readAll(); // 读取串口接收缓冲区中的所有数据
    QString textData = QString::fromUtf8(data); // 将字节数组转换为字符串
    qDebug() << "Received data:" << textData;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << value;
    ui->spinBox->setValue(value);
    value = 255 - value;
    // 将 value 限制在 0 到 255 之间
    value = qBound(0, value, 255);
    // 将整数转换为字符串
    QString data = QString::number(value);

    // 发送数据
    serial.write(data.toUtf8());

}

void MainWindow::iniUI()
{
    //界面组件初始化
    QList<int> list;
    list = {1,2,3,4,5};
    qDebug() << list;

}

void MainWindow::iniSignalSlots()
{
    //信号槽关联
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{

}

