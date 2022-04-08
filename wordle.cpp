#include "wordle.h"

Wordle::Wordle(){
    ifstream file("words.txt");
    string line;
    if(file.is_open()) {
        while (getline(file,line)) {
            words.append(QString::fromStdString(line.substr(0,5)));
        }
    }
    else
        throw("File not found.");
}

QString Wordle::getWord(){
    int random = rand() % words.size();
    QStringList::iterator it = words.begin();
    advance(it,random);
    return *it;
}

int Wordle::times(QString letter, QString word){
    int time = 0;
    QString::iterator x = word.begin();
    while(x!=word.end()){
        if(*x==letter)
            time++;
        x++;
    }
    return time;
}


