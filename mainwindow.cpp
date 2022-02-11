#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    QSize window_size = MainWindow::size()/2;
    QSize textS = ui->textEdit->size()/2;
    QSize buttonS = ui->start->size()/2;
    ui->set->setVisible(false);
    ui->textEdit->move(window_size.width() - textS.width(),window_size.height() - textS.width());
    ui->start->move(window_size.width() - buttonS.width(),window_size.height() - buttonS.height() + 10);
    ui->set->move(window_size.width() - buttonS.width(),window_size.height() - buttonS.height() + 10);
    ui->exit->move(window_size.width() - buttonS.width(),window_size.height() - buttonS.height() + 40);
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
    ui->textEdit->setHtml("<p align='center'> Enter your Name </p>");
    ui->textEdit->setReadOnly(false);
    ui->start->setDisabled(true);
    ui->set->setEnabled(true);
    ui->start->setVisible(false);
    ui->set->setVisible(true);
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_set_clicked()
{
    QString name = ui->textEdit->toPlainText();
    GameWindow *g = new GameWindow(name);
    g->show();
    close();
}

