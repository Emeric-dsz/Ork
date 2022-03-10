#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include "character.h"
#include "room.h"

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

    void on_Map_clicked();

    void on_North_clicked();

    void on_South_clicked();

    void on_East_clicked();

    void on_West_clicked();

    void on_Take_clicked(bool checked);

private:
    Ui::GameWindow *ui;
    void createRooms();
    Room* currentRoom;
    list<Room*> rooms;
};

#endif // GAMEWINDOW_H
