#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->Name->setHtml("<p align='center' style='font-size:20px;font-weight:bold;'>"+name+"</p>");
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_Ouch_clicked()
{
    ui->Life->setValue(ui->Life->value() - 10);
}


void GameWindow::on_Life_valueChanged(int value)
{
    if (value == 0)
        QApplication::quit();
}

