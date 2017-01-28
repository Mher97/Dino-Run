#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QList>
#include <QSlider>
#include <QFont>
#include <QTimer>
#include <QDialog>
#include <QPaintEvent>
#include <QPalette>
#include <stdlib.h>
#include "widget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        QLabel *label1;
        QPushButton *start;
        QPushButton *about;
        QPushButton *exit;

        QMediaPlayer *media;
        QMediaPlaylist *playlist;
        QLabel *sound_label;
        QSlider *slider;
        QPushButton *sound_on;
        QPushButton *sound_off;
        QTimer *timer;
        QWidget *about_widget;
        void about_widget_maker();

        widget *W;
    private slots:
        void mediaslot0();
        void mediaslot1();
        void mediaslot2();
        void widget_show();
};

#endif // MAINWINDOW_H
