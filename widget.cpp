#include "widget.h"
#include "ui_widget.h"
#include <QDebug>



widget::widget(QWidget *parent) :QWidget(parent),ui(new Ui::widget)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1366,768);
    counter=0;

    desert = QImage("/home/mher97/projects/Game/resources/desert11.jpg");
    sky = QImage("/home/mher97/projects/Game/resources/sky.jpg");
    flag=QImage("/home/mher97/projects/Game/resources/flag.png");
    cactus1=QImage("/home/mher97/projects/Game/resources/cactus1.png");
    cactus2=QImage("/home/mher97/projects/Game/resources/cactus3.png");
    dino=QImage("/home/mher97/projects/Game/resources/dino.png");
    back=QImage("/home/mher97/projects/Game/resources/back.png");

    V = vector<int>(101,0);
    flag_x=136600-366;
    cactus_x=1000;
    dino_y=588;
    dino_flag=false;

    for (int i=1;i<101;++i)
    {
        V[i]=V[i-1]+1366;

    }
    for(;;)
    {
        srand(time(NULL));
        if (counter)
        {
            counter=1-counter;
            for_type.push_back(true);
        }
        else
        {
            for_type.push_back(false);
            counter=1-counter;
        }
        if (cactus_x<=20000)
            cactus_x+=rand()%100+650;
        else if (cactus_x>20000 && cactus_x<=50000)
            cactus_x+=rand()%100+500;
        else if (cactus_x>50000 && cactus_x<=80000)
            cactus_x+=rand()%100+600;
        else if (cactus_x>80000)
            cactus_x+=rand()%100+625;
        cactuses.push_back(cactus_x);
        if (cactus_x+600>135600)
            break;
    }
    random_shuffle(for_type.begin(),for_type.end());
    counter=0;
    pix=2;
    winner_flag=false;
    collission_flag=false;

    t=new QTimer();
    dino_t=new QTimer();
    t->start(8);
    connect(t,SIGNAL(timeout()),this,SLOT(move()));

    connect(dino_t,SIGNAL(timeout()),this,SLOT(dino_jump()));

    myfile.setFileName("/home/mher97/projects/Game/score.txt");
    if (!myfile.open(QFile::ReadOnly | QFile::Text))
    {
        highscore=0;
    }
    QTextStream in(&myfile);
    QString str=in.readLine();
    highscore=str.toInt();
    myfile.flush();
    myfile.close();

    score=0;
    score_text_label=new QLabel(this);
    score_label=new QLabel(this);
    score_label->setGeometry(1220,30,100,30);
    score_text_label->setGeometry(1100,30,100,30);
    font=new QFont("Sans",20,20);
    score_label->setFont(*font);
    score_text_label->setFont(*font);
    score_text_label->setText("SCORE ");
    score_label->setText("0");

    sound[0]=new QSound("/home/mher97/projects/Game/resources/sounds/Mariocoinsound.wav");
    sound[1]=new QSound("/home/mher97/projects/Game/resources/sounds/carmetal.wav");
    sound[2]=new QSound("/home/mher97/projects/Game/resources/sounds/tada.wav");

    movie=new QMovie("/home/mher97/projects/Game/resources/dino_anim2.gif");
    animlabel=new QLabel(this);
    anim_label_y=656;
    animlabel->setGeometry(229,anim_label_y,43,31);
    animlabel->setMovie(movie);
    movie->start();

    this->setWindowIcon(QIcon("/home/mher97"
                              "/projects/Game/resources/dinoo.png"));
}

widget::~widget()
{
    delete ui;
}

QRectF widget::draw_image(int a, int b, int c, int d)
{
    return QRect(a,b,c,d);
}

