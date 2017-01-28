#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1366,768);

    label1=new QLabel(this);
    label1->setGeometry(0,0,1366,768);
    label1->setPixmap(QPixmap("/home/mher97/projects/Game/resources/desert6.jpg"));

    QFont f("Sans",20,10);
    start=new QPushButton("Start",this);
    start->setGeometry(500,247,317,50);
    start->setStyleSheet("QPushButton { background-color : transparent; color : black; }");
    start->setFont(f);

    about=new QPushButton("About",this);
    about->setGeometry(500,302,317,50);
    about->setStyleSheet("QPushButton { background-color : transparent; color : black; }");
    about->setFont(f);

    exit=new QPushButton("Exit",this);
    exit->setGeometry(500,357,317,50);
    exit->setStyleSheet("QPushButton { background-color : transparent; color : black; }");
    exit->setFont(f);


    slider=new QSlider(Qt::Horizontal,this);
    slider->setGeometry(1200,700,100,40);
    slider->setRange(0,100);
    slider->setValue(50);

    sound_label=new QLabel(this);
    sound_label->setText("<b>Sound</b>");
    sound_label->setGeometry(1200,670,70,40);
    sound_off=new QPushButton("OFF",this);
    sound_off->setStyleSheet("QPushButton { background-color : red; color : black; }");
    sound_off->setGeometry(1260,680,30,15);
    sound_on=new QPushButton("ON",this);
    sound_on->setStyleSheet("QPushButton { background-color : red; color : black; }");
    sound_on->setGeometry(1260,682,30,15);

    media=new QMediaPlayer();
    playlist=new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("/home/mher97/projects/Game/resources/music/USSR.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("/home/mher97/projects/Game/resources/music/credits.wav"));
    playlist->addMedia(QUrl::fromLocalFile("/home/mher97/projects/Game/resources/music/byob_soad.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("/home/mher97/projects/Game/resources/music/Wolfgang Amadeus Mozart - Реквием по мечте Лондонский сим....mp3"));
    media->setPlaylist(playlist);

    timer=new QTimer(this);
    connect(slider,SIGNAL(valueChanged(int)),media,SLOT(setVolume(int)));

    connect(sound_on,SIGNAL(clicked()),this,SLOT(mediaslot0()));
    connect(sound_on,SIGNAL(clicked()),this,SLOT(mediaslot1()));
    connect(sound_on,SIGNAL(clicked()),sound_on,SLOT(hide()));
    connect(sound_on,SIGNAL(clicked()),sound_off,SLOT(show()));

    connect(sound_off,SIGNAL(clicked()),this,SLOT(mediaslot2()));
    connect(sound_off,SIGNAL(clicked()),sound_off,SLOT(hide()));
    connect(sound_off,SIGNAL(clicked()),sound_on,SLOT(show()));

    this->about_widget_maker();
    //connect(start,SIGNAL(clicked()),this,SLOT(hide()));
    connect(start,SIGNAL(clicked()),this,SLOT(widget_show()));
    connect(about,SIGNAL(clicked()),about_widget,SLOT(showFullScreen()));
    connect(about,SIGNAL(clicked()),this,SLOT(hide()));
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));
    this->setWindowIcon(QIcon("/home/mher97/projects/Game/resources/dinoo.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about_widget_maker()
{
    QFont *font=new QFont("Sans",20,20);

    about_widget=new QWidget();
    about_widget->setGeometry(0,0,1366,768);
    QLabel *local_label=new QLabel(about_widget),*local_label2=new QLabel(about_widget);
    local_label->setGeometry(0,0,1366,768);
    local_label2->setGeometry(480,250,368,268);
    local_label->setPixmap((QPixmap("/home/mher97/projects/Game/resources/sea2.jpg")));
    local_label2->setFont(*font);
    local_label2->setStyleSheet("QLabel {color:black;}");
    local_label2->setText("In order to know about the \n   game you just play ..."
                           "\n \n \n" "Created by Mher Hakobyan");

    QPushButton *local=new QPushButton("Exit",about_widget);
    local->setGeometry(1250,10,60,30);
    local->setStyleSheet("QPushButton { background-color : yellow; color : black; }");
    connect(local,SIGNAL(clicked()),about_widget,SLOT(close()));
    connect(local,SIGNAL(clicked()),this,SLOT(showFullScreen()));
}

void MainWindow::mediaslot0()
{
    media->setVolume(slider->value());
    media->play();
}

void MainWindow::mediaslot1()
{
     connect(timer,SIGNAL(timeout()),media,SLOT(play()));
     timer->start(680000);
}

void MainWindow::mediaslot2()
{
    media->stop();
    media->setVolume(0);
}

void MainWindow::widget_show()
{
    W=new widget();
    W->showFullScreen();
}
