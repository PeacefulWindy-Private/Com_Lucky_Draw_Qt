#include "lucky.h"
#include "ui_lucky.h"

Music Media;

Lucky::Lucky(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lucky)
{
    ui->setupUi(this);
    Lucky::readCfg();
    Lucky::readName();
    Lucky::Init();
    Lucky::ctlInit();
}

Lucky::~Lucky()
{
    delete ui;
}

void Lucky::Init()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Time.setParent(this);
    connect(&Time,SIGNAL(timeout()),this,SLOT(on_TimeOut()));
    rect=Lucky::getRect();
}

void Lucky::readName()
{
    QFile file("namelist.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream ts(&file);
        ts.setCodec("UTF-8");
        while(!ts.atEnd())
        {
            Name.append(ts.readLine());
        }
        file.close();

    }
    else if(file.open(QIODevice::WriteOnly))
    {
        file.close();
    }
}

void Lucky::readCfg()
{
    QFile FCfg("config.ini");
    if(FCfg.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMap<QString,int>map;
        map.insert("background",1);
        map.insert("icon",2);
        map.insert("startse",3);
        map.insert("stopse",4);
        map.insert("randmin",5);
        map.insert("randmax",6);

        QTextStream ts(&FCfg);
        ts.setCodec("UTF-8");
        QString tx;
        QStringList tl;
        while(!ts.atEnd())
        {
            tx=ts.readLine();
            tl=tx.split(",");
            if(tl.size()>=2)
            {
                switch(map.value(tl.at(0)))
                {
                case 1:
                    Cfg.Bg=tl.at(1);
                    break;
                case 2:
                    Cfg.Icon=tl.at(1);
                    break;
                case 3:
                    Cfg.Se1=tl.at(1);
                    break;
                case 4:
                    Cfg.Se2=tl.at(1);
                    break;
                case 5:
                    Cfg.Min=tl.at(1);
                    break;
                case 6:
                    Cfg.Max=tl.at(1);
                    break;
                }
            }
        }
        FCfg.close();
        return;
    }
    else if(FCfg.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream ts(&FCfg);
        ts.setCodec("UTF-8");
        ts<<tr("设置背景图片")<<endl;
        ts<<"background,imgs/background.jpg"<<endl;
        ts<<tr("设置图标")<<endl;
        ts<<"icon,imgs/icon.png"<<endl;
        ts<<tr("设置开始抽奖的音效（重复）")<<endl;
        ts<<"startse,se/001.mp3"<<endl;
        ts<<tr("设置停止抽奖的音效（不重复）")<<endl;
        ts<<"stopse,se/002.mp3"<<endl;
        ts<<tr("设置随机数最小值（包含该值）")<<endl;
        ts<<"randmin,1"<<endl;
        ts<<tr("设置随机数最大值（包含该值）")<<endl;
        ts<<"randmax,1000"<<endl;
        FCfg.close();

        Cfg.Bg="imgs/background.jpg";
        Cfg.Icon="imgs/icon.png";
        Cfg.Se1="se/001.mp3";
        Cfg.Se2="se/002.mp3";
        Cfg.Min="1";
        Cfg.Max="1000";

        return;
    }
}

QRect Lucky::getRect()
{
    return QApplication::desktop()->availableGeometry();
}

void Lucky::on_TimeOut()
{
    if(Name.size()>0)
    {
        LNum.setText(Name.at(qrand()%Name.size()));
    }
    else
    {
        LNum.setText(QString::number(qrand()%(Cfg.Max.toInt()+1)+Cfg.Min.toInt(),10));
    }

}

void Lucky::WindowInit()
{
    QPixmap pix(Cfg.Bg);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    this->setGeometry(rect.width()*20/100,
                      rect.height()*20/100,
                      rect.width()*60/100,
                      rect.height()*60/100);
    this->setFixedSize(rect.width()*60/100,
                       rect.height()*60/100);
    pix=pix.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background,pix);

    pix.load(Cfg.Icon);
    this->setWindowIcon(pix);
    this->setWindowTitle("计算机协会抽奖系统");
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void Lucky::StartInit()
{
    QFont font;
    font.setPointSize(16*rect.width()/800);
    font.setFamily("宋体");
    font.setBold(true);

    QPalette palette;
    palette.setColor(QPalette::ButtonText,QColor(255,255,255));

    Start.setParent(this);
    Start.setPalette(palette);
    Start.setFont(font);
    Start.setStyleSheet("background-color:#0AC986");
    Start.setText("开始抽奖");
    connect(&Start,SIGNAL(released()),this,SLOT(on_StartRelease()));
    Start.setGeometry(this->width()*35/100,
                      this->height()*70/100,
                      this->width()*30/100,
                      this->height()*10/100);
    Start.show();
}

void Lucky::StopInit()
{
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);
    font.setPixelSize(10*rect.width()/800);

    QPalette palette;
    palette.setColor(QPalette::ButtonText,QColor(255,255,255));

    Stop.setParent(this);
    Stop.setPalette(palette);
    Stop.setStyleSheet("background-color:#EA0653");
    Stop.setFont(font);
    Stop.setText("停止");
    connect(&Stop,SIGNAL(released()),this,SLOT(on_StopRelease()));
    Stop.setGeometry(this->width()*38/100,
                      this->height()*85/100,
                      this->width()*24/100,
                      this->height()*5/100);
    Stop.show();
}

void Lucky::LNumInit()
{
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);
    font.setPixelSize(60*rect.width()/800);

    QPalette palette;
    palette.setColor(QPalette::WindowText,QColor(255,255,255,180));

    LNum.setParent(this);
    LNum.setFont(font);
    LNum.setPalette(palette);
    LNum.setAlignment(Qt::AlignCenter);
    LNum.setText("0000");
    LNum.setGeometry(this->width()*30/100,
                     this->height()*38/100,
                     this->width()*40/100,
                     this->height()*20/100);
    LNum.show();
}

void Lucky::ctlInit()
{
    Lucky::WindowInit();
    Lucky::StartInit();
    Lucky::StopInit();
    Lucky::LNumInit();
}

void Lucky::on_StartRelease()
{
    Time.start(20);
    Media.Stop();
    Media.Play(Cfg.Se1.toStdString(),true);
}

void Lucky::on_StopRelease()
{
    Time.stop();
    Media.Stop();
    Media.Play(Cfg.Se2.toStdString(),false);
}