void widget::W_widget_maker()
{
    W_widget=new QWidget(this);
    W_widget->setGeometry(400,200,514,368);
    W_widget->setStyleSheet("QWidget { background-color : green; color : black; }");
    QLabel **locals;
    QPushButton *button;
    locals=new QLabel*[3];
    for (int i=0;i<3;++i)
    {
        locals[i]=new QLabel(W_widget);
        locals[i]->setStyleSheet("QLabel {color:white;}");
        locals[i]->setFont(*font);
    }
    locals[0]->setGeometry(200,50,150,64);
    locals[1]->setGeometry(50,130,150,30);
    locals[2]->setGeometry(50,170,150,30);
    locals[0]->setText("You win");
    locals[1]->setText("Your score");
    locals[2]->setText("High score");

    button=new QPushButton(W_widget);
    button->setGeometry(150,310,214,50);
    button->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
    button->setFont(*font);
    button->setText("Main Menu");
    connect(button,SIGNAL(clicked()),W_widget,SLOT(close()));
    connect(button,SIGNAL(clicked()),this,SLOT(close()));
}

void widget::L_widget_maker()
{
    L_widget=new QWidget(this);
    L_widget->setGeometry(400,200,514,368);
    L_widget->setStyleSheet("QWidget { background-color : grey; color : black; }");
    QLabel **locals;
    QPushButton *button1,*button2;
    locals=new QLabel*[3];
    for (int i=0;i<3;++i)
    {
        locals[i]=new QLabel(L_widget);
        locals[i]->setStyleSheet("QLabel {color:white;}");
        locals[i]->setFont(*font);
    }
    locals[0]->setGeometry(200,50,150,64);
    locals[1]->setGeometry(50,130,150,30);
    locals[2]->setGeometry(50,170,150,30);
    locals[0]->setText("You lost ");
    locals[1]->setText("Your score");
    locals[2]->setText("High score");
    button1=new QPushButton(L_widget);
    button2=new QPushButton(L_widget);
    button1->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
    button2->setStyleSheet("QPushButton { background-color : transparent; color : white; }");
    button1->setGeometry(50,310,200,50);
    button2->setGeometry(268,310,200,50);
    button1->setFont(*font);
    button2->setFont(*font);
    button1->setText("New Game");
    button2->setText("Main Menu");
    connect(button2,SIGNAL(clicked()),L_widget,SLOT(close()));
    connect(button2,SIGNAL(clicked()),this,SLOT(close()));

    connect(button1,SIGNAL(clicked()),this,SLOT(new_game()));
}

void widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(draw_image(0,0,1366,768) , sky);
    for (int i=0;i<101;++i)
    {
        painter.drawImage(draw_image(V[i],668,1366,100),desert);
    }
    painter.drawImage(draw_image(200,dino_y,100,100),dino);
    painter.drawImage(draw_image(flag_x,608,76,80),flag);
    for (size_t i=0;i<cactuses.size();++i)
    {
        if (for_type[i])
            painter.drawImage(draw_image(cactuses[i],588,70,90),cactus1);
        else painter.drawImage(draw_image(cactuses[i],588,70,90),cactus2);
    }
    painter.drawImage(draw_image(40,20,50,50),back);
}

void widget::keyPressEvent(QKeyEvent *K)
{
    switch(K->key())
    {
        case Qt::Key_Space:
        if (dino_y==588)
        {
            sound[0]->play();
            dino_flag=true;
            dino_t->start(3);
        }
        break;
    }
    update();
}

void widget::mousePressEvent(QMouseEvent *e)
{
    int x=e->x(),y=e->y();
    if (x>=40 && x<=90)
    {
        if (y>=20 && y<=70)
        {
           delete this;
        }
    }
}

