#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QString name,QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_Ouch_clicked();

    void on_Life_valueChanged(int value);

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
