#ifndef WORDLE_H
#define WORDLE_H

#include "gamewindow.h"
#include <fstream>

using namespace std;

class Wordle
{
private:
    QStringList words;
public:
    Wordle();
    QString getWord();
    int times(QString letter, QString word);
};

#endif // WORDLE_H