void widget::move()
{
    int i;
    if (counter==50000)
        ++pix;
    if (counter==80000)
        ++pix;
    int size=cactuses.size();
    for(i = 0 ; i < size ; ++i)
    {
        if (i<101)
            V[i]-=pix;
        cactuses[i]-=pix;
        if (!for_type[i])
        {
             if (cactuses[i]>=190 && cactuses[i]<=273)
             {
                  if (dino_y>=498)
                  {
                        collission_flag=true;
                        sound[1]->play();
                        t->stop();
                        break;
                  }
              }
        }
        else
        {
             if (cactuses[i]>=190 && cactuses[i]<=268)
             {
                  if (dino_y>=508)
                  {
                        collission_flag=true;
                        sound[1]->play();
                        t->stop();
                        break;
                  }
             }
        }
    }
    flag_x-=pix;
    score+=pix;
    score_label->setText(to_string(score));
    counter+=pix;
    if (flag_x<=300)
    {
        winner_flag=true;
        sound[2]->play();
        t->stop();
    }

    if (winner_flag)
    {
        W_widget_maker();
        score_label2=new QLabel(W_widget);
        high_score_label=new QLabel(W_widget);
        score_label2->setFont(*font);
        high_score_label->setFont(*font);
        score_label2->setGeometry(350,130,150,30);
        high_score_label->setGeometry(350,170,150,30);
        score_label2->setStyleSheet("QLabel {color:white;}");
        high_score_label->setStyleSheet("QLabel {color:white;}");
        score_label2->setText(to_string(score));
        high_score_label->setText(to_string(highscore));
        if (score>highscore)
        {
            new_high_score_text_label=new QLabel(W_widget);
            new_high_score_label=new QLabel(W_widget);
            new_high_score_text_label->setFont(*font);
            new_high_score_label->setFont(*font);
            new_high_score_text_label->setGeometry(50,220,270,30);
            new_high_score_label->setGeometry(350,220,150,30);
            new_high_score_text_label->setStyleSheet("QLabel {color:white;}");
            new_high_score_label->setStyleSheet("QLabel {color:white;}");
            new_high_score_text_label->setText("New high score");
            new_high_score_label->setText(to_string(score));
            highscore=score;
        }
        if (myfile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&myfile);
            out<<to_string(highscore);
            myfile.close();
        }
        movie->stop();
        W_widget->show();
    }
    if (collission_flag)
    {
        L_widget_maker();
        score_label2=new QLabel(L_widget);
        high_score_label=new QLabel(L_widget);
        score_label2->setFont(*font);
        high_score_label->setFont(*font);
        score_label2->setGeometry(350,130,150,30);
        high_score_label->setGeometry(350,170,150,30);
        score_label2->setStyleSheet("QLabel {color:white;}");
        high_score_label->setStyleSheet("QLabel {color:white;}");
        score_label2->setText(to_string(score));
        high_score_label->setText(to_string(highscore));
        if (score>highscore)
        {
            new_high_score_text_label=new QLabel(L_widget);
            new_high_score_label=new QLabel(L_widget);
            new_high_score_text_label->setFont(*font);
            new_high_score_label->setFont(*font);
            new_high_score_text_label->setGeometry(50,220,270,30);
            new_high_score_label->setGeometry(350,220,150,30);
            new_high_score_text_label->setStyleSheet("QLabel {color:white;}");
            new_high_score_label->setStyleSheet("QLabel {color:white;}");
            new_high_score_text_label->setText("New high score");
            new_high_score_label->setText(to_string(score));
            highscore=score;
        }
        if (myfile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&myfile);
            out<<to_string(highscore);
            myfile.close();
        }
        movie->stop();
        L_widget->show();
    }
    update();
}

void widget::dino_jump()
{
   if (dino_y<=588)
   {
       if (dino_y==428)
            dino_flag=false;
       if (dino_flag)
       {
           movie->stop();
           --dino_y;
           --anim_label_y;
           animlabel->setGeometry(229,anim_label_y,43,31);
       }
       else
       {
           movie->stop();
           ++dino_y;
           ++anim_label_y;
           animlabel->setGeometry(229,anim_label_y,43,31);
       }
   }
   if (dino_y==588 && !dino_flag)
   {
       if (!collission_flag && !winner_flag)
            movie->start();
       dino_t->stop();
   }
   update();
}

void widget::new_game()
{
    L_widget->close();
    delete this;
    widget *w=new widget();
    w->showFullScreen();
}

QString widget::to_string(int n)
{
    QString answer=0;
    while(n)
    {
        answer.push_back(n%10+'0');
        n/=10;
    }
    reverse(answer.begin(),answer.end());
    if (answer.isEmpty())
        answer.push_back("0");
    return answer;
}
