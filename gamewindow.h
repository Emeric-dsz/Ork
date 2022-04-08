#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <list>

#include "character.h"
#include "wordle.h"
#include "room.h"

namespace Ui {
class GameWindow;
}

struct letters{
    letters(QChar l, int p){
        letter = l;
        place = p;
        misplaced = false;
        rightP = false;
    };
    QChar letter;
    int place;
    bool misplaced;
    bool rightP;
};

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QString name,QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_Life_valueChanged(int value);

    void on_Map_clicked();



    void on_Take_clicked(bool checked);

    void on_Inventory_itemDoubleClicked(QListWidgetItem *item);

    void on_Attack_clicked();
    void on_North_clicked();
    void on_South_clicked();
    void on_East_clicked();
    void on_West_clicked();

    void on_Enter_clicked();

private:
    Ui::GameWindow *ui;
    void createRooms();
    player *player;
    Wordle *wordle;
    void sort(letters** to);
    void check(QString word, letters** isRight);
};

#endif // GAMEWINDOW_H
