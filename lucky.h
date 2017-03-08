#ifndef LUCKY_H
#define LUCKY_H

#include <QWidget>
#include<QTime>
#include<QTimer>
#include<QRect>
#include<QLabel>
#include<QPushButton>
#include<QDesktopWidget>
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QStringList>
#include<QVector>
#include"music.h"

namespace Ui {
class Lucky;
}

struct StrCfg{
    QString Bg;
    QString Icon;
    QString Se1;
    QString Se2;
    QString Min;
    QString Max;
};

class Lucky : public QWidget
{
    Q_OBJECT

public:
    explicit Lucky(QWidget *parent = 0);
    ~Lucky();

private:
    Ui::Lucky *ui;
    QPushButton Start;
    QPushButton Stop;
    QRect rect;
    QLabel LNum;
    QTimer Time;
    StrCfg Cfg;
    QVector<QString> Name;

    void Init();
    void ctlInit();
    QRect getRect();
    void readCfg();

    void WindowInit();
    void StartInit();
    void StopInit();
    void LNumInit();
    void readName();
public slots:
    void on_StartRelease();
    void on_StopRelease();
    void on_TimeOut();
};

#endif // LUCKY_H
