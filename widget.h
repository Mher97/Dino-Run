#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QRectF>
#include <QRect>
#include <QPen>
#include <QImage>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QSound>
#include <QMovie>
#include <ctime>
#include <algorithm>
#include <QFile>
#include <vector>

using namespace std;

namespace Ui
{
    class widget;
}

class widget : public QWidget
{
    Q_OBJECT

    public:
        explicit widget(QWidget *parent = 0);
        ~widget();

    private:
        Ui::widget *ui;
        QRectF draw_image(int a, int b, int c, int d);
        QImage desert;
        QImage sky;
        QImage flag;
        QImage dino;
        QImage cactus1;
        QImage cactus2;
        QImage back;
        int flag_x;
        int cactus_x;
        vector<int> V;
        vector<int> cactuses;
        vector<bool> for_type;

        QTimer *t;
        QTimer *dino_t;
        int dino_y;
        bool dino_flag;

        bool winner_flag;
        bool collission_flag;
        QWidget *W_widget;
        void W_widget_maker();
        QWidget *L_widget;
        void L_widget_maker();

        QLabel *score_label;
        QLabel *score_text_label;

        int counter;
        int pix;

        int score;
        int highscore;
        QFile myfile;
        QString to_string(int);

        QLabel *score_label2;
        QLabel *high_score_label;
        QLabel *new_high_score_label;
        QLabel *new_high_score_text_label;

        QFont *font;
        QSound *sound[3];

        QMovie *movie;
        QLabel *animlabel;
        int anim_label_y;

    protected:
        void paintEvent(QPaintEvent *e);
        void keyPressEvent(QKeyEvent *K);
        void mousePressEvent(QMouseEvent *e);
    private slots:
        void move();
        void dino_jump();
        void new_game();
};

#endif // WIDGET_H
