#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSize window_size = MainWindow::size();
    ui->textBrowser->move(window_size.width()/3,window_size.height()/3);
    ui->start->move(window_size.width()/3 + 100,window_size.height()/3 + 100);
    ui->exit->move(window_size.width()/3 + 100,window_size.height()/3 + 150);
    /*push_button2 = new QPushButton(this);
    push_button2->setText("Click");
    push_button2->setGeometry(QRect(QPoint(0, 0), QSize(100, 50)));
    connect(push_button2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    ui->textBrowser->setHtml("<p align='center'> Enter your Name </p>");
    ui->textBrowser->setReadOnly(false);
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

